#ifndef GBGAME_DistanceGame_H
#define GBGAME_DistanceGame_H
#include <Arduino.h>
#include <SPI.h>
#include "core/macros.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
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
    
    Ultrasonic ultrasonic;
    Thread m_gameLogic;
    Thread m_userInput;
    EventFlags m_updateUI;
    bool m_running;

    Canvas m_screen;



    int m_targetLength;
    int m_measured = 0;
    int m_score = 0;
   
    


public:
    DistanceGame();
    void game();
    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;
};



#endif //GBGAME_DistanceGame_H
