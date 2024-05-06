#include "canvasMainMenu1.h"

void CanvasMainMenu1::init() {
    C.setTextColor(0xFFFF);
    C.setTextSize(2);
    C.setTextWrap(false);
    C.setCursor(18, 0);
    C.print("-GbgGame-");
    C.drawLine(1, 18, 128, 18, 0xFFFF);
    C.drawBitmap(1, 1, image_light_bits, 16, 16, 0xA800);
    C.setCursor(31, 26);
    C.print("Games");
    C.setCursor(31, 47);
    C.print("Settings");
}