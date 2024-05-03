#ifndef GBGAME_MAINMENU_H
#define GBGAME_MAINMENU_H
#include "core/state.h"
#include "ui/canvas.h"
#include "ui/mainMenu/canvasMainMenu1.h"
#include "ui/mainMenu/canvasMainMenu2.h"
#include "hardware/buttons.h"


class MainMenu : public State{
public:
    void handleInput() override;

    void update() override;

    void run() override;

    void stop() override;

    explicit MainMenu();

private:
     CanvasMainMenu1 m_textCanvas;
     CanvasMainMenu2 m_handCanvas;
     Canvas *m_pntrCanvas;

     class Thread m_gfx;
     class Thread m_move;
     class EventFlags m_isDoneMoving;

};
#endif //GBGAME_MAINMENU_H
