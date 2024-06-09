
/**
 * @brief This is the game "Voicy". You control the circle on the 
 * screen by making noise or sound into the microphone. You get points for every second
 * you stay on the waveform line.
 * 
 * @class MicGame contains the logic and initializes everything necessary for the "Voicy" game.
 *
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
#include "hardware/microphone.h"
#include "hardware/vibration.h"

class MicGame : public State {
private:
    rtos::Thread *t_gameLogic = nullptr;        //Thread that handles the game logic/order
    rtos::Thread *t_userInput = nullptr;        //Thread that handles user input
    rtos::Thread *t_screenUpdate = nullptr;     //This thread is responsible for updating the screen when the SCREEN_UPDATE_FLAG is set (highest priority)
    rtos::Thread *t_animateWaveform = nullptr;  //This thread animates the waveform on screen



    rtos::EventFlags m_gameFlags;    //Contains flags ADVANCE_GAME_FLAG and SCREEN_UPDATE_FLAG

    Vibration vibration;

    //Canvas object for drawing the screens
    MicGameUI *m_canvas = nullptr;
    bool challengeMode = false;

public:
    MicGame();

    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;

    void game();                          //Contains the logic for the game
    void animateWaveform();               //Function that animates the waveform in a thread
    void updatePosition(int change);      //Updates the new ball position

    void incrementCounter();              //Increments m_timerCounter by 1 every second, used for game length and score

    void challenge(int score);            //end or respond to a challenge

    Microphone mic;                       //object with all mic funtionality
    
    bool m_runWaveform = true;            //Used for exiting waveform animation
    int m_position = 64;                  //Position of the ball
    int m_score = 0;                      //User score, increments every second the waveform crosses the ball
    volatile int m_timeCounter = 0;       //Counts the seconds since state started

};

#endif //GBGAME_micGame_H
