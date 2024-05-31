#ifndef GBGAME_multiplayerMenuUI_H
#define GBGAME_multiplayerMenuUI_H
#include "ui/canvas.h"
#include "core/macros.h"
#include "functionality/challenge.h"
//#include "core/state.h"

class MultiplayerMenu; // Forward declaration

class MultiplayerMenuUI {
public:

    explicit MultiplayerMenuUI(MultiplayerMenu *pGame);

    MultiplayerMenu *parentState;
    Canvas c_main;

    void init();
    
    void drawScreen1();           // Draws the menu options
    void drawLobbyList();           // Draws lobby screen
    void drawScreen3();           // Draws new screen
    void drawScreen4();           // Draws my games screen
    void drawNotConnectedScreen();
    void drawWaitingScreen();
    void drawChallengeInfo(Challenge* challenge);

    const String m_menuOptions[3] = {
        "   Lobby",
        "    New",
        " My games"
    };
 
private:
                                  

};

#endif //GBGAME_multiplayerMenuUI_H
