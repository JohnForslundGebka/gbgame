#include "mainMenu.h"
#include "mbed.h"
#include "rtos.h"
#include "ui/images.h"
using namespace mbed;
using namespace rtos;
using namespace std::chrono;

EventFlags State::stateFlags;

/**
 * Handles button input to navigate through menu items.
 */
void MainMenu::handleInput() {
    uint32_t m_result;
    while (true){
        m_result = Buttons::states.wait_any(Buttons::UP_FLAG | Buttons::DOWN_FLAG | Buttons::A_FLAG, osWaitForever, true);
        // Handle input and update positions
        switch(m_result){
            case Buttons::UP_FLAG:
                m_handCanvas.setY(max(30, m_handCanvas.getY() - 20)); //update coordinates of hand
                m_selectedState = max(1,m_selectedState-1); //change the selected state
                m_pntrCanvas = &m_handCanvas;
                break;

            case Buttons::DOWN_FLAG:
                m_handCanvas.setY(min(50, m_handCanvas.getY() + 20)); //update coordinates of hand
                m_selectedState = min(2,m_selectedState+1); //change the selected state
                m_pntrCanvas = &m_handCanvas;
                break;

            case Buttons::A_FLAG:
                switch (m_selectedState) {  //start the selected state
                    case 1:
                        //set the stateFlags, to the state that the StateHandler should run
                        State::stateFlags.set(DISTANCE_GAME);
                        break;
                    default:
                        break;
                }

            default:
                break;
        }
        m_isDoneMoving.set(SCREEN_UPDATE_FLAG);
        m_handCanvas.updatePos();
       // ThisThread::sleep_for(milliseconds(500));
    }
}

/**
 * Updates the display based on the current state of the canvas.
 */
void MainMenu::update() {
    while (m_isRunning && m_isDoneMoving.wait_any(SCREEN_UPDATE_FLAG,osWaitForever)){
        m_displayManager.updateScreen(m_pntrCanvas);
    }
}
/**
 * Initializes and runs the main menu.
 */
void MainMenu::run() {
    m_isRunning = true;
    t_gfx.start(callback(this, &MainMenu::update));
    t_move.start(callback(this, &MainMenu::handleInput));

    m_textCanvas.init();
    m_handCanvas.init();

    m_displayManager.updateScreen(&m_textCanvas);
    m_displayManager.updateScreen(&m_handCanvas);

}

void MainMenu::stop() {
    m_isRunning = false;
    t_gfx.join();
    t_move.terminate();
    State::stateFlags.set(MAIN_MENU);
}

MainMenu::MainMenu() : m_textCanvas(128,128,0,0), m_handCanvas(16,11,7,30),
                       t_gfx(osPriorityNormal1, 1024),
                       t_move(osPriorityNormal, 1024) {}
