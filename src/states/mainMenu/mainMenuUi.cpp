#include "mainMenuUi.h"
#include "mainMenu.h"
#include "wifi/dataTransmit.h"


MainMenuUi::MainMenuUi(MainMenu *p) : c_canvas(128,128,0,0), parentState(p) {
}

void MainMenuUi::init() {

    DataTransmit &dataTransmit = DataTransmit::getInstance();
    updateTextFields();
    c_canvas.C.fillScreen(BLACK);

    c_canvas.C.setTextColor(WHITE);
    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextWrap(false);
    c_canvas.C.setCursor(18, 0);
    c_canvas.C.print("-GbgGame-");

    c_canvas.C.drawLine(1, 18, 128, 18, 0xFFFF);
    if(dataTransmit.wifiIsConnected) {
        c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, BLUE);
    } else {
        c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, WHITE);
    }

    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setTextSize(1);
    c_canvas.C.setCursor(21, 33);
    c_canvas.C.print(textField[3]);
    c_canvas.C.setCursor(21, 48);
    c_canvas.C.print(textField[4]);

    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextColor(GREEN);
    c_canvas.C.setCursor(7, 62);
    c_canvas.C.print(textField[0]);  //The selected state

    c_canvas.C.setTextColor(WHITE);
    c_canvas.C.setTextSize(1);
    c_canvas.C.setCursor(21, 88);
    c_canvas.C.print(textField[1]);

    c_canvas.C.setCursor(21, 105);
    c_canvas.C.print(textField[2]);
    c_canvas.C.print(textField[2]);
}

void MainMenuUi::drawText(){

    DataTransmit &dataTransmit = DataTransmit::getInstance();
     updateTextFields();
     c_canvas.C.fillScreen(BLACK);

    c_canvas.C.setTextColor(WHITE);
    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextWrap(false);
    c_canvas.C.setCursor(18, 0);
    c_canvas.C.print("-GbgGame-");

    c_canvas.C.drawLine(1, 18, 128, 18, 0xFFFF);
    if(dataTransmit.wifiIsConnected) {
        c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, BLUE);
    } else {
        c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, WHITE);
    }

    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setTextSize(1);
    c_canvas.C.setCursor(21, 33);
    c_canvas.C.print(textField[3]);
    c_canvas.C.setCursor(21, 48);
    c_canvas.C.print(textField[4]);

    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextColor(GREEN);
    c_canvas.C.setCursor(0, 62);
    c_canvas.C.print(textField[0]);  //The selected state

    c_canvas.C.setTextColor(WHITE);
    c_canvas.C.setTextSize(1);
    c_canvas.C.setCursor(21, 88);
    c_canvas.C.print(textField[1]);

    c_canvas.C.setCursor(21, 105);
    c_canvas.C.print(textField[2]);
}

void MainMenuUi::updateTextFields() {
    int counter = parentState->m_selectedState;

    for (int i = 0; i < 5; i++){
        textField[i] = GlobalStates::mainMenuList[counter]->m_stateName;

        if(counter == GlobalStates::numberOfMainMenuStates - 1)
            counter = 0;
        else
            counter++;
    }
}

void MainMenuUi::moveDown() {
     drawText();
}

void MainMenuUi::moveUp() {
    drawText();
}


