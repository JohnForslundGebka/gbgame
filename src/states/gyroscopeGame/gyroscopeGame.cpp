#include "gyroscopeGame.h"
#include "functionality/scores.h"
#include "functionality/challengeHandler.h"

GyroscopeGame::GyroscopeGame() : State("Tilty"), IMU_LSM6DSOX(Wire,0x6A) {}


void GyroscopeGame::handleInput() {
while (true){

    uint32_t result = Buttons::states.wait_any(Buttons::START_FLAG  | Buttons::A_FLAG, osWaitForever, false);

    if (result== Buttons::START_FLAG) {
        m_isRunning = false;
        State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
        Buttons::states.clear(Buttons::START_FLAG);
        break;
    } else if (result == Buttons::A_FLAG) {
       // m_gameFlags.set(ADVANCE_GAME_FLAG);
        Buttons::states.clear(Buttons::A_FLAG);
    }
}
}

void GyroscopeGame::game() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    //class that is used for handling highscores and leaderboards
    Scores &leaderBoard = Scores::getInstance();
    //class that is used for challenges
    ChallengeHandler &challengeHandler = ChallengeHandler::getInstance();
    m_challengeMode = challengeHandler.startingAChallenge || challengeHandler.respondingToChallenge;

    //Creates and initializes a timer and attached a function that increments m_timeCounter every second
    Ticker ticker;
    ticker.attach([this]() { this->incrementCounter(); }, 1s);

    // Initialize falling balls with random positions and colors
    for (int i = 0; i < m_numFallingBalls; i++) {
        resetFallingBall(i);
    }

    while (m_isRunning) {
        switch (gameState) {
            case PLAYING :
                //check if the time is up
                if (m_timeCounter == 0) {
                    gameState = GAME_OVER;
                    break;
                }
                //draw the score and time and player ball
                m_canvas->draw();
                for (int i = 0; i < m_numFallingBalls; i++) {
                    //draw the falling ball
                    m_canvas->drawFallingBalls(m_fallingBalls[i].x, m_fallingBalls[i].y, m_fallingBalls[i].color);
                    m_fallingBalls[i].y += m_fallingSpeed;
                    // Check if any part of the player's ball overlaps with the falling ball
                    if (abs(m_fallingBalls[i].x - m_playerBallX) < PLAYERBALL_RADIUS + m_fallingBallRadius &&
                        abs(m_fallingBalls[i].y - m_playerBally) < PLAYERBALL_RADIUS + m_fallingBallRadius) {
                        // Update score based on the color of the falling ball
                        if (m_fallingBalls[i].color == GREEN) {
                            m_score++;
                        } else if (m_fallingBalls[i].color == RED) {
                            m_score -= 2;
                        }
                        resetFallingBall(i);
                    }
                    // Reset the falling ball if it goes off the screen
                    if (m_fallingBalls[i].y > 127) {
                        resetFallingBall(i);
                    }
                }
                // Update the player's ball position based on gyroscope data
                updatePositionOfBall();
                m_gameFlags.set(SCREEN_UPDATE_FLAG);
              //  ThisThread::sleep_for(50ms);
                break;

            case GAME_OVER :
                if(m_challengeMode){
                    challenge(m_score);
                } else {
                    //if a new highscore was set
                    if (m_score > leaderBoard.maxScores[m_flagName]) {
                        m_canvas->drawCheckingSCore();
                        m_gameFlags.set(SCREEN_UPDATE_FLAG);
                        rtos::ThisThread::sleep_for(50ms);
                        leaderBoard.checkIfScoreWasHighcore(m_score, this);
                        m_isRunning = false;
                        State::stateFlags.set(GlobalStates::stateList[INDEX_NEW_HIGHSCORE]->getFlagName());
                    }else {
                       //if not added to leaderboard
                        m_canvas->drawNoHighcoreScreen(m_score); //draw the no highscore screen
                        m_gameFlags.set(SCREEN_UPDATE_FLAG);

                        rtos::ThisThread::sleep_for(5s);
                        //Return to main manu when game finish
                        m_isRunning = false;
                        State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
                    }

              //  m_gameFlags.set(SCREEN_UPDATE_FLAG);
                m_isRunning = false;
                break;
        }
    }
    }


}

