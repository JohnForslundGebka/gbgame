#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <Serial.h>
#include "mbed.h"
#include "rtos.h"
#include "hardware/buttons.h"

#define DC_PIN   15   // Data/Command
#define CS_PIN   14   // Chip Select, can use any GPIO except A6/A7
#define RST_PIN  9    // Reset

// Create an instance of the display
Adafruit_SSD1351 display = Adafruit_SSD1351(128, 128, &::SPI, CS_PIN, DC_PIN, RST_PIN);
GFXcanvas16 canvas(128, 128);

using namespace mbed;
using namespace rtos;


//Buttons object
Buttons buttons;
uint32_t flagsRead = 0;

int ballX = 10;
int ballY = 10;

void setup() {
    ::SPI.begin();
    Serial.begin(9600);
    display.begin(13000000);
    display.fillScreen(0x0000);
}

void loop() {

    //clear canvas
    canvas.fillScreen(0x0000); // Clear canvas (not display)

    // Draw the ball at the new position
    canvas.fillCircle(ballX, ballY, 3, 0xA800);

    //draw canvas
    display.drawRGBBitmap(0, 0, canvas.getBuffer(), canvas.width(), canvas.height());

    //wait for flags to be set
    flagsRead = buttons.buttonStates.wait_any(
            Buttons::UP_FLAG |
            Buttons::LEFT_FLAG |
            Buttons::RIGHT_FLAG |
            Buttons::START_FLAG |
            Buttons::A_FLAG |
            Buttons::B_FLAG |
            Buttons::DOWN_FLAG, osWaitForever, false
    );
    //draw circle depending on which flag was set
    switch (flagsRead) {
        case Buttons::UP_FLAG:
            ballY += -2;
            break;
        case Buttons::LEFT_FLAG:
            ballX += -2;
            break;
        case Buttons::RIGHT_FLAG:
            ballX += 2;
            break;
        case Buttons::DOWN_FLAG:
            ballY += 2;
            break;
        default:
            break;
    }


}