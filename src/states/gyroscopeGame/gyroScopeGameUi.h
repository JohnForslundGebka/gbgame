#ifndef GBGAME_GYROSCOPEGAMEUI_H
#define GBGAME_GYROSCOPEGAMEUI_H
#include "ui/canvas.h"
#include "core/macros.h"
#include "core/state.h" // Include State but forward-declare GyroscopeGame

class GyroscopeGame; // Forward declaration

class GyroScopeGameUi {
public:
    explicit GyroScopeGameUi(GyroscopeGame *pGame);
    GyroscopeGame *parentState;
    Canvas c_main;

    void drawScoreAndTime();
    void draw();
    void drawFallingBalls(int x, int y, uint16_t color);
    void drawPlayerBall();
    void drawGameOver();

    void drawCheckingSCore();
    void drawChallengeWinScreen(String &player1name, int player1score, String &player2name, int player2score);
    void drawChallengeLoseScreen(String &player1name, int player1score, String &player2name, int player2score);
    void drawNoHighcoreScreen(int score);

private:

};


#endif //GBGAME_GYROSCOPEGAMEUI_H
