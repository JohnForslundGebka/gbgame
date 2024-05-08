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
#ifdef DEBUG
    Serial.println("NU KOLLAR MAINMENU STATE EFTER KNAPPTRYCK");
#endif

    while (m_isRunning){
        m_result = Buttons::states.wait_any(Buttons::UP_FLAG | Buttons::DOWN_FLAG | Buttons::A_FLAG, osWaitForever, true);
        // Handle input and update positions
        switch(m_result){
            case Buttons::UP_FLAG:
                canvas.c_hand.setY(max(30, canvas.c_hand.getY() - 20)); //update coordinates of hand
                if (m_selectedState > 1)
                    m_selectedState--;
                m_pntrCanvas = &canvas.c_hand;
                break;

            case Buttons::DOWN_FLAG:
                canvas.c_hand.setY(min(50, canvas.c_hand.getY() + 20)); //update coordinates of hand
                if (m_selectedState < 2)
                    m_selectedState++;
                m_pntrCanvas = &canvas.c_hand;
                break;

            case Buttons::A_FLAG:
                switch (m_selectedState) {  //start the selected state
                    case 1:
                        //set the stateFlags, to the state that the StateHandler should run
                        m_selectedState = 1;
                     //   Buttons::states.clear(Buttons::A_FLAG);
                        State::stateFlags.set(DISTANCE_GAME);
                        break;
                    default:
                        break;
                }

            default:
                break;
        }
        m_isDoneMoving.set(SCREEN_UPDATE_FLAG);
        canvas.c_hand.updatePos();
    }
}

/**
 * Updates the display based on the current state of the canvas.
 */
void MainMenu::update() {
#ifdef DEBUG
    Serial.println("NU KÖRS UPDATE I MAINMENU STATE");
#endif

    while (m_isRunning && m_isDoneMoving.wait_any(SCREEN_UPDATE_FLAG,osWaitForever)){
        m_displayManager.updateScreen(m_pntrCanvas);
    }
}
/**
 * Initializes and runs the main menu.
 */
void MainMenu::run() {
#ifdef DEBUG
    Serial.println("NU KÖRS MAIN MENU STATE");
#endif
    m_isRunning = true;

    t_gfx = new Thread;
    t_move = new Thread;

    t_gfx->start(callback(this, &MainMenu::update));
    t_move->start(callback(this, &MainMenu::handleInput));

    t_move->set_priority(osPriorityBelowNormal1);

    m_displayManager.updateScreen(&canvas.c_text);
    m_displayManager.updateScreen(&canvas.c_hand);
#ifdef DEBUG
    Serial.println("NU HAR MAIN MENU STATE GJORT FÄRDIGT SITT RUN");
#endif
}

void MainMenu::stop() {
    m_isRunning = false;
    t_gfx->join();
    t_move->join();
    delete t_gfx;
    delete t_move;

    t_gfx = nullptr;
    t_move = nullptr;
}

MainMenu::MainMenu() {
    canvas.init();
}
