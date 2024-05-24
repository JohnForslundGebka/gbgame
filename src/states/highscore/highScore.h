#ifndef GBGAME_HIGHSCORE_H
#define GBGAME_HIGHSCORE_H
#include "core/state.h"
#include "highScoreUi.h"

class HighScore : public State{
public:
    void handleInput() override;

    void update() override;

    void run() override;

    void stop() override;

    explicit HighScore();

    int m_selectedState = 0;
private:
    HighScoreUi *c_canvas = nullptr;

    rtos::Thread* t_gfx = nullptr;
    rtos::Thread* t_move= nullptr;
    class rtos::EventFlags m_gameFlags;
};


#endif //GBGAME_HIGHSCORE_H
