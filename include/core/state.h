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
    /**
 *
 * @brief Constructor
 *
 * @param m_stateName Is the name of the state, that name will be printed in certain menus
 * @param m_flagName is a uint32_t with a specific bit that is "set". That will later be used by the statehandler class,
 *                   to select which state it should run and stop
 * @param instanceCounter is a static variable that increases by 1 each time a new state is created
 */
    State(String stateName) : m_stateName(stateName) {
        m_flagName = 1UL << instanceCounter;
        instanceCounter++;
    }

    //Virtual functions that handles inputs and updates
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void run() = 0;
    virtual void stop() = 0;

    static rtos::EventFlags stateFlags;

    volatile bool m_isRunning = false;
    //name of the state, to be used in menus
    const String m_stateName;

    //flag used for exiting state
    uint32_t STOP_RUNNING = (1UL << 15);


    uint32_t getFlagName() const {
        return m_flagName;
    }

    DisplayManager & m_displayManager = DisplayManager::getInstance();
protected:
    // Unique bit set for this instance
    uint32_t m_flagName;

    static uint32_t instanceCounter;  // Tracks the number of instances
};

#endif //GBGAME_STATE_H
