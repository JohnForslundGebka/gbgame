#include "mainMenu.h"
#include "mbed.h"
#include "rtos.h"
#include "ui/images.h"
using namespace mbed;
using namespace rtos;
using namespace std::chrono;

EventFlags State::stateFlags;

void MainMenu::handleInput() {
    while (m_isRunning && Buttons::states.wait_any(Buttons::UP_FLAG | Buttons::DOWN_FLAG | Buttons::A_FLAG, osWaitForever, false)) {

        // Handle input and update positions
        switch(Buttons::states.get()){
            case Buttons::UP_FLAG:
                m_handCanvas.setY(max(30, m_handCanvas.getY() - 20));
                m_pntrCanvas = &m_handCanvas;
                break;

            case Buttons::DOWN_FLAG:
                m_handCanvas.setY(min(50, m_handCanvas.getY() + 20));
                m_pntrCanvas = &m_handCanvas;
                break;

            case Buttons::A_FLAG:
                State::stateFlags.set(DISTANCE_GAME);
            default:
                break;
        }
        m_isDoneMoving.set(MOV_FLAG);
        m_handCanvas.updatePos();
        ThisThread::sleep_for(milliseconds(500));
    }
}

void MainMenu::update() {

    while (m_isRunning && m_isDoneMoving.wait_any(MOV_FLAG,osWaitForever)){
        m_displayManager.updateScreen(m_pntrCanvas);
    }
}

void MainMenu::run() {
    m_isRunning = true;
    m_gfx.start(callback(this, &MainMenu::update));
    m_move.start(callback(this, &MainMenu::handleInput));

    m_textCanvas.init();
    m_handCanvas.init();

    m_displayManager.updateScreen(&m_textCanvas);
    m_displayManager.updateScreen(&m_handCanvas);

}

void MainMenu::stop() {
    m_isRunning = false;
    m_gfx.join();
    m_move.join();
    State::stateFlags.set(MAIN_MENU);
    DigitalIn test();
}

MainMenu::MainMenu() : m_textCanvas(128,128,0,0), m_handCanvas(16,11,7,30),
                                     m_gfx(osPriorityNormal1, 1024),
                                     m_move(osPriorityNormal, 1024) {}
