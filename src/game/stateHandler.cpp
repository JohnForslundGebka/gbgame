#include "stateHandler.h"
/**
 * @brief Handle inputs for the current state.
 *
 * This method delegates the input handling to the active state.
 */
void StateHandler::handleInput() {
    m_currentState->handleInput();
}

void StateHandler::updateState() {
    m_currentState->update();
}
/**
     * @brief Run the active state.
     *
     *
     *
     */
void StateHandler::run(){
    if (m_currentState->m_isRunning)
        m_currentState->stop();

    m_currentState->run();
}
/**
    * @brief Set the current state of the game or application.
    *
    * @param currentState The new state to be managed.
    */
void StateHandler::setState(State &currentState) {
    m_currentState->stop();
    m_currentState = &currentState;
    m_currentState->run();
}