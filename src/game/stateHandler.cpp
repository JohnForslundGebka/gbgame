#include "stateHandler.h"

void StateHandler::handleInput() {
    m_currentState->handleInput();
}

void StateHandler::updateState() {
    m_currentState->update();
}

void StateHandler::run(){
    m_currentState->run();
}

