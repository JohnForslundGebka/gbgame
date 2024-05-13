#include "settingsUi.h"
#include "settings.h"

SettingsUi::SettingsUi(Settings *p) : c_canvas(128,128,0,0), parentState(p){

}

void SettingsUi::init() {

    updateTextFields();

    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextWrap(false);
    c_canvas.C.setCursor(4, 0);
    c_canvas.C.print("-Settings-");
    c_canvas.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_canvas.C.setTextColor(0xAD55);
    c_canvas.C.setCursor(40, 29);
    c_canvas.C.print(textField[0]);
    c_canvas.C.drawBitmap(56, 49, image_hand_notice_bits_up, 11, 16, 0x555);
    c_canvas.C.drawBitmap(95, 28, image_music_fast_forward_bits, 17, 16, 0xFFFF);
    c_canvas.C.drawBitmap(14, 28, image_music_fast_backward_bits, 17, 16, 0xFFFF);
    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setCursor(7, 77);
    c_canvas.C.print("Vibra");
    c_canvas.C.setCursor(6, 100);
    c_canvas.C.print("Sound");
    c_canvas.C.drawBitmap(74, 77, image_music_record_button_bits, 15, 16, 0xFFFF);
    c_canvas.C.drawBitmap(74, 99, image_music_record_button_bits, 15, 16, 0xFFFF);
    c_canvas.C.fillCircle(81, 106, 2, RED);
    c_canvas.C.fillCircle(81, 84, 2, RED);
}

void SettingsUi::updateText() {
    c_canvas.C.fillScreen(BLACK);

    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextWrap(false);
    c_canvas.C.setCursor(4, 0);
    c_canvas.C.print("-Settings-");
    c_canvas.C.drawLine(1, 18, 128, 18, 0xFFFF);


    c_canvas.C.setTextColor(0xAD55);
    c_canvas.C.setCursor(40, 29);
    c_canvas.C.print(textField[parentState->m_selectedState]);
    c_canvas.C.drawBitmap(56, 49, image_hand_notice_bits_up, 11, 16, 0x555);
    c_canvas.C.drawBitmap(95, 28, image_music_fast_forward_bits, 17, 16, 0xFFFF);
    c_canvas.C.drawBitmap(14, 28, image_music_fast_backward_bits, 17, 16, 0xFFFF);
    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setCursor(7, 77);
    c_canvas.C.print("Vibra");
    c_canvas.C.setCursor(6, 100);
    c_canvas.C.print("Sound");
    c_canvas.C.drawBitmap(74, 77, image_music_record_button_bits, 15, 16, 0xFFFF);
    c_canvas.C.drawBitmap(74, 99, image_music_record_button_bits, 15, 16, 0xFFFF);
    c_canvas.C.fillCircle(81, 106, 2, RED);
    c_canvas.C.fillCircle(81, 84, 2, RED);
}

void SettingsUi::updateTextFields() {

    int counter = parentState->m_selectedState;

    textField[0] = "WiFi";
    textField[1] = "Account";
    textField[2] = "Test";

//    for (int i = 0; i < 3; i++){
//        textField[i] = GlobalStates::settingsList[counter]->m_stateName;
//
//        if(counter == (GlobalStates::numberOfSettingsStates - 1))
//            counter = 0;
//        else
//            counter++;
//    }
}
