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

    State() {
        m_flagName = 1UL << instanceCounter;
        instanceCounter++;
    }

    //Virtual functions that handles inputs and updates
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
    static EventFlags stateFlags;


    uint32_t getFlagName() const {
        return m_flagName;
    }

    DisplayManager & m_displayManager = DisplayManager::getInstance();
    volatile bool m_isRunning = false;
    uint32_t STOP_RUNNING = (1UL << 15);
protected:
    uint32_t m_flagName;
    static uint32_t instanceCounter;  // Tracks the number of instances
              // Unique bit set for this instance

};



#endif //GBGAME_STATE_H
