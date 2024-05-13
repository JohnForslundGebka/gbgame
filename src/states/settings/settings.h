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

    explicit Settings();

    int m_selectedState{};
private:
    SettingsUi m_canvas;
    Canvas *m_pntrCanvas{};

    Thread* t_gfx{};
    Thread* t_move{};
    class EventFlags m_gameFlags;
};
#endif //GBGAME_SETTINGS_H
