#include "game/distanceGame.h"


using namespace mbed;
using namespace rtos;
using namespace std::chrono;

// Constructor implementation
DistanceGame::DistanceGame() 
            : m_gameLogic(osPriorityNormal1, 1024), m_userInput(osPriorityNormal, 1024), m_screen(128, 128, 0, 0) 
            {
                randomSeed(micros());  //Seeds the random generator ensuring new random numbers every time.
            }

void DistanceGame::handleInput(){
    while (m_running && Buttons::states.wait_any(Buttons::A_FLAG | Buttons::B_FLAG | Buttons::START_FLAG, osWaitForever, false)){

        switch(Buttons::states.get()){
            case Buttons::A_FLAG:
                //m_measured = ultrasonic.readDistance();
                
                break;
            case Buttons::B_FLAG:   
                Serial.println("B pressed");
                break;
            case Buttons::START_FLAG:   
                Serial.println("START pressed");
                break;
        
            
            default: break;
        }

        Buttons::states.clear(Buttons::ALL_FLAG);
        m_updateUI.set(MOV_FLAG);
        ThisThread::sleep_for(milliseconds(60));
    }
}

void DistanceGame::update(){
    while (m_running && m_updateUI.wait_any(MOV_FLAG,osWaitForever))
    {
        //Serial.println(m_measured); 
       

        m_displayManager.updateScreen(&m_screen);

        // Serial.println(targetLength); 
        // Serial.println(score); 
        // Serial.println(totScore); 
    }
}
void DistanceGame::game() {
    m_targetLength = random(10, 100);

    draw_screen1();
    m_displayManager.updateScreen(&m_screen); 

    if (m_running && Buttons::states.wait_any(Buttons::A_FLAG, osWaitForever, false)){
        measured = ultrasonic.readDistance();
        score = abs(m_targetLength - measured);


        Serial.print("TargetLength:  ");
        Serial.print(m_targetLength);
        Serial.print("        Measured length:  ");
        Serial.print(measured);
        Serial.println();

        Buttons::states.clear(Buttons::ALL_FLAG);
    }

    draw_screen2();
    m_displayManager.updateScreen(&m_screen); 
 
}



void DistanceGame::run() {
    m_running = true;

    //m_gameLogic.start(callback(this, &DistanceGame::game));
    //m_userInput.start(callback(this, &DistanceGame::handleInput));
    game();
}

void DistanceGame::stop() {
    m_running = false;  // Signal threads to stop
    m_gameLogic.join();       // Wait for threads to finish
    m_userInput.join();
}

void DistanceGame::draw_screen1() {
    m_screen.C.fillRect(0, 0, 128, 128, BLACK);
    m_screen.C.setTextColor(0xFFFF);
    m_screen.C.setTextSize(2);
    m_screen.C.setTextWrap(false);
    m_screen.C.setCursor(17, 3);
    m_screen.C.print("Distance");

    m_screen.C.drawLine(125, 20, -3, 20, 0xFFFF); //Line under 'Distance'

    m_screen.C.setTextColor(0x57FF);
    m_screen.C.setTextSize(2);
    m_screen.C.setCursor(-1, 25);
    m_screen.C.print("Hold device");

    m_screen.C.setTextColor(0xFAAA);
    m_screen.C.setTextSize(3);
    m_screen.C.setCursor(22, 43);
    m_screen.C.print(m_targetLength);

    m_screen.C.drawLine(0, 0, 0, 0, 0xFFFF);
    m_screen.C.setTextColor(0xFAAA);
    m_screen.C.setTextSize(3);
    m_screen.C.setCursor(71, 43);
    m_screen.C.print("cm");

    m_screen.C.setTextColor(0x57FF);
    m_screen.C.setTextSize(2);
    m_screen.C.setCursor(16, 71);
    m_screen.C.print("from the");

    
    m_screen.C.setCursor(41, 88);
    m_screen.C.print("wall");
    
    m_screen.C.setTextColor(0xFFFF);
    m_screen.C.setCursor(20, 107);
    m_screen.C.print("press A!");
}
void DistanceGame::draw_screen2() {
    m_screen.C.fillRect(0, 0, 128, 128, BLACK);

    m_screen.C.setTextColor(0xFFFF);
    m_screen.C.setTextSize(2);
    m_screen.C.setTextWrap(false);
    m_screen.C.setCursor(17, 3);
    m_screen.C.print("Distance");

    m_screen.C.drawLine(125, 20, -3, 20, 0xFFFF); //Line under 'Distance'

    m_screen.C.setTextColor(0x57FF);
    m_screen.C.setTextSize(2);
    m_screen.C.setCursor(-1, 25);
    m_screen.C.print("Your guess");

    m_screen.C.setTextColor(0xFAAA);
    m_screen.C.setTextSize(3);
    m_screen.C.setCursor(22, 43);
    m_screen.C.print(measured);

    m_screen.C.drawLine(0, 0, 0, 0, 0xFFFF);
    m_screen.C.setTextColor(0xFAAA);
    m_screen.C.setTextSize(3);
    m_screen.C.setCursor(71, 43);
    m_screen.C.print("cm");

    m_screen.C.setTextColor(0x57FF);
    m_screen.C.setTextSize(2);
    m_screen.C.setCursor(16, 71);
    m_screen.C.print("you were");

    
    m_screen.C.setCursor(41, 88);
    m_screen.C.print(score);
    
    m_screen.C.setTextColor(0xFFFF);
    m_screen.C.setCursor(20, 107);
    m_screen.C.print("cm off!");
}





