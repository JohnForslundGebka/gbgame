#include "DistanceGame.h"
#include <Arduino.h>
#include <SPI.h>
#include "mbed.h"
#include "rtos.h"
#include "hardware/buttons.h"
using namespace mbed;
using namespace rtos;
using namespace std::chrono;

// Constructor implementation
DistanceGame::DistanceGame(Adafruit_SSD1351 &display) : m_canvas(128, 128), m_display(&display),
                                                  m_gfx(osPriorityNormal1, 1024), m_move(osPriorityNormal, 1024) {}

void DistanceGame::handleInput(){
    while (m_running && Buttons::states.wait_any(Buttons::UP_FLAG | Buttons::LEFT_FLAG | Buttons::RIGHT_FLAG | Buttons::DOWN_FLAG, osWaitForever, false)){

        switch(Buttons::states.get()){
            case Buttons::UP_FLAG:    m_yPos = max(0, m_yPos - 3); break;
            case Buttons::LEFT_FLAG:  m_xPos = max(0, m_xPos - 3); break;
            case Buttons::RIGHT_FLAG: m_xPos = min(127, m_xPos + 3); break;
            case Buttons::DOWN_FLAG:  m_yPos = min(127, m_yPos + 3); break;
            default: break;
        }
        m_isDoneMoving.set(MOV_FLAG);
        ThisThread::sleep_for(milliseconds(60));
    }
}

void DistanceGame::update(){
    while (m_running && m_isDoneMoving.wait_any(MOV_FLAG,osWaitForever))
    {
        m_canvas.fillScreen(0x0000);

        m_canvas.fillRect(m_xPos,m_yPos,14,14,BLUE);

        m_display->drawRGBBitmap(0, 0, m_canvas.getBuffer(), m_canvas.width(), m_canvas.height());
    }
}

void DistanceGame::run() {
    ::SPI.begin();
    m_display->begin(13000000);
    m_running = true;
    m_gfx.start(callback(this, &DistanceGame::update));
    m_move.start(callback(this, &DistanceGame::handleInput));

}

void DistanceGame::stop() {
    m_running = false;  // Signal threads to stop
    m_gfx.join();       // Wait for threads to finish
    m_move.join();
}
