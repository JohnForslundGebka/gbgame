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
    int m_selectedState{};

private:
     MainMenuUi *m_canvas = nullptr;
     Canvas *m_pntrCanvas = nullptr;

     rtos::Thread* t_gfx = nullptr;
     rtos::Thread* t_move = nullptr;
     class rtos::EventFlags m_gameFlags;
};
#endif //GBGAME_MAINMENU_H
