#include "settingsUi.h"
#include "settings.h"

SettingsUi::SettingsUi(Settings *p) : c_canvas(128,128,0,0), parentState(p){

}

void SettingsUi::init() {
    updateTextFields();

    c_canvas.C.setTextColor(WHITE);
    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextWrap(false);
    c_canvas.C.setCursor(18, 0);
    c_canvas.C.print("-Settings-"); //title

    c_canvas.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, 0xFFEA);

    c_canvas.C.drawBitmap(2, 64, image_hand_notice_bits, 16, 11, 0x555);
    //center choice
    c_canvas.C.setTextColor(RED);
    c_canvas.C.setCursor(27, 62);
    c_canvas.C.print(textField[0]);


    c_canvas.C.setTextColor(WHITE);
    c_canvas.C.setTextSize(1);
    c_canvas.C.setCursor(41, 88);
    c_canvas.C.print(textField[1]);
    c_canvas.C.setCursor(41, 48);
    c_canvas.C.print(textField[4]);
    c_canvas.C.setCursor(41, 33);
    c_canvas.C.print(textField[3]);
    c_canvas.C.setCursor(41, 105);
    c_canvas.C.print(textField[2]);
}

void SettingsUi::draw() {
    updateTextFields();
    c_canvas.C.fillScreen(BLACK);

    textField[0] = textField[4];

    c_canvas.C.setTextColor(WHITE);
    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextWrap(false);
    c_canvas.C.setCursor(18, 0);
    c_canvas.C.print("-Settings-");

    c_canvas.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, 0xFFEA);
    c_canvas.C.drawBitmap(2, 64, image_hand_notice_bits, 16, 11, 0x555);


    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setTextSize(1);
    c_canvas.C.setCursor(41, 33);
    c_canvas.C.print(textField[3]);
    c_canvas.C.setCursor(41, 48);
    c_canvas.C.print(textField[4]);

    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextColor(RED);
    c_canvas.C.setCursor(27, 62);
    c_canvas.C.print(textField[0]);  //The selected state

    c_canvas.C.setTextColor(WHITE);
    c_canvas.C.setTextSize(1);
    c_canvas.C.setCursor(41, 88);
    c_canvas.C.print(textField[1]);

    c_canvas.C.setCursor(41, 105);
    c_canvas.C.print(textField[2]);
}

void SettingsUi::updateTextFields() {
    int counter = parentState->m_selectedState;

    for (int i = 0; i < 5; i++){
        textField[i] = GlobalStates::settingsList[counter]->m_stateName;

        if(counter == (GlobalStates::numberOfSettingsStates - 1))
            counter = 0;
        else
            counter++;
    }
}
