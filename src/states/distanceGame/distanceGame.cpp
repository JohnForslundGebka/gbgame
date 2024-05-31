#include "distanceGame.h"
#include "distanceGameUi.h"
#include "rtos.h"
#include "mbed.h"
#include "functionality/scores.h"
#include "functionality/challengeHandler.h"


// Constructor, initializes all necessary objects
DistanceGame::DistanceGame():  State("Measury") {
}

void DistanceGame::handleInput() {
    using namespace rtos;
    using namespace mbed;
#ifdef DEBUG
     Serial.println("NU VÄNTAR JAG PÅ KNAPPAR");  
#endif
    while (m_isRunning) {
        using namespace std::chrono;

        uint32_t result = Buttons::states.wait_any(Buttons::START_FLAG  | Buttons::A_FLAG, osWaitForever, false);

        if (!m_isRunning) break;

        //debounce logic
        rtos::ThisThread::sleep_for(50ms);
        if(Buttons::states.get() == 0)
            continue;

        //clear flags
        Buttons::states.clear(Buttons::START_FLAG  | Buttons::A_FLAG);
        // Handle input and update positions
        switch (result) {
            case Buttons::A_FLAG :
                #ifdef DEBUG
                     Serial.println("HEJ FRAN A");
                #endif
                m_gameFlags.set(ADVANCE_GAME_FLAG);
                break;
            case Buttons::START_FLAG:
                #ifdef DEBUG
                    Serial.println("HEJ FRAN START");
                #endif
                 m_isRunning = false;
                State::stateFlags.set(GlobalStates::stateList[0]->getFlagName());
                break;
            default:
                break;
        }

    }
}

//Updates the screen immediately when the SCREEN_UPDATE_FLAG is set (this thread has the highest priority)
void DistanceGame::update(){
    while (m_isRunning)
    {
        m_gameFlags.wait_any(SCREEN_UPDATE_FLAG, osWaitForever);
        m_displayManager.updateScreen(&m_canvas->c_main);
    }
}

void DistanceGame::game() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    int m_totScore = 0;

    //class that is used for handling highscores and leaderboards
    Scores &leaderBoard = Scores::getInstance();
    //class that is used for challenges
    ChallengeHandler &challengeHandler = ChallengeHandler::getInstance();


#ifdef DEBUG
    Serial.println("NU BORJAR JAG");
#endif

      for (int i = 0; i < MAX_ROUNDS; i++) {
          //Seeds the random generator and generates the target length
          randomSeed(millis());
          m_targetLength = random(10, 100);
          //Creates and starts a thread that blink the screen text "button A"
          rtos::ThisThread::sleep_for(50ms);
          Thread t_screenBlink;
          t_screenBlink.start(mbed::callback(this, &DistanceGame::screenBlink));

#ifdef DEBUG
          Serial.println("NU GÖR JAG THREAD");
#endif
          m_canvas->drawScreen1();
          m_gameFlags.set(SCREEN_UPDATE_FLAG);

          //Waits for user to press A to measure distance
          m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);

          t_screenBlink.join();

          //Measures distance and calculates how far off the user was.
          m_measured = ultrasonic.readDistance();
          m_score = abs(m_targetLength - m_measured);

          if (m_score == 0) {
              m_score = 1;
          }

          double normalizedDifference = static_cast<double>(m_score) / m_targetLength;

          // Calculate the score: (1 - normalizedDifference) ensures that a smaller difference yields a higher score
          // Multiply by 100 to scale it up to the score range and use max to ensure the score is never negative
          int score = std::max(0, static_cast<int>((1 - normalizedDifference) * 100));

          m_totScore += score;

          //Draws screen2 with the results and sets the flag to update screen
          m_canvas->drawScreen2();
          m_gameFlags.set(SCREEN_UPDATE_FLAG);


          //Waits for button A press to finish the game
          m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);
      }

      //if a challenge is being played, do not send score to leaderboard
     if(challengeHandler.startingAChallenge) {
         challengeHandler.endStartChallenge(this,m_totScore);

     } else if (challengeHandler.respondingToChallenge){
        //get info from player 1
         String player1name = challengeHandler.currentChallenge->m_player1Name;
         int player1Score = challengeHandler.currentChallenge->m_player1Score;
         String player2name = challengeHandler.currentChallenge->m_player2Name;
         if(challengeHandler.endResponseToChallenge(m_totScore)){  //if the user won
                 m_canvas->drawChallengeWinScreen(player1name,player1Score,player2name,m_totScore);
                 m_gameFlags.set(SCREEN_UPDATE_FLAG);
                 rtos::ThisThread::sleep_for(5s);
                 State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
         } else {
             m_canvas->drawChallengeLooseScreen(player1name,player1Score,player2name,m_totScore);
             m_gameFlags.set(SCREEN_UPDATE_FLAG);
             rtos::ThisThread::sleep_for(5s);
             State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
         }

     }else {
         if (m_totScore > leaderBoard.maxScores[m_flagName]) {
             m_canvas->drawScreen4();
             m_gameFlags.set(SCREEN_UPDATE_FLAG);
             rtos::ThisThread::sleep_for(1s);
         }
         if (leaderBoard.addScore(m_totScore, this)) {
             m_isRunning = false;
             State::stateFlags.set(GlobalStates::stateList[INDEX_NEW_HIGHSCORE]->getFlagName());
         } else {
             m_canvas->drawScreen3(m_totScore);
             m_gameFlags.set(SCREEN_UPDATE_FLAG);

             rtos::ThisThread::sleep_for(3s);
             //Return to main manu when game finish
             m_isRunning = false;
             State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
         }
     }

