#ifndef GBGAME_STATEHANDLER_H
#define GBGAME_STATEHANDLER_H
#include "core/state.h"

class StateHandler {
public:
    //constructor
    explicit StateHandler(State* currentState) : m_currentState(currentState) {}

    void setState();
    void handleInput();
    void updateState();
    void run();

    //a pointer to the current state that is running at the moment
    State* m_currentState;

private:


};
#endif //GBGAME_STATEHANDLER_H
