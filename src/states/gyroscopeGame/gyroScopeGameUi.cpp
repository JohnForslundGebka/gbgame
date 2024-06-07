#include "gyroScopeGameUi.h"
#include "gyroscopeGame.h"

GyroScopeGameUi::GyroScopeGameUi(GyroscopeGame *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {

}

void GyroScopeGameUi::init() {
    // Draw score counter
    c_main.C.setTextSize(1);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setCursor(5, 5);
    c_main.C.print("");
    c_main.C.print(parentState->m_score);

    // Draw remaining time
    c_main.C.setCursor(90, 5);
    c_main.C.setTextColor((parentState->m_timeCounter < 10) ? 0xF800 : 0xFFFF); // Change color to red if remaining time is less than 10 seconds
    c_main.C.print(":");
    c_main.C.print(parentState->m_timeCounter); // Seconds

}

void GyroScopeGameUi::draw() {


}
