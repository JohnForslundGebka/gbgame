#include "mainMenu.h"
#include "mbed.h"
#include "rtos.h"

using namespace mbed;
using namespace rtos;


EventFlags State::stateFlags;

/**
 * Handles button input to navigate through menu items.
 */
void MainMenu::handleInput() {
    using namespace std::chrono;

#ifdef DEBUG
    Serial.println("NU KOLLAR MAINMENU STATE EFTER KNAPPTRYCK");
#endif

    while (m_isRunning){

        uint32_t m_result = Buttons::states.wait_any(Buttons::UP_FLAG | Buttons::DOWN_FLAG | Buttons::A_FLAG, osWaitForever, false);

        if (!m_isRunning) break;

        //debounce logic
        ThisThread::sleep_for(50ms);
        if(Buttons::states.get() == 0)
            continue;

        // Handle input and update positions
        switch(m_result){
            case Buttons::UP_FLAG:
                Buttons::states.clear(Buttons::UP_FLAG);
                if(m_selectedState == (GlobalStates::numberOfMainMenuStates - 1))
                    m_selectedState = 0;
                else if (m_selectedState == 0)
                    m_selectedState = (GlobalStates::numberOfMainMenuStates - 1);
                else
                    m_selectedState--;
                m_canvas->moveUp();
                m_pntrCanvas = &m_canvas->c_canvas;
                break;

            case Buttons::DOWN_FLAG:
                Buttons::states.clear(Buttons::DOWN_FLAG);
                if(m_selectedState == (GlobalStates::numberOfMainMenuStates - 1))
                    m_selectedState = 0;
                else if (m_selectedState == 0)
                    m_selectedState = (GlobalStates::numberOfMainMenuStates - 1);
                else
                    m_selectedState++;
                m_canvas->moveDown();
                m_pntrCanvas = &m_canvas->c_canvas;
                break;

            case Buttons::A_FLAG:
                //set the stateFlags, to the state that the StateHandler should run
                State::stateFlags.set(GlobalStates::mainMenuList[m_selectedState]->getFlagName());
                break;

            default:
                break;
        }
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
    }
}

/**
 * Updates the display based on the current state of the canvas.
 */
void MainMenu::update() {
#ifdef DEBUG
    Serial.println("NU KÖRS UPDATE I MAINMENU STATE");
#endif

    while (m_isRunning && m_gameFlags.wait_any(SCREEN_UPDATE_FLAG,osWaitForever)){
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
    m_canvas = new MainMenuUi(this);

    t_gfx->start(callback(this, &MainMenu::update));
    t_move->start(callback(this, &MainMenu::handleInput));

    t_move->set_priority(osPriorityBelowNormal1);

    m_canvas->init();

    m_displayManager.updateScreen(&m_canvas->c_canvas);
    
#ifdef DEBUG
    Serial.println("NU HAR MAIN MENU STATE GJORT FÄRDIGT SITT RUN");
#endif
}

void MainMenu::stop() {
    m_isRunning = false;
    if (t_gfx) {
        t_gfx->join();
        delete t_gfx;
        t_gfx = nullptr;
    }
    if (t_move) {
        t_move->join();
        delete t_move;
        t_move = nullptr;
    }

    delete m_canvas; // Properly delete the m_canvas when stopping
    m_canvas = nullptr;
    Buttons::states.clear(Buttons::ALL_FLAG);

}

MainMenu::MainMenu() : State("Main Menu"){
}
