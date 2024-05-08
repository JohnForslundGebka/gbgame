#ifndef GBGAME_MAINMENUUI_H
#define GBGAME_MAINMENUUI_H
#include "ui/canvas.h"
#include "ui/images.h"

class MainMenuUi {
public:
    Canvas c_hand;
    Canvas c_text;

    MainMenuUi();

    void init();

private:

    void drawHand();
    void drawText();

};
#endif //GBGAME_MAINMENUUI_H
