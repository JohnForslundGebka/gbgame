#include "subMenuGamesUi.h"
#include "games.h"

SubMenuGamesUi::SubMenuGamesUi(Game *p) :c_canvas(128,128,0,0), parrentState(p){}

void SubMenuGamesUi::init() {
    updateTextFields();

    c_canvas.C.setTextColor(0xFFFF);
    c_canvas.C.setTextSize(2);
    c_canvas.C.setTextWrap(false);
    c_canvas.C.setCursor(18, 0);
    c_canvas.C.print("-GbgGame-");

    c_canvas.C.drawLine(1, 18, 128, 18, 0xFFFF);
    c_canvas.C.drawBitmap(1, 1, image_light_bits, 16, 16, 0xFFEA);

    c_canvas.C.drawBitmap(2, 64, image_hand_notice_bits, 16, 11, 0x555);

    c_canvas.C.setTextColor(0xA800);
    c_canvas.C.setCursor(27, 62);
    c_canvas.C.print(textField[0]);


    c_canvas.C.setTextColor(0xFFFF);
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

void SubMenuGamesUi::updateTextFields() {



}

void SubMenuGamesUi::draw() {

}
