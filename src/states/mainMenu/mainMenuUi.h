#ifndef GBGAME_MAINMENUUI_H
#define GBGAME_MAINMENUUI_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "states/globalStates.h"


class MainMenu; // Forward declaration

class MainMenuUi {
public:
    Canvas c_canvas;

    explicit MainMenuUi(MainMenu *parentState);

    void init();

    String textField[5];

    MainMenu *parentState;
    void drawText();
    void updateTextFields();

    void moveDown();
    void moveUp();


private:

};
#endif //GBGAME_MAINMENUUI_H
