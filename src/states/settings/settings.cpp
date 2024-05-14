#include "settings.h"
#include "rtos.h"

void Settings::handleInput() {
    using namespace std::chrono;
    while (m_isRunning){
        uint32_t input = Buttons::states.wait_any(Buttons::UP_FLAG | Buttons::DOWN_FLAG | Buttons::A_FLAG | Buttons::LEFT_FLAG | Buttons::RIGHT_FLAG | Buttons::START_FLAG, osWaitForever, false);
        if (!m_isRunning) break;
        //debounce logic
        ThisThread::sleep_for(50ms);
        if(Buttons::states.get() == 0)
            continue;

        //change the hand state
        if(input==Buttons::UP_FLAG){
            if(m_handPos >= 0){
                m_handPos--;
                newHandPos();
                Buttons::states.clear(Buttons::ALL_FLAG);
                continue;
            }
        } else if (input==Buttons::DOWN_FLAG){
            if(m_handPos <= 2) {
                m_handPos++;
                newHandPos();
                Buttons::states.clear(Buttons::ALL_FLAG);
                continue;
            }
        }

        if(input==Buttons::START_FLAG){
            m_isRunning = false;
            State::stateFlags.set(GlobalStates::stateList[0]->getFlagName());
        }


        // Handle input and update positions
        switch(m_handPos){
            case 0: //if the hand is in position 0
                if (input == Buttons::LEFT_FLAG) {
                    if (m_selectedState == (GlobalStates::numberOfSettingsStates - 1))
                        m_selectedState = 0;
                    else if (m_selectedState == 0)
                        m_selectedState = (GlobalStates::numberOfSettingsStates - 1);
                    else
                        m_selectedState--;

                    m_canvas.updateText();
                    Buttons::states.clear(Buttons::ALL_FLAG);
                    break;
                }

                if(input == Buttons::RIGHT_FLAG){
                    if (m_selectedState == (GlobalStates::numberOfSettingsStates - 1))
                        m_selectedState = 0;
                    else if (m_selectedState == 0)
                        m_selectedState = (GlobalStates::numberOfSettingsStates - 1);
                    else
                        m_selectedState++;

                    m_canvas.updateText();
                    Buttons::states.clear(Buttons::ALL_FLAG);
                    break;
                }

                if (input==Buttons::A_FLAG){
                    State::stateFlags.set(GlobalStates::settingsList[m_selectedState]->getFlagName());
                }
                Buttons::states.clear(Buttons::ALL_FLAG);
                break;

            case 1:  //if the hand is in position 1
                if(input==Buttons::A_FLAG)
                    m_vibraOn = !m_vibraOn;
                m_canvas.drawHandPos1();
                Buttons::states.clear(Buttons::ALL_FLAG);
                break;

            case 2:
                if(input==Buttons::A_FLAG)
                    m_soundOn = !m_soundOn;
                m_canvas.drawHandPos2();
                Buttons::states.clear(Buttons::ALL_FLAG);
                break;
            default:
                break;
        }

        m_gameFlags.set(SCREEN_UPDATE_FLAG);
    }
}

void Settings::newHandPos() {

    switch(m_handPos)
    {
        case 0:
            m_canvas.updateText();
            m_pntrCanvas = &m_canvas.c_handPos0;
            break;
        case 1:
            m_canvas.drawHandPos1();
            m_pntrCanvas = &m_canvas.c_handPos1and2;
            break;
        case 2:
            m_canvas.drawHandPos2();
            m_pntrCanvas = &m_canvas.c_handPos1and2;
            break;
        default:
            break;
    }
    m_gameFlags.set(SCREEN_UPDATE_FLAG);

}

void Settings::update() {
    while (m_isRunning && m_gameFlags.wait_any(SCREEN_UPDATE_FLAG,osWaitForever)){
        m_displayManager.updateScreen(m_pntrCanvas);
    }
}

void Settings::game() {


}

void Settings::run() {
    m_isRunning = true;

    t_gameLogic = new Thread;
    t_gfx = new Thread;
    t_move = new Thread;

    m_pntrCanvas = &m_canvas.c_handPos0;

  //  t_gameLogic->start(callback(this, &Settings::game));
    t_gfx->start(callback(this, &Settings::update));
    t_move->start(callback(this, &Settings::handleInput));

    t_move->set_priority(osPriorityBelowNormal1);

    m_canvas.init();

    m_displayManager.updateScreen(&m_canvas.c_handPos0);
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
