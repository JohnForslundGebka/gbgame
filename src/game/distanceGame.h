#ifndef GBGAME_DistanceGame_H
#define GBGAME_DistanceGame_H
#include <Arduino.h>
#include "core/macros.h"
#include "mbed.h"
#include "rtos.h"
#include "core/state.h"
#include "hardware/buttons.h"
#include "hardware/displayManager.h"
#include "ui/canvas.h"
#include "hardware/ultrasonic.h"

using namespace mbed;
using namespace rtos;
using namespace std::chrono;

//Number of rounds for a game
#define MAX_ROUNDS 3

class DistanceGame : public State {
private:
    
    Ultrasonic ultrasonic;     //Object that initializes the ultrasonic sensor and a method that reads the distance
    Thread t_gameLogic;        //Thread that handles the game logic/order
    Thread t_userInput;        //Thread that handles user input
    Thread t_screenUpdate;     //This thread is resposible for updating the screen when the SCREEN_UPDATE_FLAG is set (highest prority)

    EventFlags m_gameFlags;    //Contains flags ADVANCE_GAME_FLAG and SCREEN_UPDATE_FLAG

    Canvas m_canvas;           //Canvas object for drawing the screens
    int textColor = WHITE;     //Variable for blinking text
    
    int m_targetLength;        //Randomly generated number for the target length of the game
    int m_measured;            //The distance read by the ultracosin sensor get saved here
    int m_score;               //The calculated score gets saved here when a measurement is taken.
  
public:
    DistanceGame();
    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;

    void game();               //Contains the logic for the game

    void draw_screen1();       //Draws screen 1
    void draw_screen2();       //Draws screen 2
};



#endif //GBGAME_DistanceGame_H
