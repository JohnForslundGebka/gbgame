#include "wifiMenuUI.h"
#include "wifiMenu.h"

WifiMenuUI::WifiMenuUI(WifiMenu *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {
}

void WifiMenuUI::init() {}

//Exit screen
void WifiMenuUI::drawScreen1() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    //Draw wifi symbol
    if(parentState->wifi.wifiIsConnected){
    c_main.C.drawBitmap(0, 0, image_wifi_3_bars_bits, 19, 16, BLUE);
    } else {
        c_main.C.drawBitmap(0, 0, image_wifi_3_bars_bits, 19, 16, WHITE);
    }


    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(45, 3);
    c_main.C.print("Wifi");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);                                //Draw line under "Wifi"

    //Draw menu options
    int cursorPosition = 31;
    c_main.C.setCursor(4, cursorPosition);
        
    int index = 0; // Initialize an index to use for comparison
    for (const auto& menuOption : m_menuOptions) {  // Use range-based loop
        if (parentState->m_option == index) {
            c_main.C.setTextColor(GREEN);
        } else {
            c_main.C.setTextColor(0x738E);
        }

        c_main.C.print(menuOption);   // Print the current menu option
        cursorPosition += 25;
        c_main.C.setCursor(4, cursorPosition);  // Update the cursor position for the next option

        index++;  // Increment the index manually
    }
}

//password screen
void WifiMenuUI::drawScreen2() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.drawBitmap(0, 0, image_wifi_3_bars_bits, 19, 16, 0xFFFF);       //Draw wifi symbol

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("Password");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);    //Draw line under "Wifi"

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(1);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(4, 30);
    c_main.C.print("A:save password");
    c_main.C.setCursor(4, 45);
    c_main.C.print("B: go back");
    
    //Draw line under selected letter
    int selectedLetter = 9;                           
    for (int i = 0; i < parentState->m_selectedLetter; i++) {
        selectedLetter += 6;
    }
    c_main.C.drawLine(selectedLetter, 72, selectedLetter + 5, 72, 0xFFFF);

    //Draw password    
    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(1);
    c_main.C.setCursor(10, 64);
    c_main.C.print(parentState->m_password);  
}

//show networks screen
void WifiMenuUI::drawScreenNetworks() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(24, 3);
    c_main.C.print("Networks");

    c_main.C.drawLine(0, 20, 128, 20, WHITE);    //Draw line under "Networks"
    
        //Draw list of networks   
    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(1);

    int cursorPosition = 30; 
    c_main.C.setCursor(1, cursorPosition);

    for (int i = 0; i < parentState->m_networkList.size(); i++) {

        //Change the color to green when printing selected option
        if (parentState->m_selectedNetwork == i) {
            c_main.C.setTextColor(GREEN);
            
        } else {
            c_main.C.setTextColor(WHITE);
        }
    
        c_main.C.print(parentState->m_networkList[i]);
        
        //Update cursor position
        cursorPosition += 9;
        c_main.C.setCursor(1, cursorPosition);
    } 

    
}

//set name screen
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
    c_main.C.setTextColor(0xFABF);
    c_main.C.setCursor(40, 64);
    c_main.C.print(parentState->m_username);  
}

//connection screen
void WifiMenuUI::drawScreen4() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(WHITE);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(3, 64);
    c_main.C.print("Connecting..");
}

void WifiMenuUI::drawNetworks() {
    c_main.C.fillScreen(BLACK);
    c_main.C.drawBitmap(44, 47, image_Restoring_bits, 38, 32, 0xFFFF);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(1);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(10, 89);
    c_main.C.print("Searching for wifi");
    c_main.C.drawBitmap(56, 20, image_hour_glass_75_bits, 11, 16, 0xFFFF);
}

