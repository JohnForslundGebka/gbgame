/**
 * @class Settings
 * @brief Is used to display certain settings of the systems
 *
 *  currently in a not completed state, but will in the future be used to log into wifi etc
 */
#ifndef GBGAME_SETTINGS_H
#define GBGAME_SETTINGS_H
#include "core/state.h"
#include "settingsUi.h"
#include "hardware/buttons.h"

class Settings : public State{
public:
    void handleInput() override;

    /**
     * Updates the display based on the current state of the canvas.
     */
    void update() override;

    /**
   *
   * @brief Starts all the threads that the state will use
   *
   * @param *m_canvas is a pointer to the UI class than handles all the screen operations
   */
    void run() override;

    void stop() override;

    void newHandPos();

    explicit Settings();

    /**
      *
      * @brief variables used for choosing the next state that should start
      *
      * @param m_selectedState will change value depending which state is chosen in the menu
      * @param m_handPos is changed by pressing "up" or "down". It controls a small state machine that determines
      * which canvas will be printed to the display
      */
    int m_selectedState{};
    int m_handPos{};

    //Variables used for turning the vibrations and sound on or off
    volatile bool m_vibraOn = false;
    volatile bool m_soundOn = false;
private:
    SettingsUi* m_canvas = nullptr;
    Canvas *m_pntrCanvas{};

    rtos::Thread* t_gfx = nullptr;
    rtos::Thread* t_move= nullptr;

    class rtos::EventFlags m_gameFlags;

    const uint32_t handMove = (1UL << 5);


};
#endif //GBGAME_SETTINGS_H
