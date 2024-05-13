#ifndef GBGAME_GAMESUI_H
#define GBGAME_GAMESUI_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "states/globalStates.h"

class Games; //forward declaration

class GamesUI {
public:

    Canvas c_canvas;
    Games *parentState;

    explicit GamesUI(Games *p);

    String textField[5];

    void init();
    void updateTextFields();
    void draw();

};

#endif //GBGAME_GAMESUI_H
