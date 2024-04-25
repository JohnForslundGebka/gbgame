#include "Buttons2.h"

//pin numbers for each button
const uint8_t Buttons2::buttonPins[numberOfButtons] = {2, 3, 4, 5, 6, 7, 8};

//volatile bool Buttons2::states[numberOfButtons];

void Buttons2::begin() {
    for (int i = 0; i < numberOfButtons; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
        switch (i) {
            case 0: attachInterrupt(digitalPinToInterrupt(buttonPins[i]), ISRButton0, CHANGE); break;
            case 1: attachInterrupt(digitalPinToInterrupt(buttonPins[i]), ISRButton1, CHANGE); break;
            case 2: attachInterrupt(digitalPinToInterrupt(buttonPins[i]), ISRButton2, CHANGE); break;
            case 3: attachInterrupt(digitalPinToInterrupt(buttonPins[i]), ISRButton3, CHANGE); break;
            case 4: attachInterrupt(digitalPinToInterrupt(buttonPins[i]), ISRButton4, CHANGE); break;
            case 5: attachInterrupt(digitalPinToInterrupt(buttonPins[i]), ISRButton5, CHANGE); break;
            case 6: attachInterrupt(digitalPinToInterrupt(buttonPins[i]), ISRButton6, CHANGE); break;
        }
    }

}


bool Buttons2::getButtonState(int index) {
    index--;
    if (index >= 0 && index < (numberOfButtons)) {
        return states[index];
    }
    return false; // Return false if out of bounds
}

uint8_t Buttons2::getButtonNumber() {
    for (int i = 0; i < numberOfButtons; i++) {
        if (states[i] == true) {
            return i + 1;
        } else {
            return 0;
        }
    }   
}

void Buttons2::noButtonsPressed() {
    for (int i = 0; i < numberOfButtons; i++) {
        states[i] == false;
    }
}

// ISR functions buttons
void Buttons2::ISRButton0() { states[0] = digitalRead(buttonPins[0]) == LOW; }
void Buttons2::ISRButton1() { states[1] = digitalRead(buttonPins[1]) == LOW; }
void Buttons2::ISRButton2() { states[2] = digitalRead(buttonPins[2]) == LOW; }
void Buttons2::ISRButton3() { states[3] = digitalRead(buttonPins[3]) == LOW; }
void Buttons2::ISRButton4() { states[4] = digitalRead(buttonPins[4]) == LOW; }
void Buttons2::ISRButton5() { states[5] = digitalRead(buttonPins[5]) == LOW; }
void Buttons2::ISRButton6() { states[6] = digitalRead(buttonPins[6]) == LOW; }

