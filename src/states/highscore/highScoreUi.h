#ifndef GBGAME_HIGHSCOREUI_H
#define GBGAME_HIGHSCOREUI_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "functionality/scores.h"

class HighScore; // Forward declaration

class HighScoreUi {
private:
 //   Scores &scores = Scores::getInstance();
    HighScore *parentState;
    uint32_t currentSelectedGame = 0;

public:
    Canvas c_main;
    explicit HighScoreUi(HighScore *p);
    void drawHighscore();
    void drawNotConnectedScreen()
};


#endif //GBGAME_HIGHSCOREUI_H
