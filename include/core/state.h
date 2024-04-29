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
class State {
public:
    //Virtual functions that handles inputs and updates
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
    volatile bool m_isRunning = false;
};

#endif //GBGAME_STATE_H
