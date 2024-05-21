#ifndef GBGAME_HIGHSCORE_H
#define GBGAME_HIGHSCORE_H
#include "core/state.h"

class HighScore : public State{
public:
    void handleInput() override;

    void update() override;

    void run() override;

    void stop() override;

    explicit HighScore();
};


#endif //GBGAME_HIGHSCORE_H
