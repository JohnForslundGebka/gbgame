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
    c_main.C.setCursor(45, 3);
    c_main.C.print("Lobby");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);                                //Draw line under "Wifi"

    //Draw menu options
    int cursorPosition = 31;
    c_main.C.setCursor(4, cursorPosition);
        
    for (int i = 0; i < 4; i++) {
        if (parentState->m_option == i) {
            c_main.C.setTextColor(GREEN);
        } 
        else {
            c_main.C.setTextColor(0x738E);
        }

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
    c_main.C.print("New");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);    //Draw line under "Wifi"
 
    // //Draw password    
    // c_main.C.setTextColor(WHITE);
    // c_main.C.setTextSize(1);
    // c_main.C.setCursor(10, 64);
    // c_main.C.print(parentState->m_password);  
}

//show networks screen
// void MultiplayerMenuUI::drawScreenNetworks() {
//     c_main.C.fillRect(0, 0, 128, 128, BLACK);

//     c_main.C.setTextColor(WHITE);
//     c_main.C.setTextSize(2);
//     c_main.C.setTextWrap(false);
//     c_main.C.setCursor(24, 3);
//     c_main.C.print("Networks");

//     c_main.C.drawLine(0, 20, 128, 20, WHITE);    //Draw line under "Networks"
    
//     int cursorPosition = 30; 

//         //Draw list of networks   
//     c_main.C.setTextColor(WHITE);
//     c_main.C.setTextSize(1);

//     c_main.C.setCursor(1, cursorPosition);

//     for (int i = 0; i < parentState->m_networkList.size(); i++) {

//         //Change the color to green when printing selected option
//         if (parentState->m_selectedNetwork == i) {
//             c_main.C.setTextColor(GREEN);
//         }
//         else {
//             c_main.C.setTextColor(WHITE);

//         }
    
//         c_main.C.print(parentState->m_networkList[i]);
        
//         //Update cursor position
//         cursorPosition += 9;
//         c_main.C.setCursor(1, cursorPosition);
//     } 
// }

//set name screen

void MultiplayerMenuUI::drawScreen3() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("My games");


    c_main.C.drawLine(0, 20, 128, 20, WHITE);    
    
    int selectedLetter = 37;                           //Draw line under "Wifi"

}

void MultiplayerMenuUI::drawScreen4() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("My games");


    c_main.C.drawLine(0, 20, 128, 20, WHITE);    
    
    int selectedLetter = 37;                           //Draw line under "Wifi"

}




