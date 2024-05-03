#include "stateHandler.h"
#include "core/state.h"

StateHandler::StateHandler(): mainThread(osPriorityAboveNormal,1024), m_currentState(&mainMenu) {
}

void StateHandler::updateState() {

    while (true){
        uint32_t state = State::stateFlags.wait_any(MAIN_MENU | DISTANCE_GAME, osWaitForever, true);
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
     run();
     mainThread.start(callback(this,&StateHandler::updateState));

}