#ifdef DEBUG
   Serial.println("NU HAR GAME KÖRTS KLART");
#endif

}

void DistanceGame::run() {

    using namespace rtos;
    using namespace mbed;
    //Starts the threads
    m_isRunning = true;

#ifdef DEBUG
    Serial.println("NU RUN JAG");
#endif

    t_gameLogic = new Thread;
    t_screenUpdate = new Thread;
    t_userInput = new Thread;
    m_canvas = new DistanceGameUi(this);


    t_gameLogic->start(mbed::callback(this, &DistanceGame::game));
    t_userInput->start(mbed::callback(this, &DistanceGame::handleInput));
    t_screenUpdate->start(mbed::callback(this, &DistanceGame::update));

#ifdef DEBUG
    Serial.println("NU RUN JAG FÄRDIGT");
#endif
}

void DistanceGame::stop() {
    using namespace std::chrono;
#ifdef DEBUG
    Serial.println("NU STOPPAR DISTANCEGAME");
#endif
    m_isRunning = false;
    //set flags, to not be stuck in waiting
    Buttons::states.set(Buttons::START_FLAG | Buttons::A_FLAG);
    m_gameFlags.set(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);
#ifdef DEBUG
    Serial.println("AVSLUTAR TRÅDAR");
#endif
    // Finnish threads and clean upp pointers
    if(t_gameLogic) {
        t_gameLogic->join();
        delete t_gameLogic;
        t_gameLogic = nullptr;
    }
#ifdef DEBUG
    Serial.println("AVSLUTAT GAME LOGIC");
#endif
    if(t_userInput){
        t_userInput->join();
        delete t_userInput;
        t_userInput = nullptr;
    }
#ifdef DEBUG
    Serial.println("AVSLUTAT USER INPUT");
#endif
    if(t_screenUpdate){
        t_screenUpdate->join();
        delete t_screenUpdate;
        t_screenUpdate = nullptr;
    }
#ifdef DEBUG
    Serial.println("AVSLUTAT SCREEN UPDARE");
#endif

    delete m_canvas; // Properly delete the m_canvas when stopping
    m_canvas = nullptr;


    //clear all flags before exiting
    m_gameFlags.clear(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);
    Buttons::states.clear(Buttons::START_FLAG | Buttons::A_FLAG);

    rtos::ThisThread::sleep_for(10ms);
#ifdef DEBUG
    Serial.println("HEJDA FRAN STOP I DISTANCEGAME");
#endif
}

void DistanceGame::screenBlink() {
    using namespace std::chrono;
    while (m_isRunning) {
#ifdef DEBUG
        Serial.println("NU BLINKAR JAG");
#endif
        if (m_gameFlags.get() & ADVANCE_GAME_FLAG) {
            m_gameFlags.clear(ADVANCE_GAME_FLAG);
            break;
        }

        textColor = WHITE;
        m_canvas->drawScreen1();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        rtos::ThisThread::sleep_for(300ms);
        textColor = BLACK;
        m_canvas->drawScreen1();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        rtos::ThisThread::sleep_for(300ms);
    }
}



