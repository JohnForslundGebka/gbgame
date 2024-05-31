#ifndef GBGAME_DISTANCEGAMEUI_H
#define GBGAME_DISTANCEGAMEUI_H
#include "ui/canvas.h"
#include "core/macros.h"
#include "core/state.h" // Include State but forward-declare DistanceGame


class DistanceGame; // Forward declaration

class DistanceGameUi {
public:

    explicit DistanceGameUi(DistanceGame *pGame);

    DistanceGame *parentState;
    Canvas c_main;

    void init();

    void drawScreen1();
    void drawScreen2();
    void drawScreen3(int score);
    void drawScreen4();
    void drawChallengeWinScreen(String &player1name, int player1score, String &player2name, int player2score);
    void drawChallengeLooseScreen();

private:


};

#endif //GBGAME_DISTANCEGAMEUI_H
