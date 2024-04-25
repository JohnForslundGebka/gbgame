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

Thread gfx;
Buttons button;

using namespace mbed;
using namespace rtos;

uint32_t flagsRead = 0;

int ballX = 10;
int ballY = 10;


void print()
{
  Serial.println("WOHO!");

    while(Buttons::buttonStates.wait_any
    (Buttons::UP_FLAG |
    Buttons::LEFT_FLAG |
    Buttons::RIGHT_FLAG |
    Buttons::START_FLAG |
    Buttons::A_FLAG |
    Buttons::B_FLAG |
    Buttons::DOWN_FLAG,
    osWaitForever, false))
    {
        Serial.println("WOHO i loooopen");
      //  clear canvas
        canvas.fillScreen(0x0000); // Clear canvas (not display)

        switch (Buttons::buttonStates.get()) {
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
            case Buttons::UP_RIGHT_FLAG:
                ballY += -2;
                ballX += 2;
                break;
            case Buttons::UP_LEFT_FLAG:
                ballX += -2;
                ballY += -2;
                break;
            default:
                break;
        }

        // Draw the ball at the new position
        canvas.fillCircle(ballX, ballY, 3, 0xA800);
        //draw canvas
        display.drawRGBBitmap(0, 0, canvas.getBuffer(), canvas.width(), canvas.height());
      }
}

void setup() {
    Serial.begin(9600);
    delay(5000);  // Allow time for the serial connection to stabilize
    Serial.println("Serial started");  // Check if this gets printed
    ::SPI.begin();
    display.begin(13000000);
    display.fillScreen(0x0000);
    gfx.start(print);
}

void loop() {
    Serial.println("LOOP");  // Check if this gets printed
    ThisThread::sleep_for(1000);
}