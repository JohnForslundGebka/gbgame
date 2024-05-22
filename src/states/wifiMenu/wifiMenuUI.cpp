#include "wifiMenuUI.h"
#include "wifiMenu.h"

WifiMenuUI::WifiMenuUI(WifiMenu *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {
}

void WifiMenuUI::init() {}

//Exit screen
void WifiMenuUI::drawScreen1() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.drawBitmap(0, 0, image_wifi_3_bars_bits, 19, 16, 0xFFFF);       //Draw wifi symbol


    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(45, 3);
    c_main.C.print("Wifi");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);                                //Draw line under "Wifi"

    //Draw menu options
    int cursorPosition = 35;
    c_main.C.setCursor(4, cursorPosition);
        
    for (int i = 0; i < 3; i++) {
        if (parentState->m_option == i) {
            c_main.C.setTextColor(GREEN);
        } 
        else {
            c_main.C.setTextColor(0x738E);
        }

        c_main.C.print(m_menuOptions[i]);
        cursorPosition += 30;
        c_main.C.setCursor(4, cursorPosition);
    }
}

void WifiMenuUI::drawScreen2() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.drawBitmap(0, 0, image_wifi_3_bars_bits, 19, 16, 0xFFFF);       //Draw wifi symbol


    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("Password");


    c_main.C.drawLine(0, 20, 128, 20, WHITE);    //Draw line under "Wifi"
    
    //Draw line under selected letter
    int selectedLetter = 9;                           
    for (int i = 0; i < parentState->m_selectedLetter; i++) {
        selectedLetter += 6;
    }
    c_main.C.drawLine(selectedLetter, 72, selectedLetter + 5, 72, 0xFFFF);



    //Draw password    
    c_main.C.setTextColor(GREEN);
    c_main.C.setTextSize(1);
    c_main.C.setCursor(10, 64);
    c_main.C.print(parentState->m_password);  
}

void WifiMenuUI::drawScreen3() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.drawBitmap(0, 0, image_wifi_3_bars_bits, 19, 16, 0xFFFF);       //Draw wifi symbol


    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("Set name");


    c_main.C.drawLine(0, 20, 128, 20, WHITE);    
    
    int selectedLetter = 37;                           //Draw line under "Wifi"
    
    for (int i = 0; i < parentState->m_selectedLetter; i++) {
        selectedLetter += 12;
    }

    c_main.C.drawBitmap(selectedLetter, 38, image_music_fast_backward_1_bits, 16, 17, 0xFFFF);
    c_main.C.drawBitmap(selectedLetter, 88, image_music_fast_backward_bits, 16, 17, 0xFFFF);

    //Draw username    
    c_main.C.setTextColor(GREEN);
    c_main.C.setCursor(40, 64);
    c_main.C.print(parentState->m_username);  
}


