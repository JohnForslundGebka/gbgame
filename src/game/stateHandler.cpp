#include "stateHandler.h"
#include "core/state.h"

StateHandler::StateHandler(): m_mainThread(osPriorityAboveNormal,1024), m_currentState(&mainMenu) {
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
        uint32_t state = State::stateFlags.wait_any(MAIN_MENU | DISTANCE_GAME, osWaitForever, true);
        switch (state){
            case MAIN_MENU :
                m_currentState->stop();
                m_currentState = &mainMenu;
                run();
                break;
            case DISTANCE_GAME :
                m_currentState->stop();
                m_currentState = &distanceGame;
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
     run();
    m_mainThread.start(callback(this,&StateHandler::updateState));

}
