#include "newHighscore.h"
#include "hardware/buttons.h"


void NewHighscore::handleInput() {

    if(Buttons::states.wait_any(Buttons::A_FLAG,osWaitForever, true) == Buttons::A_FLAG){
        m_isRunning = false;
        State::stateFlags.set(GlobalStates::stateList[INDEX_HIGHSCORE]->getFlagName());
    }
}

void NewHighscore::update() {
    while (m_isRunning && m_gameFlags.wait_any(SCREEN_UPDATE_FLAG, osWaitForever)) {
        m_displayManager.updateScreen(m_pntrCanvas);
    }
}

void NewHighscore::run() {
    using namespace rtos;
    using namespace mbed;
    m_isRunning = true;

    //start threads
    c_canvas = new NewHighscoreUi(this);
    t_gfx = new Thread;
    t_move = new Thread;
    t_dance = new Thread;
    c_canvas->drawText(m_score);
    m_pntrCanvas = &c_canvas->c_text;
    m_displayManager.updateScreen(m_pntrCanvas);

    t_gfx->start(callback(this, &NewHighscore::update));
    t_move->start(callback(this, &NewHighscore::handleInput));
    t_dance->start(callback(this,&NewHighscore::dance));
    t_move->set_priority(osPriorityBelowNormal);

   // m_gameFlags.set(SCREEN_UPDATE_FLAG);
}

void NewHighscore::stop() {
    m_isRunning = false;
    m_gameFlags.set(SCREEN_UPDATE_FLAG);
    Buttons::states.set(Buttons::A_FLAG);

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
    if(t_dance){
        t_dance->join();
        delete t_dance;
        t_dance = nullptr;
    }

    delete c_canvas; // Properly delete the canvas when stopping
    c_canvas = nullptr;

    m_gameFlags.clear(SCREEN_UPDATE_FLAG);
    Buttons::states.clear(Buttons::ALL_FLAG);

}

void NewHighscore::dance() {
    using namespace std::chrono;
    //change the animation of the dancing stick figure
    while(m_isRunning) {
        m_pntrCanvas = &c_canvas->c_dancingMan;
        for (int i = 0; i < 4; i++) {
            c_canvas->drawDance(i); //function in the UI class that prints out arms in the different positions
            m_gameFlags.set(SCREEN_UPDATE_FLAG);
            rtos::ThisThread::sleep_for(100ms);
        }
    }
}

NewHighscore::NewHighscore() : State("New Highscore") {}

void NewHighscore::setScore(int score) {
    NewHighscore::m_score = score;
}
