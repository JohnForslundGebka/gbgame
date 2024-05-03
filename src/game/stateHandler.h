//stateHandler.h
/**
 * @brief This is a class that is responsible for running and stopping the different states of the machine
 *
 *
 *   The StateHandler class is designed to control the transition between different states
 *   of a game or application, such as menus, gameplay, pause screens, etc. It ensures that
 *   the current state is correctly managed and that state transitions are handled smoothly.
 *
 *
 *
 *
 *
 */
#ifndef GBGAME_STATEHANDLER_H
#define GBGAME_STATEHANDLER_H
#include "core/state.h"
#include "mainMenu.h"

class StateHandler {
public:
    //constructor
    StateHandler();

   //
   [[noreturn]] void updateState();
    void run();
    void init();

private:
    // Main thread object
    Thread m_mainThread;

    //Pointer to the current state that is running at the moment
    State* m_currentState;

    //all available states
    MainMenu mainMenu;
};
#endif //GBGAME_STATEHANDLER_H