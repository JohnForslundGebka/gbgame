#include "multiplayerMenuUI.h"
#include "multiplayerMenu.h"

MultiplayerMenuUI::MultiplayerMenuUI(MultiplayerMenu *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {
}

void MultiplayerMenuUI::init() {}

//Exit screen
void MultiplayerMenuUI::drawScreen1() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(1, 3);
    c_main.C.print("Multiplayer");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);                                //Draw line under "Wifi"

    //Draw menu options
    int cursorPosition = 31;
    c_main.C.setCursor(4, cursorPosition);
        
    for (int i = 0; i < 4; i++) {
        //Sets color of selected option
        c_main.C.setTextColor(*parentState->m_optionPtr == i ? GREEN : 0x738E);

        c_main.C.print(m_menuOptions[i]);
        cursorPosition += 25;
        c_main.C.setCursor(4, cursorPosition);
    }
}

//password screen
void MultiplayerMenuUI::drawScreen2() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("Lobby");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);   

    int cursorPosition = 30;

    for (int i = 0; i < parentState -> m_lobbyList.size(); i++) {
        //Sets color of selected option
        c_main.C.setTextColor(*parentState->m_optionPtr == i ? GREEN : 0x738E);

        c_main.C.setCursor(4, cursorPosition);
        c_main.C.print(parentState -> m_lobbyList[i]);
        
        cursorPosition += 25;
    }
 

}

void MultiplayerMenuUI::drawScreen3() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(20, 3);
    c_main.C.print("New Game");
    c_main.C.drawLine(0, 20, 128, 20, WHITE);    

    c_main.C.setTextColor(GREEN);

    c_main.C.setCursor(20, 40);
    c_main.C.print("Press A");
    c_main.C.setCursor(8, 65);
    c_main.C.print("and choose");
    c_main.C.setCursor(25, 90);
    c_main.C.print("a game! ");
    
}

void MultiplayerMenuUI::drawScreen4() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("My games");
    c_main.C.drawLine(0, 20, 128, 20, WHITE);    

    int cursorPosition = 30;

    for (int i = 0; i < parentState -> m_myGamesList.size(); i++) {
        //Sets color of selected option
        c_main.C.setTextColor(*parentState->m_optionPtr == i ? GREEN : 0x738E);

        c_main.C.setCursor(4, cursorPosition);
        c_main.C.print(parentState -> m_myGamesList[i]);
        
        cursorPosition += 25;
    }
    
}




