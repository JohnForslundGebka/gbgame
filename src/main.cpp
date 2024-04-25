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

#define DISPLAY_WIDTH  128
#define DISPLAY_HEIGHT 128
#define BALL_RADIUS    3

#define MOV_FLAG  (1UL << 2)
uint32_t flags = 0xFFFFFFFF;

// Create an instance of the display
Adafruit_SSD1351 display = Adafruit_SSD1351(128, 128, &::SPI, CS_PIN, DC_PIN, RST_PIN);
GFXcanvas16 canvas(128, 128);
EventFlags isDoneMoving;

Thread gfx(osPriorityNormal1);
Thread bal(osPriorityNormal);
Buttons button;

using namespace mbed;
using namespace rtos;


int ballX = 10;
int ballY = 10;
int balRad = 3;

//isDoneMoving.wait_any(MOV_FLAG,osWaitForever,true)

void print()
{
    while(isDoneMoving.wait_any(MOV_FLAG,osWaitForever,true)){

        Serial.println("WOHO i print");
        //clear canvas
        canvas.fillScreen(0x0000);
        // Draw the ball at the new position
        canvas.fillCircle(ballX, ballY, 3, 0xA800);
        //draw canvas
        display.drawRGBBitmap(0, 0, canvas.getBuffer(), canvas.width(), canvas.height());
      }
}

void moveBal() {
    while (Buttons::buttonStates.wait_any(
            0xFFFFFFFF,
            osWaitForever, false)) {

        Serial.println("WOHO i movbal");

        switch (Buttons::buttonStates.get()) {
            case Buttons::UP_FLAG:
                if (ballY > BALL_RADIUS)  // Ensure the ball doesn't go out of the upper boundary
                    ballY -= 1;
                break;
            case Buttons::LEFT_FLAG:
                if (ballX > BALL_RADIUS)  // Ensure the ball doesn't go out of the left boundary
                    ballX -= 1;
                break;
            case Buttons::RIGHT_FLAG:
                if (ballX < DISPLAY_WIDTH - BALL_RADIUS)  // Ensure the ball doesn't go out of the right boundary
                    ballX += 1;
                break;
            case Buttons::DOWN_FLAG:
                if (ballY < DISPLAY_HEIGHT - BALL_RADIUS)  // Ensure the ball doesn't go out of the lower boundary
                    ballY += 1;
                break;
            case Buttons::UP_RIGHT_FLAG:
                if (ballY > BALL_RADIUS && ballX < DISPLAY_WIDTH - BALL_RADIUS) {
                    ballY -= 1;
                    ballX += 1;
                }
                break;
            case Buttons::UP_LEFT_FLAG:
                if (ballY > BALL_RADIUS && ballX > BALL_RADIUS) {
                    ballY -= 1;
                    ballX -= 1;
                }
                break;
            default:
                break;
        }

        isDoneMoving.set(MOV_FLAG);
    }
}

void setup() {
    Serial.begin(9600);
  //  delay(5000);  // Allow time for the serial connection to stabilize
    Serial.println("Serial started");  // Check if this gets printed
    ::SPI.begin();
    display.begin(13000000);
    display.fillScreen(0x0000);
    gfx.start(print);
    bal.start(moveBal);
}

void loop() {
   // Serial.println("LOOP");  // Check if this gets printed
    ThisThread::sleep_for(1000);
}