#include "settingsUi.h"
#include "settings.h"

SettingsUi::SettingsUi(Settings *p) : c_handPos0(128, 128, 0, 0),c_handPos1and2(128,128,0,0), parentState(p){

}

void SettingsUi::init() {

    updateTextFields();

    c_handPos0.C.setTextColor(0xFFFF);
    c_handPos0.C.setTextSize(2);
    c_handPos0.C.setTextWrap(false);
    c_handPos0.C.setCursor(4, 0);
    c_handPos0.C.print("-Settings-");
    c_handPos0.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_handPos0.C.setTextColor(0xAD55);
    c_handPos0.C.setCursor(40, 29);
    c_handPos0.C.print(textField[0]);
    c_handPos0.C.drawBitmap(56, 49, image_hand_notice_bits_up, 11, 16, 0x555);
    c_handPos0.C.drawBitmap(95, 28, image_music_fast_forward_bits, 17, 16, 0xFFFF);
    c_handPos0.C.drawBitmap(14, 28, image_music_fast_backward_bits, 17, 16, 0xFFFF);
    c_handPos0.C.setTextColor(0xFFFF);
    c_handPos0.C.setCursor(7, 77);
    c_handPos0.C.print("Vibra");
    c_handPos0.C.setCursor(6, 100);
    c_handPos0.C.print("Sound");
    c_handPos0.C.drawBitmap(74, 77, image_music_record_button_bits, 15, 16, 0xFFFF);
    c_handPos0.C.drawBitmap(74, 99, image_music_record_button_bits, 15, 16, 0xFFFF);
    c_handPos0.C.fillCircle(81, 106, 2, RED);
    c_handPos0.C.fillCircle(81, 84, 2, RED);

    c_handPos1and2.C.setTextColor(0xFFFF);
    c_handPos1and2.C.setTextSize(2);
    c_handPos1and2.C.setTextWrap(false);
    c_handPos1and2.C.setCursor(4, 0);
    c_handPos1and2.C.print("-Settings-");
    c_handPos1and2.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_handPos1and2.C.setTextColor(0xAD55);
    c_handPos1and2.C.setCursor(40, 29);
    c_handPos1and2.C.print(textField[0]);
    c_handPos1and2.C.drawBitmap(97, 77, image_hand_notice_bits_left, 16, 11, 0x555);
    c_handPos1and2.C.drawBitmap(95, 28, image_music_fast_forward_bits, 17, 16, 0xFFFF);
    c_handPos1and2.C.drawBitmap(14, 28, image_music_fast_backward_bits, 17, 16, 0xFFFF);
    c_handPos1and2.C.setTextColor(0xFFFF);
    c_handPos1and2.C.setCursor(7, 77);
    c_handPos1and2.C.print("Vibra");
    c_handPos1and2.C.setCursor(6, 100);
    c_handPos1and2.C.print("Sound");
    c_handPos1and2.C.drawBitmap(74, 77, image_music_record_button_bits, 15, 16, 0xFFFF);

    if(parentState->m_soundOn){
        c_handPos1and2.C.fillCircle(81, 106, 2, GREEN);
    } else {
        c_handPos1and2.C.fillCircle(81, 106, 2, RED);
    }

    if(parentState->m_vibraOn){
        c_handPos1and2.C.fillCircle(81, 84, 2, GREEN);
    } else{
        c_handPos1and2.C.fillCircle(81, 84, 2, RED);
    }
    c_handPos1and2.C.drawBitmap(74, 99, image_music_record_button_bits, 15, 16, 0xFFFF);

}

void SettingsUi::updateText() {
    c_handPos0.C.fillScreen(BLACK);

    c_handPos0.C.setTextColor(WHITE);
    c_handPos0.C.setTextSize(2);
    c_handPos0.C.setTextWrap(false);
    c_handPos0.C.setCursor(4, 0);
    c_handPos0.C.print("-Settings-");
    c_handPos0.C.drawLine(1, 18, 128, 18, 0xFFFF);


    c_handPos0.C.setTextColor(0xAD55);
    c_handPos0.C.setCursor(40, 29);
    c_handPos0.C.print(textField[parentState->m_selectedState]);
    c_handPos0.C.drawBitmap(56, 49, image_hand_notice_bits_up, 11, 16, 0x555);
    c_handPos0.C.drawBitmap(95, 28, image_music_fast_forward_bits, 17, 16, 0xFFFF);
    c_handPos0.C.drawBitmap(14, 28, image_music_fast_backward_bits, 17, 16, 0xFFFF);
    c_handPos0.C.setTextColor(0xFFFF);
    c_handPos0.C.setCursor(7, 77);
    c_handPos0.C.print("Vibra");
    c_handPos0.C.setCursor(6, 100);
    c_handPos0.C.print("Sound");
    c_handPos0.C.drawBitmap(74, 77, image_music_record_button_bits, 15, 16, 0xFFFF);
    c_handPos0.C.drawBitmap(74, 99, image_music_record_button_bits, 15, 16, 0xFFFF);

    if(parentState->m_soundOn){
        c_handPos1and2.C.fillCircle(81, 106, 2, GREEN);
    } else {
        c_handPos1and2.C.fillCircle(81, 106, 2, RED);
    }

    if(parentState->m_vibraOn){
        c_handPos1and2.C.fillCircle(81, 84, 2, GREEN);
    } else{
        c_handPos1and2.C.fillCircle(81, 84, 2, RED);
    }
}

