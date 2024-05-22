#ifndef GBGAME_NEWHIGHSCOREUI_H
#define GBGAME_NEWHIGHSCOREUI_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"

class NewHighscore;

class NewHighscoreUi {
public:
    NewHighscore* parentState;
    Canvas c_text;
    Canvas c_dancingMan;

    explicit NewHighscoreUi(NewHighscore *parentState);

    void drawText(int score);
    void drawDance(int pose);

};


#endif //GBGAME_NEWHIGHSCOREUI_H
