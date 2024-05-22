#include "wifiMenu.h"
#include "wifiMenuUI.h"
#include "rtos.h"
#include "mbed.h"

// Constructor, initializes the state with it's name "Wifi Menu"
WifiMenu::WifiMenu():  State("Wifi Menu"){}

void WifiMenu::handleInput() {
    using namespace rtos;
    using namespace mbed;

    while (m_isRunning) {
        using namespace std::chrono;

        uint32_t result = Buttons::states.wait_any(Buttons::START_FLAG  | Buttons::A_FLAG | Buttons::UP_FLAG 
                                                | Buttons::DOWN_FLAG | Buttons::LEFT_FLAG | Buttons::RIGHT_FLAG | Buttons::B_FLAG, osWaitForever, false);

        if (!m_isRunning) break;

        //debounce logic
        rtos::ThisThread::sleep_for(50ms);
        if(Buttons::states.get() == 0) {
            continue;
        }

        //clear flags
        Buttons::states.clear(Buttons::START_FLAG  | Buttons::A_FLAG) | Buttons::UP_FLAG 
                            | Buttons::DOWN_FLAG | Buttons::LEFT_FLAG | Buttons::RIGHT_FLAG | Buttons::B_FLAG;
        // Handle input and update positions
        switch (result) {
            case Buttons::A_FLAG :
                m_gameFlags.set(ADVANCE_GAME_FLAG);
                break;

            case Buttons::START_FLAG:
                m_isRunning = false;
                State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
                break;

            case Buttons::UP_FLAG:
                if (!m_optionEntered) {
                    m_option--;
                    if (m_option < 0) {
                        m_option = 0;
                    }
                } 
                else {
                    if (m_option == 1) {
                        m_password[m_selectedLetter]++;
                        checkLetterBounds(m_password[m_selectedLetter]);
                    } 
                    else if (m_option == 2) {
                         m_username[m_selectedLetter]++;
                        checkLetterBounds(m_username[m_selectedLetter]);
                    }
                }
                break;

            case Buttons::DOWN_FLAG:
                if (!m_optionEntered) {
                    m_option++;
                    if (m_option > 2) {
                        m_option = 2;
                    }
                }
                else {
                    if (m_option == 1) {
                        m_password[m_selectedLetter]++;
                        checkLetterBounds(m_password[m_selectedLetter]);
                    }
                    else if (m_option == 2) {
                        m_username[m_selectedLetter]--;
                        checkLetterBounds(m_username[m_selectedLetter]);
                    }
                    
                }

                break;

            case Buttons::LEFT_FLAG:
                if (m_optionEntered && m_option > 0) {
                    m_selectedLetter--;
                    if (m_selectedLetter < 0) {
                        m_selectedLetter = 0;
                    }
                }
                    
                break;

            case Buttons::RIGHT_FLAG:
                if (m_optionEntered && m_option > 0) {
                    m_selectedLetter++;
                    if (m_selectedLetter > m_maxLetter) {
                        m_selectedLetter = m_maxLetter;
                }
                    
                }
                
                break;

            case Buttons::B_FLAG:
                m_optionEntered = false;
                break;

            default:
                m_letterIncrement = 0;
                break;
        }
        ThisThread::sleep_for(50ms);
    }
}

//Updates the screen immediately when the SCREEN_UPDATE_FLAG is set (this thread has the highest priority)
void WifiMenu::update(){
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    while (m_isRunning)
    {
        m_gameFlags.wait_any(SCREEN_UPDATE_FLAG, osWaitForever);
        m_displayManager.updateScreen(&m_canvas->c_main);
    }
}

void WifiMenu::game() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;
    
    while (m_isRunning) {
        Serial.println(m_selectedLetter);
        
        //Enters the selected option when A button pressed
        uint32_t result = m_gameFlags.get();
        if (result == ADVANCE_GAME_FLAG) {
            m_optionEntered = true;
            m_gameFlags.clear(ADVANCE_GAME_FLAG);
        }

        // Display the password screen and sets letter edit ranges
        if (m_optionEntered && m_option == 1) {
            m_canvas->drawScreen2();
            m_gameFlags.set(SCREEN_UPDATE_FLAG);

            m_maxLetter = 14;  //Max selectable letter in password
            setASCIIBounds(40, 255);
            Serial.println(m_maxLetter);
            Serial.println(m_selectedLetter);
        }

        // Display the set name screen and sets letter edit ranges
        else if (m_optionEntered && m_option == 2) {
            m_canvas->drawScreen3();
            m_gameFlags.set(SCREEN_UPDATE_FLAG);

            m_maxLetter = 3;  //Max selectable letter in name
            setASCIIBounds(65, 122);

        }

        else if (!m_optionEntered) {
            m_canvas->drawScreen1();
            m_gameFlags.set(SCREEN_UPDATE_FLAG);
        }
        

        ThisThread::sleep_for(150ms); 
    }

    //Waits for button A press to exit the game
    //m_gameFlags.wait_any(ADVANCE_GAME_FLAG, osWaitForever, true);

    //Return to main menu when game finish
    m_isRunning = false;
    State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
}

void WifiMenu::run() {
    using namespace rtos;
    using namespace mbed;

    m_option = 0;

    //Starts the threads
    m_isRunning = true;

#ifdef DEBUG
    Serial.println("NU RUN JAG");
#endif

    t_gameLogic = new Thread;
    t_screenUpdate = new Thread;
    t_userInput = new Thread;

    m_canvas = new WifiMenuUI(this);

    t_gameLogic->start(mbed::callback(this, &WifiMenu::game));
    t_userInput->start(mbed::callback(this, &WifiMenu::handleInput));
    t_screenUpdate->start(mbed::callback(this, &WifiMenu::update));

}

void WifiMenu::stop() {
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


void WifiMenu::setName() {

}

void WifiMenu::checkLetterBounds(char &letter) {
    if (letter > m_maxASCII) {
        letter = m_maxASCII;
    }
    else if (letter < m_minASCII) {
        letter = m_minASCII;
    }
}

void WifiMenu::setASCIIBounds(int min, int max) {
    m_minASCII = min;
    m_maxASCII = max;
}







