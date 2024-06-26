#include "multiplayerMenu.h"
#include "rtos.h"
#include "mbed.h"
#include <string>
#include "functionality/challengeHandler.h"
#include "wifi/dataTransmit.h"



// Constructor, initializes the state with it's name "Wifi Menu"
MultiplayerMenu::MultiplayerMenu() :  State("Multiplayer"){}

void MultiplayerMenu::handleInput() {
    using namespace rtos;
    using namespace mbed;

    m_optionEntered = false;

    while (m_isRunning) {
        using namespace std::chrono;

        uint32_t result = Buttons::states.wait_any(Buttons::START_FLAG  | Buttons::A_FLAG | Buttons::UP_FLAG 
                                                | Buttons::DOWN_FLAG | Buttons::B_FLAG, osWaitForever, false);

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

                if (!m_optionEntered) {
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
                (*m_optionPtr)--;
                if (*m_optionPtr < 0) { *m_optionPtr = 0; } 
                Buttons::states.clear(Buttons::UP_FLAG);               
                break;

            case Buttons::DOWN_FLAG:
                (*m_optionPtr)++;
                if (*m_optionPtr > m_optionMAX) { *m_optionPtr = m_optionMAX; }
                Buttons::states.clear(Buttons::DOWN_FLAG);
                break;

            case Buttons::B_FLAG:
                m_optionEntered = false;
                m_option = 0;
                Buttons::states.clear(Buttons::B_FLAG);
                break;

            default:
                break;
        }
        m_gameFlags.set(INPUT_UPDATE_FLAG);
        ThisThread::sleep_for(50ms);
    }
}

