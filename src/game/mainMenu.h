#ifndef GBGAME_MAINMENU_H
#define GBGAME_MAINMENU_H
#include "core/state.h"
#include "ui/canvas.h"

class MainMenu : public State{
public:
    void handleInput() override;

    void update() override;

    void run() override;

    void stop() override;

    explicit MainMenu();
private:
     Canvas m_canvas;

};
#endif //GBGAME_MAINMENU_H
