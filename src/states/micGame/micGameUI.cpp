#include "micGameUI.h"
#include "micGame.h"

MicGameUI::MicGameUI(MicGame *pGame) : parentState(pGame), c_main(128, 128, 0, 0) {}

void MicGameUI::init() {}

void MicGameUI::drawScreen1() {

    randomSeed(static_cast<int>(millis())); // Initialize random number generator seed with noise from analog pin

    // Initialize the first element to some starting value, e.g., 0
    const int size = 128;
    int arr[size];
    arr[0] = 64;

    // Generate the rest of the array
    for (int i = 1; i < size; ++i) {
    
        if (random(2) == 0) {  // random(2) returns either 0 or 1
            arr[i] = arr[i - 1] + 3;  // Increment the previous element
        } else {
            arr[i] = arr[i - 1] - 3;  // Decrement the previous element
        }
    }


    c_main.C.fillRect(0, 0, 128, 128, BLACK);
    c_main.C.setTextColor(0xFFFF);
    c_main.C.setTextSize(2);
    c_main.C.setTextWrap(false);
    c_main.C.setCursor(17, 3);
    c_main.C.print("Mic Game");

    for (int x = 0; x < size; x++) {
        c_main.C.drawPixel(x, arr[x], 0xFAAA);
    }

    // c_main.C.setTextColor(0xFAAA);
    // c_main.C.setTextSize(3);
    // c_main.C.setCursor(22, 43);
    // c_main.C.print(parentState->m_testNumber);
}

