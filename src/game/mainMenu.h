#ifndef GBGAME_MAINMENU_H
#define GBGAME_MAINMENU_H
#include "core/state.h"
#include "ui/canvas.h"
#include "hardware/buttons.h"

class MainMenu : public State{
public:
    void handleInput() override;

    void update() override;

    void run() override;

    void stop() override;

    explicit MainMenu();

private:
     Canvas m_textCanvas;
     Canvas m_handCanvas;
     Canvas *m_pntrCanvas;

     class Thread m_gfx;
     class Thread m_move;
     class EventFlags m_isDoneMoving;

};
#endif //GBGAME_MAINMENU_H
