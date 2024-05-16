#include "games.h"
#include "gamesUi.h"
#include "rtos.h"


void Games::handleInput() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    while (m_isRunning){

        //the thread will pause until a new button press is detected
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
                //makes sure the m_selectedState does not go "out of bounds"
                if(m_selectedState == (GlobalStates::numberOfGameStates - 1))
                    m_selectedState = 0;
                else if (m_selectedState == 0)
                    m_selectedState = (GlobalStates::numberOfGameStates - 1);
                else
                    m_selectedState--;
                m_canvas->draw();
                m_pntrCanvas = &m_canvas->c_canvas;
                break;

            case Buttons::DOWN_FLAG:
                Buttons::states.clear(Buttons::DOWN_FLAG);
                //makes sure the m_selectedState does not go "out of bounds"
                if(m_selectedState == (GlobalStates::numberOfGameStates - 1))
                    m_selectedState = 0;
                else if (m_selectedState == 0)
                    m_selectedState = (GlobalStates::numberOfGameStates - 1);
                else
                    m_selectedState++;
                m_canvas->draw();
                m_pntrCanvas = &m_canvas->c_canvas;
                break;

            case Buttons::A_FLAG:
                //set the stateFlags, to the state that the StateHandler should run
                State::stateFlags.set(GlobalStates::gameList[m_selectedState]->getFlagName()); //select which state to run based on the selected state variable
                break;

            default:
                break;
        }
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
    }

}

void Games::update() {

    while (m_isRunning && m_gameFlags.wait_any(SCREEN_UPDATE_FLAG,osWaitForever)){
        m_displayManager.updateScreen(m_pntrCanvas);
    }
}

void Games::run() {
    using namespace rtos;
    using namespace mbed;
    m_isRunning = true;

    t_gfx = new rtos::Thread;
    t_move = new rtos::Thread;
    m_canvas = new GamesUI(this);

    t_gfx->start(callback(this, &Games::update));
    t_move->start(callback(this, &Games::handleInput));

    t_move->set_priority(osPriorityBelowNormal1);

    m_canvas->init();

    m_displayManager.updateScreen(&m_canvas->c_canvas);
}

void Games::stop() {
    //clean upp all the threads and pointers
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

Games::Games() : State("Games"){}
