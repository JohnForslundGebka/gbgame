#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <Serial.h>
#include "mbed.h"
#include "rtos.h"
#include "hardware/buttons.h"
#include "core/state.h"
#include "game/stateHandler.h"
#include "macros.h"
#include "core/macros.h"

// Create an instance of the display
Adafruit_SSD1351 display = Adafruit_SSD1351(128, 128, &::SPI, CS_PIN, DC_PIN, RST_PIN);
GFXcanvas16 canvas(128, 128);
EventFlags isDoneMoving;

Thread gfx(osPriorityNormal1);
Thread move(osPriorityNormal);

Buttons button;

using namespace mbed;
using namespace rtos;
using namespace std::chrono;

int xPos = 64;
int yPos = 64;

void moveBall(){

    while (Buttons::states.wait_any(Buttons::UP_FLAG | Buttons::LEFT_FLAG | Buttons::RIGHT_FLAG | Buttons::DOWN_FLAG, osWaitForever, false)){

           switch(Buttons::states.get()){
               case Buttons::UP_FLAG:    yPos = max(0, yPos - 3); break;
               case Buttons::LEFT_FLAG:  xPos = max(0, xPos - 3); break;
               case Buttons::RIGHT_FLAG: xPos = min(127, xPos + 3); break;
               case Buttons::DOWN_FLAG:  yPos = min(127, yPos + 3); break;
               default: break;
           }
           isDoneMoving.set(MOV_FLAG);
           ThisThread::sleep_for(milliseconds(60));
    }
}

void print(){
    while (isDoneMoving.wait_any(MOV_FLAG,osWaitForever))
    {
        canvas.fillScreen(0x0000);

        canvas.fillRect(xPos,yPos,14,14,RED);

        display.drawRGBBitmap(0, 0, canvas.getBuffer(), canvas.width(), canvas.height());
    }
}

void setup(){
    ::SPI.begin();
    display.begin(13000000);
    Serial.begin(9600);
    gfx.start(print);
    move.start(moveBall);
}

void loop(){
    ThisThread::sleep_for(5000);
}
