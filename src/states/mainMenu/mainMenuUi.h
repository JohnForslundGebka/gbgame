#ifndef GBGAME_MAINMENUUI_H
#define GBGAME_MAINMENUUI_H
#include "ui/canvas.h"
#include "ui/images.h"

class MainMenuUi {
public:
    Canvas c_hand;
    Canvas c_canvas;

    MainMenuUi();

    void init();


    String stateTitles[5];

private:
    void moveUp();
    void moveDown();


};
#endif //GBGAME_MAINMENUUI_H
