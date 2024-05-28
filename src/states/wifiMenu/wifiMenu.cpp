#include "wifiMenu.h"
#include "wifiMenuUI.h"
#include "rtos.h"
#include "mbed.h"
#include <string>


// Constructor, initializes the state with it's name "Wifi Menu"
WifiMenu::WifiMenu():  State("Wifi Menu"){}

void WifiMenu::handleInput() {
    using namespace rtos;
    using namespace mbed;

    m_optionEntered = false;

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

        // Handle input and update positions
        switch (result) {
            case Buttons::A_FLAG :
                //Enters the selected option when A button pressed
                //If an option is selected, A button executes whatever it is (login function etc.)
                
                if (m_optionEntered) {
                    m_execute = true;
                }   

                if (!m_optionEntered){
                    m_optionEntered = true;
                }
                Buttons::states.clear(Buttons::A_FLAG);
                break;

            case Buttons::START_FLAG:
                m_isRunning = false;
                State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
                Buttons::states.clear(Buttons::START_FLAG);
                break;

            case Buttons::UP_FLAG:
                if (!m_optionEntered) {
                    m_option--;

                    if (m_option < 0) { m_option = 0; }
                }
                else if (m_optionEntered && m_option == NEW_WIFI) {
                    m_selectedNetwork--;
                    if (m_selectedNetwork < 0) { m_selectedNetwork = 0; }
                }

                if (m_optionEntered) {
                    p_selectedText[m_selectedLetter]++;
                    checkLetterBounds(p_selectedText[m_selectedLetter]);
                }
                Buttons::states.clear(Buttons::UP_FLAG);
                break;

            case Buttons::DOWN_FLAG:
                if (!m_optionEntered) {
                    m_option++;
                    if (m_option > m_optionMAX) { m_option = m_optionMAX; }
                } 
                else if (m_optionEntered && m_option == NEW_WIFI) {
                    m_selectedNetwork++;
                    if (m_selectedNetwork > m_networkList.size()) { m_selectedNetwork = m_networkList.size(); }
                }
    
                if (m_optionEntered) {
                    p_selectedText[m_selectedLetter]--;
                    checkLetterBounds(p_selectedText[m_selectedLetter]);
                }
                Buttons::states.clear(Buttons::DOWN_FLAG);
                break;

            case Buttons::LEFT_FLAG:
                if (m_optionEntered && m_option > 0) {
                    m_selectedLetter--;
                    if (m_selectedLetter < 0) {
                        m_selectedLetter = 0;
                    }
                }
                Buttons::states.clear(Buttons::LEFT_FLAG);
                break;

            case Buttons::RIGHT_FLAG:
                if (m_optionEntered && m_option > 0) {
                    m_selectedLetter++;
                    if (m_selectedLetter > m_maxLetter) {
                        m_selectedLetter = m_maxLetter;
                }
                    
                }
                Buttons::states.clear(Buttons::RIGHT_FLAG);
                break;

            case Buttons::B_FLAG:
                m_optionEntered = false;
                Buttons::states.clear(Buttons::B_FLAG);
                break;

            default:
                break;
        }
        m_gameFlags.set(ADVANCE_GAME_FLAG);
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
        //ThisThread::sleep_for(100ms); 
    }
}

