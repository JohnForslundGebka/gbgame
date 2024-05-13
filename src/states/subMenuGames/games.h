#ifndef GBGAME_GAMES_H
#define GBGAME_GAMES_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "states/globalStates.h"

class Games : public State {
public:

    int m_selectedState{};

    void handleInput() override;

    void update() override;

    void run() override;

    void stop() override;

    explicit Games();
private:
    Thread* t_gfx;
    Thread* t_move;
};

#endif //GBGAME_GAMES_H
