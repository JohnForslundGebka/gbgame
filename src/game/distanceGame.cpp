#include "game/distanceGame.h"


using namespace mbed;
using namespace rtos;
using namespace std::chrono;

// Constructor implementation
DistanceGame::DistanceGame() : m_gameLogic(osPriorityNormal1, 1024), m_userInput(osPriorityNormal, 1024), m_screen(128, 128, 0, 0) {}

void DistanceGame::handleInput(){
    while (m_running && Buttons::states.wait_any(Buttons::A_FLAG | Buttons::B_FLAG | Buttons::START_FLAG, osWaitForever, false)){

        switch(Buttons::states.get()){
            case Buttons::A_FLAG:
                // m_measured = ultrasonic.readDistance();
                // m_score = abs(m_targetLength - m_measured);
                
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
        Serial.println(m_measured); 
       

        m_displayManager.updateScreen(&m_screen);

        // Serial.println(targetLength); 
        // Serial.println(score); 
        // Serial.println(totScore); 
    }
}
// void DistanceGame::game() {
    
//         //Randomize a number between 10 and 100 store to targetLength

//         if(i == 0) {
//           Serial.println("Draw welcome/first screen and update");   
//         } else {
//             Serial.println("Draw other screen and update");
//         }
        

//         //wait for button press and take measurement when A button pressed

//         //Calculate score and add to total

//     }

//     //Update screen with total score and ranking etc. 
    
// }



void DistanceGame::run() {
    m_running = true;
    m_gameLogic.start(callback(this, &DistanceGame::update));
    m_userInput.start(callback(this, &DistanceGame::handleInput));

    m_targetLength = random(10, 101); 

    Serial.println(m_targetLength);

            
    m_screen.C.setTextColor(0xFFFF);
    m_screen.C.setTextSize(2);
    m_screen.C.setTextWrap(false);
    m_screen.C.setCursor(17, 3);
    m_screen.C.print("Distance");
    m_screen.C.drawLine(0, 0, 0, 0, 0xFFFF);
    m_screen.C.setTextColor(0x540);
    m_screen.C.setCursor(88, 24);
    m_screen.C.print("0");
    m_screen.C.drawLine(0, 0, 0, 0, 0xFFFF);
    m_screen.C.setTextColor(0xFFFF);
    m_screen.C.setCursor(21, 24);
    m_screen.C.print("Score");
    m_screen.C.drawLine(0, 0, 0, 0, 0xFFFF);
    m_screen.C.setTextColor(0xFAAA);
    m_screen.C.setTextSize(3);
    m_screen.C.setCursor(22, 67);
    m_screen.C.print(m_targetLength);
    m_screen.C.setTextColor(0x57FF);
    m_screen.C.setTextSize(2);
    m_screen.C.setCursor(-1, 45);
    m_screen.C.print("Hold device");
    m_screen.C.drawLine(0, 0, 0, 0, 0xFFFF);
    m_screen.C.setTextColor(0xFAAA);
    m_screen.C.setTextSize(3);
    m_screen.C.setCursor(71, 67);
    m_screen.C.print("cm");
    m_screen.C.drawRect(67, 15, 1, 1, 0xFFFF);
    m_screen.C.setTextColor(0x57FF);
    m_screen.C.setTextSize(2);
    m_screen.C.setCursor(16, 95);
    m_screen.C.print("from the");
    m_screen.C.drawLine(125, 20, -3, 20, 0xFFFF);
    m_screen.C.setCursor(41, 112);
    m_screen.C.print("wall");

    m_displayManager.updateScreen(&m_screen);
}

void DistanceGame::stop() {
    m_running = false;  // Signal threads to stop
    m_gameLogic.join();       // Wait for threads to finish
    m_userInput.join();
}







