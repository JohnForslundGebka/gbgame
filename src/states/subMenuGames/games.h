/**
 * @class Games
 * @brief Handles the games menu
 *
 * Is used to select different states to start from the games sub menu
 */
#ifndef GBGAME_GAMES_H
#define GBGAME_GAMES_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "states/subMenuGames/gamesUi.h"
#include "states/globalStates.h"
#include "hardware/buttons.h"

class Games : public State {
public:
    /**
    * Handles button input to navigate through menu items.
    */
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

    /**
    * Stops all the running threads, and cleans upp and deletes the pointers
    */
    void stop() override;

    //consructor
    explicit Games();
    int m_selectedState{};
private:
    Canvas *m_pntrCanvas = nullptr;
    GamesUI *m_canvas = nullptr;
    rtos::Thread* t_gfx = nullptr;
    rtos::Thread* t_move= nullptr;
    class rtos::EventFlags m_gameFlags;
};

#endif //GBGAME_GAMES_H
