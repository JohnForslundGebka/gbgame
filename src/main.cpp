#include "mbed.h"
#include "rtos.h"
#include "hardware/buttons.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

#define DC_PIN   15   // Data/Command
#define CS_PIN   14   // Chip Select, can use any GPIO except A6/A7
#define RST_PIN  9    // Reset

// Create an instance of the display
Adafruit_SSD1351 display = Adafruit_SSD1351(128, 128, &SPI, CS_PIN, DC_PIN, RST_PIN);
GFXcanvas16 canvas(128, 128);

using namespace mbed;
using namespace rtos;


//Buttons object
Buttons buttons;
uint32_t flagsRead = 0;

int ballX = 10;
int ballY = 10;

void setup() {
    SPI.begin();
    Serial.begin(9600);
    display.begin(13000000);
    display.fillScreen(0x0000);
}

void loop() {

    canvas.fillScreen(0x0000); // Clear canvas (not display)

    // Draw the ball at the new position
    canvas.fillCircle(ballX, ballY, 3, 0xA800);

    flagsRead = buttons.buttonStates.wait_any(
            Buttons::UP_FLAG |
            Buttons::LEFT_FLAG |
            Buttons::RIGHT_FLAG |
            Buttons::START_FLAG |
            Buttons::A_FLAG |
            Buttons::B_FLAG |
            Buttons::DOWN_FLAG, osWaitForever, false
    );
    Serial.println(flagsRead);


}