//Updates the screen immediately when the SCREEN_UPDATE_FLAG is set (this thread has the highest priority)
void MultiplayerMenu::update(){
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

void MultiplayerMenu::game() {
    ChallengeHandler &challengeHandler = ChallengeHandler::getInstance();


    DataTransmit &wifi = DataTransmit::getInstance();

    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;

    while (m_isRunning) {

        m_gameFlags.wait_any(INPUT_UPDATE_FLAG,osWaitForever, true);


        if (m_optionEntered) {

            m_optionPtr = &m_subOption;

            if (m_option == LOBBY) {

                m_canvas->drawLobbyList();
                m_gameFlags.set(SCREEN_UPDATE_FLAG);
                
                //Sets the number of maximum selectable options in the lobby list
                m_optionMAX = m_lobbyList.size() - 1;

                //This code executes when pressing A in the lobby menu
                if (m_execute) {
                    m_execute = false;
                    m_optionEntered = false;
                    m_option = 0;

                    if(m_lobbyList.size()>0){
                    //Use m_subOption to index which challenge to start.
                    challengeHandler.respondToChallenge(m_lobbyList[m_subOption]);}
                }
            }

            
            else if (m_option == NEW) {

                m_canvas->drawScreen3();
                m_gameFlags.set(SCREEN_UPDATE_FLAG);

                if (m_execute) {
                
                    //Clear flags
                    m_option = 0;
                    m_execute = false;
                    m_optionEntered = false; 

                    challengeHandler.startingAChallenge = true;

                    State::stateFlags.set(GlobalStates::stateList[INDEX_GAMES]->getFlagName());
                }
            }

            // Display the set name screen and sets letter edit ranges
            else if (m_option == MY_GAMES) {
                m_optionMAX = m_myGamesList.size() - 1;
                m_canvas->drawMyGames();
                m_gameFlags.set(SCREEN_UPDATE_FLAG);

                if (m_execute) {
                    m_canvas->drawChallengeInfo(m_myGamesList[m_subOption]);
                    Buttons::states.clear(Buttons::ButtonFlags::A_FLAG);
                    ThisThread::sleep_for(2s);
                    Buttons::states.wait_any(Buttons::ButtonFlags::A_FLAG);

                    if (m_myGamesList[m_subOption]->m_played) {
                        m_canvas->drawWaitingScreen();
                        m_gameFlags.set(SCREEN_UPDATE_FLAG);
                        //Removes the challenge from database
                        wifi.removeChallengeFromData(m_myGamesList[m_subOption]->m_ID);
                        //Clear the local vector of challenges
                        m_myGamesList.clear();
                        //Get the new vector of challenges
                        challengeHandler.getChallengesFromLobby(m_lobbyList);
                        for (auto &challenge : challengeHandler.challenges) {
                            if(challenge.m_player1Name == wifi.userName) {
                                m_myGamesList.push_back(&challenge);
                            }
                        }
                    }
                    //Clear flags
                    m_execute = false;
                    m_gameFlags.set(INPUT_UPDATE_FLAG);
                }
            }
        }
        else {
            m_optionMAX = 2;                //Sets maximum number of selectable options
            m_optionPtr = &m_option;
            m_canvas->drawScreen1();
            m_gameFlags.set(SCREEN_UPDATE_FLAG);
        }
        
        ThisThread::sleep_for(100ms); 
    }
   

    m_execute = false; 
}


void MultiplayerMenu::run() {
    using namespace rtos;
    using namespace mbed;
    using namespace std::chrono;
    DataTransmit &wifi = DataTransmit::getInstance();
    m_canvas = new MultiplayerMenuUI(this);
    m_myGamesList.clear();

    if(!wifi.wifiIsConnected){
        m_canvas->drawNotConnectedScreen(); //draw wifi message screen
        m_displayManager.updateScreen(&m_canvas->c_main);
        ThisThread::sleep_for(std::chrono::seconds(3));
        State::stateFlags.set(GlobalStates::stateList[INDEX_MAIN_MENU]->getFlagName());
    } else {
        m_option = 0;
        m_optionEntered = false;
        m_execute = false;
        
        m_canvas->drawWaitingScreen();
        m_displayManager.updateScreen(&m_canvas->c_main);

        //get all the challenges from the database
        ChallengeHandler &challengeHandler = ChallengeHandler::getInstance();
        challengeHandler.getChallengesFromLobby(m_lobbyList);

        //fill m_myGamesList vector with pointers to the users challenges
        for (auto &challenge : challengeHandler.challenges)
        {
            if(challenge.m_player1Name == wifi.userName) {
                m_myGamesList.push_back(&challenge);
            }
        }

        //Starts the threads
        m_isRunning = true;
        t_gameLogic = new Thread;
        t_screenUpdate = new Thread;
        t_userInput = new Thread;
        t_userInput->start(mbed::callback(this, &MultiplayerMenu::handleInput));
        t_screenUpdate->start(mbed::callback(this, &MultiplayerMenu::update));
        t_gameLogic->start(mbed::callback(this, &MultiplayerMenu::game));
 }
}

void MultiplayerMenu::stop() {
    using namespace std::chrono;

    m_isRunning = false;
    //set flags, to not be stuck in waiting
    Buttons::states.set(Buttons::START_FLAG | Buttons::A_FLAG);
    m_gameFlags.set(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);

    // Finnish threads and clean upp pointers
    if(t_gameLogic) {
        t_gameLogic->join();
        delete t_gameLogic;
        t_gameLogic = nullptr;
    }

    if(t_userInput){
        t_userInput->join();
        delete t_userInput;
        t_userInput = nullptr;
    }

    if(t_screenUpdate){
        t_screenUpdate->join();
        delete t_screenUpdate;
        t_screenUpdate = nullptr;
    }
   
    delete m_canvas; // Properly delete the m_canvas when stopping
    m_canvas = nullptr;

    //clear all flags before exiting
    m_gameFlags.clear(SCREEN_UPDATE_FLAG | ADVANCE_GAME_FLAG);
    Buttons::states.clear(Buttons::START_FLAG | Buttons::A_FLAG);

    rtos::ThisThread::sleep_for(10ms);
}



