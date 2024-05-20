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
                State::stateFlags.set(GlobalStates::stateList[static_cast<int>(index::ARRAY_MAIN_MENU)]->getFlagName());
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
        //ThisThread::sleep_for(20ms);
    }
}

void MicGame::game() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    while (m_isRunning) {
        // m_canvas->drawWaveform();
        // m_gameFlags.set(SCREEN_UPDATE_FLAG);
        // ThisThread::sleep_for(30ms);
        m_canvas->drawBall(m_ballPos);
        // mic.onPDMdata();
        mic.processAudioData();
        //Serial.println(m_mic.value);
        m_ballPos += mic.m_value;
    }



    //Waits for button A press to finish the game
    m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);
    //Return to main menu when game finish
        m_isRunning = false;
        State::stateFlags.set(GlobalStates::stateList[0]->getFlagName());

}

void MicGame::run() {
    using namespace rtos;
    using namespace mbed;
    //Starts the threads
    m_isRunning = true;



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
    Serial.println("NU STOPPAR DISTANCEGAME");
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
   
    if(t_animateWaveform){
        t_animateWaveform->join();
        delete t_animateWaveform;
        t_animateWaveform = nullptr;
    }

#ifdef DEBUG
    Serial.println("AVSLUTAT SCREEN UPDARE");
#endif

    delete m_canvas; // Properly delete the m_canvas when stopping
    m_canvas = nullptr;


    //clear all flags before exiting
    m_gameFlags.clear(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);
    Buttons::states.clear(Buttons::START_FLAG | Buttons::A_FLAG);

    rtos::ThisThread::sleep_for(10ms);

#ifdef DEBUG
    Serial.println("HEJDA FRAN STOP I DISTANCEGAME");
#endif
}


void MicGame::animateWaveform() {
    using namespace std::chrono;
    using namespace rtos;

    while (m_isRunning) {
        m_canvas->drawWaveform();
        m_gameFlags.set(SCREEN_UPDATE_FLAG);
        ThisThread::sleep_for(30ms);
    }
}



