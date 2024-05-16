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

    m_canvas->drawScreen1();
    m_gameFlags.set(SCREEN_UPDATE_FLAG);

    //Waits for button A press to finish the game
    m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);

    rtos::ThisThread::sleep_for(1000ms);

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
    m_canvas = new MicGameUI(this);


    t_gameLogic->start(mbed::callback(this, &MicGame::game));
    t_userInput->start(mbed::callback(this, &MicGame::handleInput));
    t_screenUpdate->start(mbed::callback(this, &MicGame::update));
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




