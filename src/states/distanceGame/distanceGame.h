
/**
 * @brief Runs the game "DistanceGame", a game that lets the user 
 * play a game by measuring the distance to the wall. 
 * 
 * @class DistanceGame is a derived class of 'state'.
 * To run the DistanceGame set the DISTANCE_GAME flag State::stateFlags.set(DISTANCE_GAME)
 * and let the StateHandler switch to the DistanceGame state.
 *

 * @param DistanceGame::m_gameFlags has flags for updating the
 * SCREEN_UPDATE_FLAG and ADVANCE_GAME_FLAG that controls if the screen is 
 * updated or the game is advancing sequentially.
 */
#ifndef GBGAME_DistanceGame_H
#define GBGAME_DistanceGame_H
#include <Arduino.h>
#include "core/macros.h"
#include "mbed.h"
#include "rtos.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "hardware/displayManager.h"
#include "hardware/ultrasonic.h"
#include "distanceGameUi.h"

class ChallengeHandler;

//Number of rounds for a game
#define MAX_ROUNDS 3

class DistanceGame : public State {
private:
    Ultrasonic ultrasonic;     //Object that initializes the ultrasonic sensor and a method that reads the distance
    rtos::Thread *t_gameLogic = nullptr;        //Thread that handles the game logic/order
    rtos::Thread *t_userInput = nullptr;      //Thread that handles user input
    rtos::Thread *t_screenUpdate = nullptr;  //This thread is responsible for updating the screen when the SCREEN_UPDATE_FLAG is set (highest priority)

    rtos::EventFlags m_gameFlags;    //Contains flags ADVANCE_GAME_FLAG and SCREEN_UPDATE_FLAG

    //Canvas object for drawing the screens
    DistanceGameUi *m_canvas = nullptr;
public:
    DistanceGame();

    int textColor = WHITE;     //Variable for blinking text

    int m_targetLength{};        //Randomly generated number for the target length of the game
    int m_measured{};            //The distance read by the ultrasonic sensor get saved here
    int m_score{};               //The calculated score gets saved here when a measurement is taken.
    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;

    void game();               //Contains the logic for the game

    //UI function
    void screenBlink();        //Blinks the "press A" text

};

#endif //GBGAME_DistanceGame_H
