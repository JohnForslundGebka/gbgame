#ifndef GBGAME_WIFI_MENU_UI_H
#define GBGAME_WIFI_MENU_UI_H
#include "ui/canvas.h"
#include "core/macros.h"
#include "core/state.h" // Include State but forward-declare DistanceGame

class WifiMenu; // Forward declaration

class WifiMenuUI {
public:

    explicit WifiMenuUI(WifiMenu *pGame);

    WifiMenu *parentState;
    Canvas c_main;

    void init();
    
    void drawScreen3();           // Draws the exit/finish screen

private:

};

#endif //GBGAME_WIFI_MENU_UI_H
