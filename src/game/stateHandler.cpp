#include "stateHandler.h"
/**
 * @brief Handle inputs for the current state.
 *
 * This method delegates the input handling to the active state.
 */

void StateHandler::updateState() {
    while (true){
        uint32_t state = State::stateFlag.wait_any(MAIN_MENU | DISTANCE_GAME,  osWaitForever, true);
        switch (state){
            case MAIN_MENU :
             m_currentState = &mainMenu;
             run();
                break;
            case DISTANCE_GAME :
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

void StateHandler::init() {
     mainThread.start(callback(this,&updateState));

}
