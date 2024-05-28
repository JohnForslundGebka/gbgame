#ifndef GBGAME_MULTIPLAYER_UI_H
#define GBGAME_MULTIPLAYER_UI_H
#include "ui/canvas.h"
#include "core/macros.h"
#include "core/state.h" 

class MultiplayerMenu; // Forward declaration

class MultiplayerMenuUI {
public:

    explicit MultiplayerMenuUI(MultiplayerMenu *pGame);

    MultiplayerMenu *parentState;
    Canvas c_main;

    void init();
    
    void drawScreen1();           // Draws the menu options
    void drawScreen2();           // Draws lobby screen
    void drawScreen3();           // Draws new screen
    void drawScreen4();           // Draws my games screen

    char m_menuOptions[3][12] = {
        "   Lobby",
        "    New",
        " My games"
    };
 
private:
                                  

};

#endif //GBGAME_MULTIPLAYER_UI_H