void WifiMenu::game() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;
    
    while (m_isRunning) {

        m_gameFlags.wait_any(ADVANCE_GAME_FLAG,osWaitForever, true);
        
        if (m_optionEntered && m_option == NEW_WIFI) {


            //Scan networks and add to vector
            if (m_getNetworks) {
                m_canvas->drawNetworks();
                m_gameFlags.set(SCREEN_UPDATE_FLAG);
                rtos::ThisThread::sleep_for(40ms);
                wifi.getNetworkNames(m_networkList);
                m_getNetworks = false;
            }

            //Sets the number of maximum selectable options
            m_optionMAX = m_networkList.size() - 1;

            m_canvas->drawScreenNetworks();
            m_gameFlags.set(SCREEN_UPDATE_FLAG);

            if (m_execute) {
                // Save network name as string to use for login
                m_saved_network = m_networkList[m_selectedNetwork].c_str();
                std::strncpy(wifi.ssid,m_saved_network.c_str(),m_saved_network.size());

                if (flash::writeToFlash(m_saved_network, "network")) {
                    Serial.println("Network saved to flash");
                }

                Serial.println("Network selected");
                m_getNetworks = true;
                m_execute = false;
                m_optionEntered = false;
                m_option = 0;
            }

            ThisThread::sleep_for(30);
        }
        

        // Display the password screen and sets letter edit ranges
        if (m_optionEntered && m_option == PASSWORD) {
            p_selectedText = m_password;

            m_maxLetter = 14;                //Max selectable letter in password
            setASCIIBounds(40, 255);         //Sets ASCII range for letter input

            m_canvas->drawScreen2();
            m_gameFlags.set(SCREEN_UPDATE_FLAG);

            //in here the password is saved to flash and to the data transmit class
            if (m_execute) {
                //Null terminate the password and save it to the m_string_password string
                m_password[m_selectedLetter + 1] = '\0';
                updatePasswordString();

                wifi.password = m_password;
                //Save to password to flash
                if (flash::writeToFlash(m_string_password, "password")) {
                    Serial.println("Password saved to flash");
                }

                //Clear flags and go back to wifi menu
                m_option = 0;
                m_execute = false;
                m_optionEntered = false; 
            }
        }

        // Display the set name screen and sets letter edit ranges
        else if (m_optionEntered && m_option == SET_NAME) {
            p_selectedText = m_username;

            m_maxLetter = 3;                //Max selectable letter in name
            setASCIIBounds(65, 122);        //Set range for ascii letter input

            m_canvas->drawScreen3();
            m_gameFlags.set(SCREEN_UPDATE_FLAG);


            if (m_execute) {
                //Here the username is saved to flash and update the GlobalSettings userName variable
                wifi.userName = m_username;
                // Save username to flash memory
                std::string m_string_username(m_username);
                if (flash::writeToFlash(m_string_username, "username")) {
                    Serial.println("username saved to flash");
                }

                //Clear flags and go back to wifi menu
                m_option = 0;
                m_optionEntered = false;
                m_execute = false;
                m_gameFlags.set(ADVANCE_GAME_FLAG);
            }
        }

        // Display the login last screen and tries to connect to last wifi
        else if (m_optionEntered && m_option == LOGIN_LAST) {

            // Call login function with saved network and password
            Serial.println("Connecting...");
            m_canvas->drawScreen4();
            m_gameFlags.set(SCREEN_UPDATE_FLAG);
            Serial.println(wifi.userName);
            Serial.println(wifi.ssid);
            Serial.println(wifi.password);

            wifi.init();
            Serial.println("tried to connect...");


            //Clear flags and go back to wifi menu
            m_option = 0;
            m_execute = false;
            m_optionEntered = false;
            m_gameFlags.set(ADVANCE_GAME_FLAG);
        }

        else if (!m_optionEntered) {
            m_optionMAX = 3;                //Sets maximum number of selectable options

            m_canvas->drawScreen1();
            m_gameFlags.set(SCREEN_UPDATE_FLAG);
        }

        ThisThread::sleep_for(100ms); 
    }

    m_execute = false; 

    //Return to main menu when game finish
    m_isRunning = false;
    State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
}

void WifiMenu::run() {
    using namespace rtos;
    using namespace mbed;

    if(m_firstRun){
        using namespace GlobalSettings;

        wifi.userName = flash::readFromFlash("username");
        wifi.ssid = flash::readFromFlash("network");  // replace with your wifi ssid
        wifi.password = flash::readFromFlash("password");  // replace with your wifi password

        wifi.userName.toCharArray(m_username, sizeof(m_username));

        m_firstRun = false;
    }

    m_option = 0;

    m_gameFlags.set(ADVANCE_GAME_FLAG);

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
    
    t_userInput->set_priority(osPriorityAboveNormal1);

}

void WifiMenu::stop() {
    using namespace std::chrono;

#ifdef DEBUG
    Serial.println("NU STOPPAR MIC GAME");
#endif

    m_isRunning = false;
    m_getNetworks = true;
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

void WifiMenu::updatePasswordString() {
    m_string_password = "";  // Clear existing string_password
    for (int i = 0; i < sizeof(m_password); i++) {
        if (m_password[i] == '\0') {
            break;  // Stop copying if a null terminator is found
        }
        m_string_password += m_password[i];  // Append character to string
    }
}


