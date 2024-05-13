//state.h
/**
 * @brief This is the base class for the states of the machine
 *        They could be Main Menu, setting, etc
 *
 *      Each state class can go into the "stateholder" class
 *
 *
 *
 *
 *
 */
#ifndef GBGAME_STATE_H
#define GBGAME_STATE_H
#include "hardware/displayManager.h"
#include "states/globalStates.h"

class State {
public:
    //Constructor
    State(String stateName) : m_stateName(stateName) {
        m_flagName = 1UL << instanceCounter;
        instanceCounter++;
    }

    //Virtual functions that handles inputs and updates
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void run() = 0;
    virtual void stop() = 0;

    static EventFlags stateFlags;

    volatile bool m_isRunning = false;

    //flag used for exiting state
    uint32_t STOP_RUNNING = (1UL << 15);


    uint32_t getFlagName() const {
        return m_flagName;
    }

    DisplayManager & m_displayManager = DisplayManager::getInstance();
protected:
    // Unique bit set for this instance
    uint32_t m_flagName;
    //name of the state, to be used in menus
    const String m_stateName;
  //  char stateName[15];  // C-style string that holds the name of the state
    static uint32_t instanceCounter;  // Tracks the number of instances
};

#endif //GBGAME_STATE_H
