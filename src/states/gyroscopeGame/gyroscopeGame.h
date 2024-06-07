#include <core/state.h>
#include "core/macros.h"
#include "mbed.h"
#include "rtos.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "hardware/displayManager.h"

class GyroscopeGame : public State{
private:
    rtos::Thread *t_gameLogic = nullptr;        //Thread that handles the game logic/order
    rtos::Thread *t_userInput = nullptr;      //Thread that handles user input
    rtos::Thread *t_screenUpdate = nullptr;  //This thread is responsible for updating the screen when the SCREEN_UPDATE_FLAG is set (highest priority)

    rtos::EventFlags m_gameFlags;    //Contains flags ADVANCE_GAME_FLAG and SCREEN_UPDATE_FLAG

    // Ball properties
    int m_ballX = 64; // Center of the screen
    int m_ballY = 64; // Center of the screen
    const int m_ballRadius = 5;

    // Falling ball properties
    const static int m_numFallingBalls = 5;
    int m_fallingBallX[m_numFallingBalls];
    int m_fallingBallY[m_numFallingBalls];
    int m_fallingBallColors[m_numFallingBalls]; // Array to store colors of falling balls
    const int m_fallingBallRadius = 2;
    const int m_fallingSpeed = 4; // Falling speed

    // Gyro sensitivity (tune this value)
    const float m_sensitivity = 10.0; // Increased sensitivity

    // Score and time
    int m_score = 0;
    unsigned long m_startTime;
    unsigned long m_gameTime = 60000; // 1 minute in milliseconds

    // Game states
    enum GameState {
        STARTING,
        PLAYING,
        GAME_OVER
    };
public:

    explicit GyroscopeGame();

    void resetFallingBall(int index);

    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;
    void challenge(int score);
    void incrementCounter(); //Function that attaches to the timer interrupt ticker and increments time counter

    void game();               //Contains the logic for the game

};