void GyroscopeGame::stop() {
    using namespace std::chrono;
    m_isRunning = false;
    //set flags, to not be stuck in waiting
    Buttons::states.set(Buttons::START_FLAG | Buttons::A_FLAG);
    m_gameFlags.set(SCREEN_UPDATE_FLAG);

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

    IMU.end();

    //clear all flags before exiting
    m_gameFlags.clear(SCREEN_UPDATE_FLAG);
    Buttons::states.clear(Buttons::START_FLAG | Buttons::A_FLAG);

    rtos::ThisThread::sleep_for(50ms);
}

void GyroscopeGame::update() {

    while (m_isRunning)
    {   m_gameFlags.wait_any(SCREEN_UPDATE_FLAG, osWaitForever, true);
        m_displayManager.updateScreen(&m_canvas->c_main);
    }
}


void GyroscopeGame::run() {
    //initialize the game
    m_timeCounter = 60;
    gameState = PLAYING;
    using namespace rtos;
    using namespace mbed;
    m_score = 0;
    m_isRunning = true;
    //Create the threads
    t_gameLogic = new Thread;
    t_screenUpdate = new Thread;
    t_userInput = new Thread;

    //Start the threads
    t_gameLogic->start(mbed::callback(this, &GyroscopeGame::game));
    t_userInput->start(mbed::callback(this, &GyroscopeGame::handleInput));
    t_screenUpdate->start(mbed::callback(this, &GyroscopeGame::update));
    t_screenUpdate->set_priority(osPriorityAboveNormal);
    t_userInput->set_priority(osPriorityAboveNormal);

    m_canvas = new GyroScopeGameUi(this);
    m_canvas->draw();
    m_displayManager.updateScreen(&m_canvas->c_main);

   // initialize the Gyroscope
    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
    }
    Serial.println("IMU initialized!");

}
//function to reset the falling ball
void GyroscopeGame::resetFallingBall(int index) {
    m_fallingBalls[index].x = random(0, 127);
    m_fallingBalls[index].y = 0;
    // Assign colors with green balls being four times as frequent as red balls
    m_fallingBalls[index].color = (random(0, 5) > 0) ? GREEN : RED;
    Serial.println("resetting falling ball");
}

void GyroscopeGame::incrementCounter() {
    m_timeCounter--;
}

void GyroscopeGame::updatePositionOfBall() {
    float x, y, z;
    // Update ball position based on IMU data
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(x, y, z);
        m_playerBallX += int(y * m_sensitivity); // Use gyroscope's Y-axis reading for left-right movement
        m_playerBally += int(x * m_sensitivity); // Use gyroscope's X-axis reading for up-down movement

        // Ensure the ball stays within the screen bounds
        if (m_playerBallX < PLAYERBALL_RADIUS) m_playerBallX = PLAYERBALL_RADIUS;
        if (m_playerBallX > 127 - PLAYERBALL_RADIUS) m_playerBallX = 127 - PLAYERBALL_RADIUS;
        if (m_playerBally < PLAYERBALL_RADIUS) m_playerBally = PLAYERBALL_RADIUS;
        if (m_playerBally > 127 - PLAYERBALL_RADIUS) m_playerBally = 127 - PLAYERBALL_RADIUS;
    }

}

void GyroscopeGame::challenge(int score) {
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
            m_canvas->drawChallengeLoseScreen(player1name,player1Score,player2name,score);
            m_gameFlags.set(SCREEN_UPDATE_FLAG);
            rtos::ThisThread::sleep_for(std::chrono::seconds(5));
            State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
        }
    }
}