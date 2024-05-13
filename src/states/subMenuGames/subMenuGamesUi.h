#ifndef GBGAME_SUBMENUGAMESUI_H
#define GBGAME_SUBMENUGAMESUI_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "states/globalStates.h"

class Game; //forward declaration

class SubMenuGamesUi {
public:

    Canvas c_canvas;
    Game *parrentState;

    explicit SubMenuGamesUi(Game *p);

    String textField[5];

    void init();
    void updateTextFields();
    void draw();



};

#endif //GBGAME_SUBMENUGAMESUI_H