void SettingsUi::updateTextFields() {

    //temporary code used for testing

  //  int counter = parentState->m_selectedState;

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

void SettingsUi::drawHandPos1() {

    c_handPos1and2.C.fillScreen(BLACK);
    c_handPos1and2.C.setTextColor(0xFFFF);
    c_handPos1and2.C.setTextSize(2);
    c_handPos1and2.C.setTextWrap(false);
    c_handPos1and2.C.setCursor(4, 0);
    c_handPos1and2.C.print("-Settings-");
    c_handPos1and2.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_handPos1and2.C.setTextColor(0xAD55);
    c_handPos1and2.C.setCursor(40, 29);
    c_handPos1and2.C.print(textField[parentState->m_selectedState]);
    c_handPos1and2.C.drawBitmap(97, 77, image_hand_notice_bits_left, 16, 11, 0x555);
    c_handPos1and2.C.drawBitmap(95, 28, image_music_fast_forward_bits, 17, 16, 0xFFFF);
    c_handPos1and2.C.drawBitmap(14, 28, image_music_fast_backward_bits, 17, 16, 0xFFFF);
    c_handPos1and2.C.setTextColor(0xFFFF);
    c_handPos1and2.C.setCursor(7, 77);
    c_handPos1and2.C.print("Vibra");
    c_handPos1and2.C.setCursor(6, 100);
    c_handPos1and2.C.print("Sound");
    c_handPos1and2.C.drawBitmap(74, 77, image_music_record_button_bits, 15, 16, 0xFFFF);

    if(parentState->m_soundOn){
        c_handPos1and2.C.fillCircle(81, 106, 2, GREEN);
    } else {
        c_handPos1and2.C.fillCircle(81, 106, 2, RED);
    }

    if(parentState->m_vibraOn){
        c_handPos1and2.C.fillCircle(81, 84, 2, GREEN);
    } else{
        c_handPos1and2.C.fillCircle(81, 84, 2, RED);
    }

    c_handPos1and2.C.drawBitmap(74, 99, image_music_record_button_bits, 15, 16, 0xFFFF);

}

void SettingsUi::drawHandPos2() {

    c_handPos1and2.C.fillScreen(BLACK);
    c_handPos1and2.C.setTextColor(0xFFFF);
    c_handPos1and2.C.setTextSize(2);
    c_handPos1and2.C.setTextWrap(false);
    c_handPos1and2.C.setCursor(4, 0);
    c_handPos1and2.C.print("-Settings-");
    c_handPos1and2.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_handPos1and2.C.setTextColor(0xAD55);
    c_handPos1and2.C.setCursor(40, 29);
    c_handPos1and2.C.print(textField[parentState->m_selectedState]);
    c_handPos1and2.C.drawBitmap(97, 100, image_hand_notice_bits_left, 16, 11, 0x555);
    c_handPos1and2.C.drawBitmap(95, 28, image_music_fast_forward_bits, 17, 16, 0xFFFF);
    c_handPos1and2.C.drawBitmap(14, 28, image_music_fast_backward_bits, 17, 16, 0xFFFF);
    c_handPos1and2.C.setTextColor(0xFFFF);
    c_handPos1and2.C.setCursor(7, 77);
    c_handPos1and2.C.print("Vibra");
    c_handPos1and2.C.setCursor(6, 100);
    c_handPos1and2.C.print("Sound");
    c_handPos1and2.C.drawBitmap(74, 77, image_music_record_button_bits, 15, 16, 0xFFFF);

    if(parentState->m_soundOn){
        c_handPos1and2.C.fillCircle(81, 106, 2, GREEN);
    } else {
        c_handPos1and2.C.fillCircle(81, 106, 2, RED);
    }

    if(parentState->m_vibraOn){
        c_handPos1and2.C.fillCircle(81, 84, 2, GREEN);
    } else{
        c_handPos1and2.C.fillCircle(81, 84, 2, RED);
    }

    c_handPos1and2.C.drawBitmap(74, 99, image_music_record_button_bits, 15, 16, 0xFFFF);
}
