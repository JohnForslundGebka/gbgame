#include "stateHandler.h"


StateHandler::StateHandler(): m_mainThread(osPriorityAboveNormal,1024), 
                            m_currentState(GlobalStates::stateList[INDEX_MAIN_MENU]) {
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
        //Here the stateHandler will loop through all states until it fins the one that has flagged
        uint32_t result = State::stateFlags.wait_any(GlobalStates::ALL_STATE_FLAGS, osWaitForever, true);
        for(auto &newState : GlobalStates::stateList)
        {
            if (result == newState->getFlagName()) //if the state is found, stop the last state and start the new
            {
                m_currentState->stop();
                m_currentState = newState;
                run();
                result = 0;
                break;
            }
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
