#include "settings.h"
#include "rtos.h"

void Settings::handleInput() {
    using namespace std::chrono;

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
                if(m_selectedState == (GlobalStates::numberOfSettingsStates - 1))
                    m_selectedState = 0;
                else if (m_selectedState == 0)
                    m_selectedState = (GlobalStates::numberOfSettingsStates - 1);
                else
                    m_selectedState--;
                m_canvas.draw();
                m_pntrCanvas = &m_canvas.c_canvas;
                break;

            case Buttons::DOWN_FLAG:
                Buttons::states.clear(Buttons::DOWN_FLAG);
                if(m_selectedState == (GlobalStates::numberOfSettingsStates - 1))
                    m_selectedState = 0;
                else if (m_selectedState == 0)
                    m_selectedState = (GlobalStates::numberOfSettingsStates - 1);
                else
                    m_selectedState++;
                m_canvas.draw();
                m_pntrCanvas = &m_canvas.c_canvas;
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

void Settings::run() {

}

void Settings::stop() {

}

Settings::Settings() : State("Settings"), m_canvas(this) {

}
