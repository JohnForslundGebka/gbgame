#include "highScore.h"
#include "highScoreUi.h"
#include "hardware/buttons.h"
#include "functionality/scores.h"
#include "wifi/dataTransmit.h"

void HighScore::handleInput() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    while(m_isRunning){
        uint32_t input = Buttons::states.wait_any(Buttons::LEFT_FLAG | Buttons::RIGHT_FLAG | Buttons::START_FLAG,osWaitForever,false);

        if (!m_isRunning) break;
        //debounce logic
        ThisThread::sleep_for(50ms);
        if(Buttons::states.get() == 0)
            continue;

        switch(input){
            case Buttons::LEFT_FLAG:
                Buttons::states.clear(Buttons::LEFT_FLAG);
                //makes sure the m_selectedState does not go "out of bounds"
                Buttons::states.clear(Buttons::LEFT_FLAG);
                if (m_selectedState == 0) {
                    // Wrap around to the last index if at the first index
                    m_selectedState = GlobalStates::numberOfGameStates - 1;
                } else {
                    // Otherwise, just decrement normally
                    m_selectedState--;
                }
                c_canvas->drawHighscore();
                m_gameFlags.set(SCREEN_UPDATE_FLAG);
                break;

            case Buttons::RIGHT_FLAG:
                Buttons::states.clear(Buttons::RIGHT_FLAG);
                if (m_selectedState == GlobalStates::numberOfGameStates - 1) {
                    // Wrap around to the first index if at the last index
                    m_selectedState = 0;
                } else {
                    // Otherwise, just increment normally
                    m_selectedState++;
                }
                c_canvas->drawHighscore();
                m_gameFlags.set(SCREEN_UPDATE_FLAG);
                break;

            case Buttons::START_FLAG:
                m_isRunning = false;
                State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
                break;

        }

    }


}

void HighScore::update() {
    while (m_isRunning && m_gameFlags.wait_any(SCREEN_UPDATE_FLAG, osWaitForever)) {
        m_displayManager.updateScreen(&c_canvas->c_main);
    }
}

void HighScore::run() {
    using namespace rtos;
    using namespace mbed;
    m_isRunning = true;
    c_canvas = new HighScoreUi(this);
    //if the unit is connected to Wi-Fi, update the leaderboard with the values from the database
    DataTransmit &wifi = DataTransmit::getInstance();
    if(!wifi.wifiIsConnected){
        c_canvas->drawNotConnectedScreen(); //draw wifi message screen
        m_displayManager.updateScreen(&c_canvas->c_main);
        ThisThread::sleep_for(std::chrono::seconds(3));
        State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
    }

    t_gfx = new Thread;
    t_move = new Thread;

    t_gfx->start(callback(this, &HighScore::update));
    t_move->start(callback(this, &HighScore::handleInput));
    t_move->set_priority(osPriorityBelowNormal);
    c_canvas->drawHighscore();
    m_gameFlags.set(SCREEN_UPDATE_FLAG);
}

void HighScore::stop() {
    m_isRunning = false;
    m_gameFlags.set(SCREEN_UPDATE_FLAG);
    Buttons::states.set(Buttons::LEFT_FLAG);

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

    delete c_canvas; // Properly delete the canvas when stopping
    c_canvas = nullptr;

    m_gameFlags.clear(ADVANCE_GAME_FLAG);
    Buttons::states.clear(Buttons::ALL_FLAG);

}

HighScore::HighScore() : State("Highscore") {}
