#include "gyroscopeGame.h"

GyroscopeGame::GyroscopeGame() : State("Balancey") {}


void GyroscopeGame::handleInput() {

}

void GyroscopeGame::game() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    const int GAME_LENGTH = 60;             //Length in seconds of a game
    //Creates and initializes a timer and attached a function that increments m_timeCounter every second
    Ticker ticker;
    ticker.attach([this]() { this->incrementCounter(); }, 1s);
    //variables used for the Gyroscope
    float x, y, z;

    // Initialize falling balls with random positions and colors
    for (int i = 0; i < m_numFallingBalls; i++) {
        resetFallingBall(i);
    }

    while (m_isRunning){
       switch(gameState)
           case PLAYING :
               //check if the time is up
               if(m_timeCounter >= GAME_LENGTH){
                   gameState = GAME_OVER;
                   break;
               }


    }
}

void GyroscopeGame::stop() {

}

void GyroscopeGame::update() {

}


void GyroscopeGame::run() {
    using namespace rtos;
    using namespace mbed;
    m_score = 0;
    m_timeCounter = 0;
    m_isRunning = true;

    t_gameLogic = new Thread;
    t_screenUpdate = new Thread;
    t_userInput = new Thread;

    //Start the threads
    t_gameLogic->start(mbed::callback(this, &GyroscopeGame::game));
    t_userInput->start(mbed::callback(this, &GyroscopeGame::handleInput));
    t_screenUpdate->start(mbed::callback(this, &GyroscopeGame::update));

    m_canvas = new GyroScopeGameUi(this);

    //initialize the Gyroscope
    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
    }
    Serial.println("IMU initialized!");

    gameState = PLAYING;
}

void GyroscopeGame::resetFallingBall(int index) {
    m_fallingBallX[index] = random(0, 127);
    m_fallingBallY[index] = 0;
    // Assign colors with green balls being four times as frequent as red balls
    m_fallingBallColors[index] = (random(0, 5) > 0) ? GREEN : RED;
}

void GyroscopeGame::updatePositionOfBall() {

}

void GyroscopeGame::incrementCounter() {
    m_timeCounter++;
}

void GyroscopeGame::challenge(int score) {

}