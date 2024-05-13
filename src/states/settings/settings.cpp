#include "settings.h"
#include "rtos.h"

void Settings::handleInput() {
    using namespace std::chrono;

    while (m_isRunning){

        uint32_t m_result = Buttons::states.wait_any(Buttons::UP_FLAG | Buttons::DOWN_FLAG | Buttons::A_FLAG | Buttons::LEFT_FLAG | Buttons::RIGHT_FLAG, osWaitForever, false);

        if (!m_isRunning) break;
        //debounce logic
        ThisThread::sleep_for(50ms);
        if(Buttons::states.get() == 0)
            continue;

        // Handle input and update positions
        switch(m_result){
            case Buttons::LEFT_FLAG:
                Buttons::states.clear(Buttons::UP_FLAG);
                if(m_selectedState == (GlobalStates::numberOfSettingsStates - 1))
                    m_selectedState = 0;
                else if (m_selectedState == 0)
                    m_selectedState = (GlobalStates::numberOfSettingsStates - 1);
                else
                    m_selectedState--;
                m_canvas.updateText();
                m_pntrCanvas = &m_canvas.c_canvas;
                Buttons::states.clear(Buttons::LEFT_FLAG);
                break;

            case Buttons::RIGHT_FLAG:
                Buttons::states.clear(Buttons::DOWN_FLAG);
                if(m_selectedState == (GlobalStates::numberOfSettingsStates - 1))
                    m_selectedState = 0;
                else if (m_selectedState == 0)
                    m_selectedState = (GlobalStates::numberOfSettingsStates - 1);
                else
                    m_selectedState++;
                m_canvas.updateText();
                m_pntrCanvas = &m_canvas.c_canvas;
                Buttons::states.clear(Buttons::RIGHT_FLAG);
                break;

            case Buttons::A_FLAG:
                //set the stateFlags, to the state that the StateHandler should run
                State::stateFlags.set(GlobalStates::settingsList[m_selectedState]->getFlagName());
                break;

            default:
                break;
        }
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
    }
}

void Settings::update() {
    while (m_isRunning && m_gameFlags.wait_any(SCREEN_UPDATE_FLAG,osWaitForever)){
        m_displayManager.updateScreen(m_pntrCanvas);
    }
}

void Settings::game() {

    while(m_isRunning)
    {
        switch(m_gameFlags.wait_any())
        {

        }
    }

}

void Settings::run() {
    m_isRunning = true;

    t_gfx = new Thread;
    t_move = new Thread;

    t_gfx->start(callback(this, &Settings::update));
    t_move->start(callback(this, &Settings::handleInput));

    t_move->set_priority(osPriorityBelowNormal1);

    m_canvas.init();

    m_displayManager.updateScreen(&m_canvas.c_canvas);
}

void Settings::stop() {
    m_isRunning = false;
    t_gfx->join();
    t_move->join();
    delete t_gfx;
    delete t_move;

    Buttons::states.clear(Buttons::ALL_FLAG);
    t_gfx = nullptr;
    t_move = nullptr;
}

Settings::Settings() : State("Settings"), m_canvas(this) {

}
