#include "micGame.h"
#include "micGameUI.h"
#include "rtos.h"
#include "mbed.h"

// Constructor, initializes the state with it's name "voicy"
MicGame::MicGame():  State("Voicy"){}

void MicGame::handleInput() {
    using namespace rtos;
    using namespace mbed;

#ifdef DEBUG
     Serial.println("NU VÄNTAR JAG PÅ KNAPPAR");  
#endif

    while (m_isRunning) {
        using namespace std::chrono;

        uint32_t result = Buttons::states.wait_any(Buttons::START_FLAG  | Buttons::A_FLAG, osWaitForever, false);

        if (!m_isRunning) break;

        //debounce logic
        rtos::ThisThread::sleep_for(50ms);
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
                State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
                break;
            
            default:
                break;
        }

    }
}

//Updates the screen immediately when the SCREEN_UPDATE_FLAG is set (this thread has the highest priority)
void MicGame::update(){
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    while (m_isRunning)
    {
        m_gameFlags.wait_any(SCREEN_UPDATE_FLAG, osWaitForever);
        m_displayManager.updateScreen(&m_canvas->c_main);
    }
}

void MicGame::game() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    const int GAME_LENGTH = 15;             //Length in seconds of a game
    int lastTime = 0;                       //Keeps track of when to update score

    //Creates and initialize a timer and attached a function that increments m_timeCounter every second
    Ticker ticker;
    ticker.attach([this]() { this->incrementCounter(); }, 1s);
    
    while (m_isRunning) {
        
        //Checks if the waveform line crosses the circle
        if (m_canvas->isWaveformInCircle(15, m_position, 8)) {

            if (m_timeCounter > lastTime) {
                m_score++;
                lastTime = m_timeCounter;
            }
        }
        
        //Process the audioBuffer setting the Microphone::m_value variable
        mic.processAudioData();

        //Updates the position of the ball based on the mic input.
        updatePosition(mic.m_value);
                
        //Finish game when time limit is reached
        if (m_timeCounter == GAME_LENGTH) {
            break;
        }
    }

    //Detach timer
    ticker.detach();

    //Exit the waveform loop for proper termination of thread
    m_runWaveform = false;

    //Draw the last screen showing the score
    m_canvas->drawScreen3();

    //Waits for button A press to exit the game
    m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);

    //Return to main menu when game finish
    m_isRunning = false;
    State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());

}

void MicGame::run() {
    using namespace rtos;
    using namespace mbed;

    //Reset the counters to 0
    m_score = 0;
    m_timeCounter = 0;


    //Starts the threads
    m_isRunning = true;
    m_runWaveform = true;

#ifdef DEBUG
    Serial.println("NU RUN JAG");
#endif

    t_gameLogic = new Thread;
    t_screenUpdate = new Thread;
    t_userInput = new Thread;
    t_animateWaveform = new Thread;

    m_canvas = new MicGameUI(this);

    t_gameLogic->start(mbed::callback(this, &MicGame::game));
    t_userInput->start(mbed::callback(this, &MicGame::handleInput));
    t_screenUpdate->start(mbed::callback(this, &MicGame::update));
    t_animateWaveform->start(mbed::callback(this, &MicGame::animateWaveform));

    //initialize pdm.h library and mic object
    mic.init();
}

void MicGame::stop() {
    using namespace std::chrono;

#ifdef DEBUG
    Serial.println("NU STOPPAR MIC GAME");
#endif

    m_isRunning = false;
    //set flags, to not be stuck in waiting
    Buttons::states.set(Buttons::START_FLAG | Buttons::A_FLAG);
    m_gameFlags.set(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);

#ifdef DEBUG
    Serial.println("AVSLUTAR TRÅDAR");
#endif

    // Finnish threads and clean upp pointers
    if(t_gameLogic) {
        t_gameLogic->join();
        delete t_gameLogic;
        t_gameLogic = nullptr;
    }

#ifdef DEBUG
    Serial.println("AVSLUTAT GAME LOGIC");
#endif

    if(t_userInput){
        t_userInput->join();
        delete t_userInput;
        t_userInput = nullptr;
    }

#ifdef DEBUG
    Serial.println("AVSLUTAT USER INPUT");
#endif

    if(t_screenUpdate){
        t_screenUpdate->join();
        delete t_screenUpdate;
        t_screenUpdate = nullptr;
    }
   
#ifdef DEBUG
    Serial.println("AVSLUTAT SCREEN UPDARE");
#endif

    if(t_animateWaveform){
        t_animateWaveform->join();
        delete t_animateWaveform;
        t_animateWaveform = nullptr;
    }


    delete m_canvas; // Properly delete the m_canvas when stopping
    m_canvas = nullptr;

    mic.end();

    //clear all flags before exiting
    m_gameFlags.clear(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);
    Buttons::states.clear(Buttons::START_FLAG | Buttons::A_FLAG);

    rtos::ThisThread::sleep_for(10ms);

#ifdef DEBUG
    Serial.println("HEJDA FRAN STOP I DISTANCEGAME");
#endif
}

//Runs in a separate thread to update the waveform and screen
void MicGame::animateWaveform() {
    using namespace std::chrono;
    using namespace rtos;

    while (m_isRunning && m_runWaveform) {
        m_canvas->drawWaveform();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        ThisThread::sleep_for(10ms);                //Update frequency
    }
}

//Function that attaches to the timer interrupt ticker and increments time counter
void MicGame::incrementCounter() {
    m_timeCounter++;
}


//Updates the ball position based on mic input, adjust sleep_for parameter to change speed
void MicGame::updatePosition(int change) {

    if (change < 0) {                   //Move down when no sound
        m_position++;
        if(m_position > 100) {
            m_position = 100;
        }
        rtos::ThisThread::sleep_for(20);
    }
    else {                              //Move ball UP when recieving sound
        m_position--;
        if(m_position < 30) {
            m_position = 30;
        }
        rtos::ThisThread::sleep_for(3);
    }
}
