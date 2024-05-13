/**
 * @class MainMenu
 * @brief Handles the main menu state of the application.
 *
 * Is used to select different states to start
 */
#ifndef GBGAME_MAINMENU_H
#define GBGAME_MAINMENU_H
#include "core/state.h"
#include "mainMenuUi.h"
#include "hardware/buttons.h"

class MainMenu : public State{
public:
    void handleInput() override;

    void update() override;

    void run() override;

    void stop() override;

    explicit MainMenu();
    int m_selectedState = 1;

private:
     MainMenuUi canvas;
     Canvas *m_pntrCanvas;

     Thread* t_gfx;
     Thread* t_move;
     class EventFlags m_isDoneMoving;
};
#endif //GBGAME_MAINMENU_H
