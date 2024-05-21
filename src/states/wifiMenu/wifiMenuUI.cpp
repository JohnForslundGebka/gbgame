#include "wifiMenuUI.h"
#include "wifiMenu.h"

WifiMenuUI::WifiMenuUI(WifiMenu *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {
    randomSeed(static_cast<int>(millis()));  // Seed the RNG
}

void WifiMenuUI::init() {}

//Exit screen
void WifiMenuUI::drawScreen3() {
    c_main.C.fillRect(0, 0, 128, 128, BLACK);

    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(23, 3);
    c_main.C.print("Wifi Menu");


}
