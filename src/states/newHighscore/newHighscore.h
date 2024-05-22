#ifndef GBGAME_NEWHIGHSCORE_H
#define GBGAME_NEWHIGHSCORE_H
#include "core/state.h"
#include "newHighscoreUi.h"

class NewHighscore : public State{
public:
    void handleInput() override;

    void update() override;

    void dance();

    void run() override;

    void stop() override;

    explicit NewHighscore();
private:
    NewHighscoreUi* c_canvas = nullptr;

    rtos::Thread* t_gfx = nullptr;
    rtos::Thread* t_move= nullptr;
    rtos::Thread* t_dance = nullptr;
    class rtos::EventFlags m_gameFlags;
};


#endif //GBGAME_NEWHIGHSCORE_H
