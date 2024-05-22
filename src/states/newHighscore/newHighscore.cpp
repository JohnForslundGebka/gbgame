#include "newHighscore.h"

void NewHighscore::handleInput() {

}

void NewHighscore::update() {

}

void NewHighscore::run() {
    using namespace rtos;
    using namespace mbed;
    m_isRunning = true;

    c_canvas = new NewHighscoreUi(this);
    t_gfx = new Thread;
    t_move = new Thread;

    t_gfx->start(callback(this, &NewHighscore::update));
    t_move->start(callback(this, &NewHighscore::handleInput));
    t_move->set_priority(osPriorityBelowNormal);
}

void NewHighscore::stop() {

}

void NewHighscore::dance() {

}

NewHighscore::NewHighscore() : State("New Highscore") {}
