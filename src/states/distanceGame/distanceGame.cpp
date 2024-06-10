#include "distanceGame.h"
#include "distanceGameUi.h"
#include "rtos.h"
#include "functionality/scores.h"
#include "functionality/challengeHandler.h"
#include "wifi/dataTransmit.h"


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

        uint32_t result = Buttons::states.wait_any(Buttons::START_FLAG | Buttons::A_FLAG, osWaitForever, false);

        if (!m_isRunning) break;

        //debounce logic
        rtos::ThisThread::sleep_for(50ms);
        if(Buttons::states.get() == 0){
            continue; // If no button is pressed, continue to wait
        }
        // Handle input and update positions
        switch (result) {
            case Buttons::A_FLAG :
                m_gameFlags.set(ADVANCE_GAME_FLAG);
                Buttons::states.clear(Buttons::A_FLAG);
                break;
            case Buttons::START_FLAG:
                 m_isRunning = false;
                 Buttons::states.clear(Buttons::START_FLAG);
                State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
                break;
            default:
                break;
        }

    }
}

//Updates the screen immediately when the SCREEN_UPDATE_FLAG is set
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
    challengeMode = challengeHandler.startingAChallenge || challengeHandler.respondingToChallenge;

    for (int i = 0; i < MAX_ROUNDS; i++) {
        //Seeds the random generator and generates the target length
        randomSeed(millis());
        m_targetLength = random(10, 100);
        //Creates and starts a thread that blink the screen text "button A"
        rtos::ThisThread::sleep_for(50ms);
        Thread t_screenBlink(osPriorityBelowNormal2,1024);
        m_shouldBlink = true;
        t_screenBlink.start(mbed::callback(this, &DistanceGame::screenBlink));

        m_canvas->drawScreen1();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        //Waits for user to press A to measure distance
        rtos::ThisThread::sleep_for(500ms);
        m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);

        m_shouldBlink = false;
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
    //If the game is in challenge mode, do not check for highscore
    if(challengeMode){
        challenge(m_totScore);
    } else if(m_totScore > leaderBoard.maxScores[m_flagName]) { //if a new highscore was set
        m_canvas->drawScreen4();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        DataTransmit &wifi = DataTransmit::getInstance();
        if (wifi.wifiIsConnected){ //If wifi is connected, send the new highscore to the database
            leaderBoard.checkIfScoreWasHighcore(m_totScore, this);
        }
        m_isRunning = false;
        State::stateFlags.set(GlobalStates::stateList[INDEX_NEW_HIGHSCORE]->getFlagName());
    } else {   //if no new highscore was set
        m_canvas->drawScreen3(m_totScore);
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        rtos::ThisThread::sleep_for(3s);
        //Return to main manu when game finish
        m_isRunning = false;
        State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
    }
}

void DistanceGame::run() {

    using namespace rtos;
    using namespace mbed;
    //Starts the threads
    m_isRunning = true;

    t_gameLogic = new Thread;
    t_screenUpdate = new Thread;
    t_userInput = new Thread;
    m_canvas = new DistanceGameUi(this);


    t_gameLogic->start(mbed::callback(this, &DistanceGame::game));
    t_userInput->start(mbed::callback(this, &DistanceGame::handleInput));
    t_screenUpdate->start(mbed::callback(this, &DistanceGame::update));
}

void DistanceGame::stop() {
    using namespace std::chrono;

    m_isRunning = false;
    //set flags, to not be stuck in waiting
    Buttons::states.set(Buttons::START_FLAG | Buttons::A_FLAG);
    m_gameFlags.set(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);

    // Finnish threads and clean upp pointers
    if(t_gameLogic) {
        t_gameLogic->join();
        delete t_gameLogic;
        t_gameLogic = nullptr;
    }

    if(t_userInput){
        t_userInput->join();
        delete t_userInput;
        t_userInput = nullptr;
    }

    if(t_screenUpdate){
        t_screenUpdate->join();
        delete t_screenUpdate;
        t_screenUpdate = nullptr;
    }

    delete m_canvas; // Properly delete the m_canvas when stopping
    m_canvas = nullptr;

    //clear all flags before exiting
    m_gameFlags.clear(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);
    Buttons::states.clear(Buttons::START_FLAG | Buttons::A_FLAG);

    rtos::ThisThread::sleep_for(10ms);

}
//Blinks the screen text "button A" to indicate to the user that they should press the button
void DistanceGame::screenBlink() {
    using namespace std::chrono;
    while (m_shouldBlink) {
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
//Handles the challenge logic
void DistanceGame::challenge(int score) {
    ChallengeHandler &ch = ChallengeHandler::getInstance();
    //If the user is starting a new challenge
    if(ch.startingAChallenge) {
        ch.endStartChallenge(this,score);
    } else if (ch.respondingToChallenge){
          //get info from player 1
          String player1name = ch.currentChallenge->m_player1Name;
          int player1Score = ch.currentChallenge->m_player1Score;
          String player2name = ch.currentChallenge->m_player2Name;
          if(ch.endResponseToChallenge(score)){
              m_canvas->drawChallengeWinScreen(player1name,player1Score,player2name,score);
              m_gameFlags.set(SCREEN_UPDATE_FLAG);
              rtos::ThisThread::sleep_for(std::chrono::seconds(5));
              State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
          } else {
              m_canvas->drawChallengeLooseScreen(player1name,player1Score,player2name,score);
              m_gameFlags.set(SCREEN_UPDATE_FLAG);
              rtos::ThisThread::sleep_for(std::chrono::seconds(5));
              State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
          }
    }
}



