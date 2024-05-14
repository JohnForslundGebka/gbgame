#ifndef GBGAME_SETTINGS_H
#define GBGAME_SETTINGS_H
#include "core/state.h"
#include "settingsUi.h"
#include "hardware/buttons.h"

class Settings : public State{
public:
    void handleInput() override;

    void update() override;

    void run() override;

    void stop() override;

    void game();
    void newHandPos();

    explicit Settings();

    int m_selectedState{};
    int m_handPos{};

    volatile bool m_vibraOn = false;
    volatile bool m_soundOn = false;
private:
    SettingsUi m_canvas;
    Canvas *m_pntrCanvas{};

    Thread* t_gfx{};
    Thread* t_move{};
    Thread *t_gameLogic{};        //Thread that handles the game logic/order

    class EventFlags m_gameFlags;

    const uint32_t handMove = (1UL << 5);


};
#endif //GBGAME_SETTINGS_H
