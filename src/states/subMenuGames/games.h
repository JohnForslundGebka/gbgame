#ifndef GBGAME_GAMES_H
#define GBGAME_GAMES_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "states/subMenuGames/gamesUi.h"
#include "states/globalStates.h"
#include "hardware/buttons.h"

class Games : public State {
public:
    void handleInput() override;

    void update() override;

    void run() override;

    void stop() override;

    explicit Games();
    int m_selectedState{};
private:
    Canvas *m_pntrCanvas{};
    GamesUI *m_canvas = nullptr;
    Thread* t_gfx = nullptr;
    Thread* t_move= nullptr;
    class EventFlags m_gameFlags;
};

#endif //GBGAME_GAMES_H
