#include "stateHandler.h"

void StateHandler::handleInput() {
    m_currentState->handleInput();
}

void StateHandler::updateState() {
    m_currentState->update();
}

void StateHandler::run(){
    m_currentState->stop();
    m_currentState->run();
}

void StateHandler::setState(State &currentState) {
    m_currentState->stop();
    m_currentState = &currentState;
    m_currentState->run();
}