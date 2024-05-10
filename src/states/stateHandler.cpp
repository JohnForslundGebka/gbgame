#include "stateHandler.h"


StateHandler::StateHandler(): m_mainThread(osPriorityAboveNormal,1024), m_currentState(GlobalStates::stateList[0]) {
}

/**
 * @brief thread function that waits for a flag to be set, then starts the corresponding state
 *
 * Will reset all flags after starting a state, then the thread will wait/sleep until a new flag has been set
 * @param state stores the flag that was set in the Eventflag object.
 * @param State::stateFlags is a static variable located in the state.h base class
 */



[[noreturn]] void StateHandler::updateState() {
    while (true){
#ifdef DEBUG
        Serial.println("NU KOM JAG IN I UPPDATESTATE I STATEHANDLER");
#endif

        uint32_t state = State::stateFlags.wait_any(MAIN_MENU | DISTANCE_GAME, osWaitForever, true);
        switch (state){
            case MAIN_MENU :

#ifdef DEBUG
                Serial.println("NU BÖRJAR JAG ATT BYTA STATE TILL MAIN MENU");
#endif

                m_currentState->stop();
              //  m_currentState = &mainMenu;
               m_currentState = GlobalStates::stateList[0];

#ifdef DEBUG
                Serial.println("NU STARTAR STATEHANDLERS MAIN MENU");
#endif

                run();
                break;
            case DISTANCE_GAME :
                m_currentState->stop();
                m_currentState = GlobalStates::stateList[1];
                run();
                break;
            default:
                break;
        }
    }
}

/**
     * @brief Run the active state.
     *
     *
     *
     */
    
void StateHandler::run(){
    if (m_currentState->m_isRunning) //check if state is already running
        m_currentState->stop();

    m_currentState->run();
}
/**
 * @brief Starts up the main thread that is responsible for changing the state
 *
 *
 */

void StateHandler::init() {
     delay(300);
     run();
     m_mainThread.start(mbed::callback(this,&StateHandler::updateState));
}
