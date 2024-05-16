#ifndef GBGAME_MIC_GAMEUI_H
#define GBGAME_MIC_GAMEUI_H
#include "ui/canvas.h"
#include "core/macros.h"
#include "core/state.h" // Include State but forward-declare DistanceGame

class MicGame; // Forward declaration

class MicGameUI {
public:

    explicit MicGameUI(MicGame *pGame);

    MicGame *parentState;
    Canvas c_main;

    void init();

    void drawScreen1();

private:


};

#endif //GBGAME_MIC_GAMEUI_H
