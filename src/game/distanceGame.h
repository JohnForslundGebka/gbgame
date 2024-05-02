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

using namespace mbed;
using namespace rtos;
using namespace std::chrono;

class DistanceGame : public State {
private:
    GFXcanvas16 m_canvas;
    Adafruit_SSD1351 *m_display;
    Thread m_gfx;
    Thread m_move;
    EventFlags m_isDoneMoving;
   // bool m_running;

    int m_xPos = 64;
    int m_yPos = 64;

public:
    DistanceGame(Adafruit_SSD1351 &display);
    void run() override;
    void handleInput() override;
    void update() override;
    void stop() override;
};



#endif //GBGAME_DistanceGame_H
