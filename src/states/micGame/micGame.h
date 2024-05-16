
/**
 * @brief 
 * 
 * @class 
 *

 * @param 
 */
#ifndef GBGAME_micGame_H
#define GBGAME_micGame_H
#include <Arduino.h>
#include "core/macros.h"
#include "mbed.h"
#include "rtos.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "hardware/displayManager.h"
#include "hardware/ultrasonic.h"
#include "micGameUi.h"


class MicGame : public State {
private:
    rtos::Thread *t_gameLogic = nullptr;        //Thread that handles the game logic/order
    rtos::Thread *t_userInput = nullptr;      //Thread that handles user input
    rtos::Thread *t_screenUpdate = nullptr;  //This thread is responsible for updating the screen when the SCREEN_UPDATE_FLAG is set (highest priority)



    rtos::EventFlags m_gameFlags;    //Contains flags ADVANCE_GAME_FLAG and SCREEN_UPDATE_FLAG

    //Canvas object for drawing the screens
    MicGameUI *m_canvas = nullptr;

public:
    MicGame();

    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;

    void game();               //Contains the logic for the game

    int m_testNumber = 42; 

};

#endif //GBGAME_micGame_H