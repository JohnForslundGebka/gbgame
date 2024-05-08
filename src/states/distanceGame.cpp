#include "states/distanceGame.h"

using namespace mbed;
using namespace rtos;
using namespace std::chrono;

// Constructor, initializes all necessary objects
DistanceGame::DistanceGame() 
            :  m_canvas(128, 128, 0, 0) {}


void DistanceGame::handleInput() {
#ifdef DEBUG
     Serial.println("NU VÄNTAR JAG PÅ KNAPPAR");  
#endif 

    while (m_isRunning) {

        uint32_t result = Buttons::states.wait_any(Buttons::START_FLAG  | Buttons::A_FLAG, osWaitForever, false);

        //debounce logic
        ThisThread::sleep_for(50ms);
        if(Buttons::states.get() == 0)
            continue;

        //clear flags
        Buttons::states.clear(Buttons::START_FLAG  | Buttons::A_FLAG);
        // Handle input and update positions
        switch (result) {
            case Buttons::A_FLAG :
                #ifdef DEBUG
                     Serial.println("HEJ FRAN A");
                #endif 
                
                m_gameFlags.set(ADVANCE_GAME_FLAG);
                break;
            case Buttons::START_FLAG:
                #ifdef DEBUG
                    Serial.println("HEJ FRAN START");
                #endif 
                
                m_isRunning = false;
                State::stateFlags.set(MAIN_MENU);
                break;
            default:
                break;
        }

    }
}

//Updates the screen immediately when the SCREEN_UPDATE_FLAG is set (this thread has the highest priority)
void DistanceGame::update(){
    while (m_isRunning)
    {
        m_gameFlags.wait_any(SCREEN_UPDATE_FLAG, osWaitForever);
        m_displayManager.updateScreen(&m_canvas);
    }
}

void DistanceGame::game() {
#ifdef DEBUG
    Serial.println("NU BORJAR JAG");
#endif 

        //Seeds the random generator and generates the target length
        randomSeed(millis());
        m_targetLength = random(10, 100);

        //Creates and starts a thread that blink the screen text "button A"
        Thread t_screenBlink;
        t_screenBlink.start(callback(this, &DistanceGame::screenBlink));

#ifdef DEBUG
    Serial.println("NU VANTAR JAG");
#endif    
        //Waits for user to press A to measure distance
        m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, false);
        
        t_screenBlink.join();

        //Measures distance and calculates how far off the user was.
        m_measured = ultrasonic.readDistance();
        m_score = abs(m_targetLength - m_measured);
    
        //Draws screen2 with the results and sets the flag to update screen
        draw_screen2();
        m_gameFlags.set(SCREEN_UPDATE_FLAG); 

        //Waits for button A press to finish the game
        m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);

        draw_screen3();
        m_gameFlags.set(SCREEN_UPDATE_FLAG); 

        ThisThread::sleep_for(1000ms);
        
        //Return to main manu when game finish
        m_isRunning = false;
        State::stateFlags.set(MAIN_MENU);

#ifdef DEBUG
   Serial.println("NU HAR GAME KÖRTS KLART");  
#endif 

} 
void DistanceGame::run() {
    //Starts the threads
    m_isRunning = true;

#ifdef DEBUG
    Serial.println("NU RUN JAG");
#endif

    t_gameLogic = new Thread;
    t_screenUpdate = new Thread;
    t_userInput = new Thread;

    t_gameLogic->start(callback(this, &DistanceGame::game));
    t_userInput->start(callback(this, &DistanceGame::handleInput));
    t_screenUpdate->start(callback(this, &DistanceGame::update));
}

void DistanceGame::stop() {
#ifdef DEBUG
    Serial.println("NU STOPPAR JAG");
#endif
    m_isRunning = false;

    // Wait for threads to finish
    t_gameLogic->join();               // CHANGE TO JOIN???
    t_userInput->terminate();
    t_screenUpdate->terminate();

    delete t_gameLogic;
    delete t_userInput;
    delete t_screenUpdate;

    t_gameLogic = nullptr;
    t_screenUpdate = nullptr;
    t_userInput = nullptr;
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
    m_canvas.C.setCursor(5, 25);
    m_canvas.C.print("Your guess");

    m_canvas.C.setTextColor(GREEN);
    m_canvas.C.setTextSize(3);
    m_canvas.C.setCursor(22, 46);
    m_canvas.C.print(m_measured);

    m_canvas.C.setTextColor(GREEN);
    m_canvas.C.setTextSize(3);
    m_canvas.C.setCursor(71, 46);
    m_canvas.C.print("cm");

    m_canvas.C.setTextColor(0x57FF);
    m_canvas.C.setTextSize(2);
    m_canvas.C.setCursor(16, 71);
    m_canvas.C.print("you were");

    m_canvas.C.setTextColor(RED);
    m_canvas.C.setCursor(53, 91);
    m_canvas.C.print(m_score);
    
    m_canvas.C.setTextColor(0xFFFF);
    m_canvas.C.setCursor(25, 109);
    m_canvas.C.print("cm off!");
}

void DistanceGame::draw_screen3() {
    m_canvas.C.fillRect(0, 0, 128, 128, BLACK);

    m_canvas.C.setTextColor(0xFFFF);
    m_canvas.C.setTextSize(2);
    m_canvas.C.setTextWrap(false);
    m_canvas.C.setCursor(17, 3);
    m_canvas.C.print("Exiting...");   
}

void DistanceGame::screenBlink() {
    while (m_isRunning) {  
        if (m_gameFlags.get() & ADVANCE_GAME_FLAG) {
            m_gameFlags.clear(ADVANCE_GAME_FLAG);
            break;  // Exit loop if the flag is set
        }

        // Set the text color to white and draw screen
        textColor = WHITE;
        draw_screen1();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        ThisThread::sleep_for(300ms);

        // Set the text color to black and draw screen
        textColor = BLACK;
        draw_screen1();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        ThisThread::sleep_for(300ms);
    }
}



