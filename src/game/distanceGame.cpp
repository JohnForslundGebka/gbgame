#include "game/distanceGame.h"

using namespace mbed;
using namespace rtos;
using namespace std::chrono;

// Constructor, initializes all necessary objects
DistanceGame::DistanceGame() 
            : t_gameLogic(osPriorityNormal, 1024), t_userInput(osPriorityNormal, 1024)
            , t_screenUpdate(osPriorityNormal1, 1024), m_canvas(128, 128, 0, 0) {}

//
void DistanceGame::handleInput(){
    
    uint32_t result = Buttons::states.wait_any(Buttons::A_FLAG | Buttons::START_FLAG, osWaitForever);

    if (result == Buttons::A_FLAG) {
        Serial.println("HEJ FRAN A!");
        m_gameFlags.set(ADVANCE_GAME_FLAG);
    } else if (result == Buttons::START_FLAG) {
        Serial.println("HEJ FRAN START!");
        State::stateFlags.set(MAIN_MENU);
    }
}

//Updates the screen immediately when the SCREEN_UPDATE_FLAG is set (this thread has the highest priority)
void DistanceGame::update(){
    while (m_gameFlags.wait_any(SCREEN_UPDATE_FLAG, osWaitForever))
    {
        m_displayManager.updateScreen(&m_canvas);
    }
}

void DistanceGame::game() {
        
        //Seeds the random generator and generates the target length
        randomSeed(millis());
        m_targetLength = random(10, 100);

        //Draws screen1 and sets the flag to update the screen
        draw_screen1();
        m_gameFlags.set(SCREEN_UPDATE_FLAG); 

        //Waits for user to press A to measure distance
        m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);
        
        //Measures distance and calculates how far off the user was.
        m_measured = ultrasonic.readDistance();
        m_score = abs(m_targetLength - m_measured);
    
        //Draws screen2 with the results and sets the flag to update screen
        draw_screen2();
        m_gameFlags.set(SCREEN_UPDATE_FLAG); 

        //Waits for button A press to finish the game
        m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);

        //Do exit code
}

void DistanceGame::run() {
    //Starts the threads
    m_isRunning = true;

    t_gameLogic.start(callback(this, &DistanceGame::game));
    t_userInput.start(callback(this, &DistanceGame::handleInput));
    t_screenUpdate.start(callback(this, &DistanceGame::update));
    
}

void DistanceGame::stop() {
    m_isRunning = false;
    // Wait for threads to finish
    t_gameLogic.join();
    t_userInput.join();
    t_screenUpdate.join();
}

void DistanceGame::draw_screen1() {
    m_canvas.C.fillRect(0, 0, 128, 128, BLACK);
    m_canvas.C.setTextColor(0xFFFF);
    m_canvas.C.setTextSize(2);
    m_canvas.C.setTextWrap(false);
    m_canvas.C.setCursor(17, 3);
    m_canvas.C.print("Distance");

    m_canvas.C.drawLine(125, 20, -3, 20, 0xFFFF); //Line under 'Distance'

    m_canvas.C.setTextColor(0x57FF);
    m_canvas.C.setTextSize(2);
    m_canvas.C.setCursor(-1, 25);
    m_canvas.C.print("Hold device");

    m_canvas.C.setTextColor(0xFAAA);
    m_canvas.C.setTextSize(3);
    m_canvas.C.setCursor(22, 43);
    m_canvas.C.print(m_targetLength);

    //m_canvas.C.drawLine(0, 0, 0, 0, 0xFFFF);
    m_canvas.C.setTextColor(0xFAAA);
    m_canvas.C.setTextSize(3);
    m_canvas.C.setCursor(71, 43);
    m_canvas.C.print("cm");

    m_canvas.C.setTextColor(0x57FF);
    m_canvas.C.setTextSize(2);
    m_canvas.C.setCursor(16, 71);
    m_canvas.C.print("from the");

    
    m_canvas.C.setCursor(41, 88);
    m_canvas.C.print("wall");
    
    m_canvas.C.setTextColor(textColor);
    m_canvas.C.setCursor(20, 107);
    m_canvas.C.print("press A!");
}

void DistanceGame::draw_screen2() {
    m_canvas.C.fillRect(0, 0, 128, 128, BLACK);

    m_canvas.C.setTextColor(0xFFFF);
    m_canvas.C.setTextSize(2);
    m_canvas.C.setTextWrap(false);
    m_canvas.C.setCursor(17, 3);
    m_canvas.C.print("Distance");

    m_canvas.C.drawLine(125, 20, -3, 20, 0xFFFF); //Line under 'Distance'

    m_canvas.C.setTextColor(0x57FF);
    m_canvas.C.setTextSize(2);
    m_canvas.C.setCursor(-1, 25);
    m_canvas.C.print("Your guess");

    m_canvas.C.setTextColor(0xFAAA);
    m_canvas.C.setTextSize(3);
    m_canvas.C.setCursor(22, 43);
    m_canvas.C.print(m_measured);

    m_canvas.C.drawLine(0, 0, 0, 0, 0xFFFF);
    m_canvas.C.setTextColor(0xFAAA);
    m_canvas.C.setTextSize(3);
    m_canvas.C.setCursor(71, 43);
    m_canvas.C.print("cm");

    m_canvas.C.setTextColor(0x57FF);
    m_canvas.C.setTextSize(2);
    m_canvas.C.setCursor(16, 71);
    m_canvas.C.print("you were");

    
    m_canvas.C.setCursor(41, 88);
    m_canvas.C.print(m_score);
    
    m_canvas.C.setTextColor(0xFFFF);
    m_canvas.C.setCursor(20, 107);
    m_canvas.C.print("cm off!");
}





