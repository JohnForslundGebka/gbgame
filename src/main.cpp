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

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define MOV_FLAG  (1UL << 2)

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

void setup(){
    ::SPI.begin();
    display.begin(13000000);
    Serial.begin(9600);

}


void loop(){

    canvas.fillScreen(0x0000);

    canvas.fillRect(10,10,14,14,RED);

    delay(300);
   // ThisThread::sleep_for(300);
}
