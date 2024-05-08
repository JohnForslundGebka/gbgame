#ifndef GBGAME_DISTANCEGAMEUI_H
#define GBGAME_DISTANCEGAMEUI_H
#include "ui/canvas.h"
#include "core/macros.h"
#include "distanceGame.h"

class DistanceGameUi {
public:

    DistanceGameUi(DistanceGame *pGame);

    DistanceGame *parentState;
    Canvas c_main;



    void init();

    void drawScreen1();
    void drawScreen2();
    void drawScreen3();

private:


};

#endif //GBGAME_DISTANCEGAMEUI_H
