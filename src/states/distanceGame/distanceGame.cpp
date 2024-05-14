#include "distanceGame.h"
#include "distanceGameUi.h"
#include "rtos.h"
#include "mbed.h"

using namespace mbed;
using namespace rtos;
using namespace std::chrono;

// Constructor, initializes all necessary objects
DistanceGame::DistanceGame():  State("Measury"),  m_canvas(this) {}

void DistanceGame::handleInput() {
#ifdef DEBUG
     Serial.println("NU VÄNTAR JAG PÅ KNAPPAR");  
#endif

    while (m_isRunning) {

        uint32_t result = Buttons::states.wait_any(Buttons::START_FLAG  | Buttons::A_FLAG, osWaitForever, false);

        if (!m_isRunning) break;

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
                State::stateFlags.set(GlobalStates::stateList[0]->getFlagName());
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
        m_displayManager.updateScreen(&m_canvas.c_main);
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
#ifdef DEBUG
    Serial.println("NU GÖR JAG THREAD");
#endif


     m_canvas.drawScreen1();
    m_gameFlags.set(SCREEN_UPDATE_FLAG);
     ThisThread::sleep_for(50ms);
//    Thread t_screenBlink;
//    t_screenBlink.start(callback(this, &DistanceGame::screenBlink));

#ifdef DEBUG
    Serial.println("NU VANTAR JAG 1");
#endif    
        //Waits for user to press A to measure distance
        m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);
        
      //   t_screenBlink.join();

        //Measures distance and calculates how far off the user was.
        m_measured = ultrasonic.readDistance();
        m_score = abs(m_targetLength - m_measured);
    
        //Draws screen2 with the results and sets the flag to update screen
        m_canvas.drawScreen2();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);


        //Waits for button A press to finish the game
        m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);

        m_canvas.drawScreen3();
        m_gameFlags.set(SCREEN_UPDATE_FLAG); 

        ThisThread::sleep_for(1000ms);

#ifdef DEBUG
    Serial.println("NU AR GAME KLART");
#endif


    //Return to main manu when game finish
        m_isRunning = false;
        State::stateFlags.set(GlobalStates::stateList[0]->getFlagName());


#ifdef DEBUG
   Serial.println("NU HAR GAME KÖRTS KLART");  
#endif 

}

void DistanceGame::run() {
    //Starts the threads
    m_isRunning = true;

    if(m_isRunning)
        Serial.println("RUNNING IS TRUE");

#ifdef DEBUG
    Serial.println("NU RUN JAG");
#endif

    t_gameLogic = new Thread;
    t_screenUpdate = new Thread;
    t_userInput = new Thread;

  //  t_userInput->set_priority(osPriorityBelowNormal);

    t_gameLogic->start(mbed::callback(this, &DistanceGame::game));

    t_userInput->start(mbed::callback(this, &DistanceGame::handleInput));
    t_screenUpdate->start(mbed::callback(this, &DistanceGame::update));

#ifdef DEBUG
    Serial.println("NU RUN JAG FÄRDIGT");
#endif
}

void DistanceGame::stop() {
#ifdef DEBUG
    Serial.println("NU STOPPAR DISTANCEGAME");
#endif
    m_isRunning = false;
    //set flags, to not be stuck in waiting
    Buttons::states.set(Buttons::START_FLAG | Buttons::A_FLAG);
    m_gameFlags.set(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);
#ifdef DEBUG
    Serial.println("AVSLUTAR TRÅDAR");
#endif
    // Wait for threads to finish
    if(t_gameLogic) t_gameLogic->join();
#ifdef DEBUG
    Serial.println("AVSLUTAT GAME LOGIC");
#endif
    t_userInput->join();
#ifdef DEBUG
    Serial.println("AVSLUTAT USER INPUT");
#endif
    t_screenUpdate->join();
#ifdef DEBUG
    Serial.println("AVSLUTAT SCREEN UPDARE");
#endif

   //delete pointers
    delete t_gameLogic;
    delete t_userInput;
    delete t_screenUpdate;


    t_gameLogic = nullptr;
    t_screenUpdate = nullptr;
    t_userInput = nullptr;


    //clear all flags before exiting
    m_gameFlags.clear(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);
    Buttons::states.clear(Buttons::START_FLAG | Buttons::A_FLAG);

    ThisThread::sleep_for(10ms);
#ifdef DEBUG
    Serial.println("HEJDA FRAN STOP I DISTANCEGAME");
#endif
}

void DistanceGame::screenBlink() {
    while (m_isRunning) {
#ifdef DEBUG
        Serial.println("NU BLINKAR JAG");
#endif

        if (m_gameFlags.get() & ADVANCE_GAME_FLAG) {
            m_gameFlags.clear(ADVANCE_GAME_FLAG);
            break;  // Exit loop if the flag is set
        }

        // Set the text color to white and draw screen
        textColor = WHITE;
        m_canvas.drawScreen1();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        ThisThread::sleep_for(300ms);

        // Set the text color to black and draw screen
        textColor = BLACK;
        m_canvas.drawScreen1();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        ThisThread::sleep_for(300ms);
    }
}



