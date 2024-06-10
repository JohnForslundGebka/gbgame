/**
* @class GyroscopeGame
* @brief A game that uses a gyroscope for control.
*
* This class represents a game where the player controls a ball using a gyroscope.
* The game logic, user input, and screen updates are handled by separate threads.
* The game has two states: PLAYING and GAME_OVER.
*/
#include <Wire.h>
#include <SPI.h>
#include <core/state.h>
#include <Arduino_LSM6DSOX.h>
#include "core/macros.h"
#include "mbed.h"
#include "rtos.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "hardware/displayManager.h"
#include "gyroScopeGameUi.h"



class GyroscopeGame : public State{
private:
    rtos::Thread *t_gameLogic = nullptr;        //Thread that handles the game logic/order
    rtos::Thread *t_userInput = nullptr;      //Thread that handles user input
    rtos::Thread *t_screenUpdate = nullptr;  //This thread is responsible for updating the screen when the SCREEN_UPDATE_FLAG is set (highest priority)
    rtos::EventFlags m_gameFlags;    //Contains flags ADVANCE_GAME_FLAG and SCREEN_UPDATE_FLAG
    GyroScopeGameUi *m_canvas = nullptr;

    // Gyro sensitivity (tune this value)
    const float m_sensitivity = 10.0;

    // Game states
    enum GameState {
        PLAYING,
        GAME_OVER
    };
    GameState gameState;
    bool m_challengeMode = false;
public:
    // Score and time
    int m_score;
    int m_timeCounter = 60;

    //falling ball properties
    const static int m_numFallingBalls = 5;
    struct Ball {
        int x;
        int y;
        uint16_t color;
    };
    Ball m_fallingBalls[m_numFallingBalls];
    const int m_fallingBallRadius = 2;
    const int m_fallingSpeed = 4; // Falling speed

    // players ball properties
    int m_playerBallX = 64; // Center of the screen
    int m_playerBally = 64; // Center of the screen
    const int PLAYERBALL_RADIUS = 5;

    explicit GyroscopeGame();

    void resetFallingBall(int index);

    void run() override;
    void handleInput() override; //Function that attaches to the user input thread and handles the user button presses
    void update() override;
    void stop() override;
    void challenge(int score); //Function that is called when the game is played in challenge mode
    void incrementCounter(); //Function that attaches to the timer interrupt ticker and increment time counter
    void updatePositionOfBall(); //Reads the gyroscope data and updates the position of the player ball
    void game();               //Contains the logic for the game
};