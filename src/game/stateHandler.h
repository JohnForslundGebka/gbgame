#ifndef GBGAME_STATEHANDLER_H
#define GBGAME_STATEHANDLER_H

class StateHandler {
public:
    //constructor
    explicit StateHandler(State* currentState) : m_currentState(currentState) {}

    void setState();
    void handleInput();
    void updateState();
    void opperator();

private:
    //a pointer to the current state that is running at the moment
    State* m_currentState;

};


#endif //GBGAME_STATEHANDLER_H
