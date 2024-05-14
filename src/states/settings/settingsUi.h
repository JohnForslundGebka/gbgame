#ifndef GBGAME_SETTINGSUI_H
#define GBGAME_SETTINGSUI_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "states/globalStates.h"

class Settings; //forward declaration

class SettingsUi {
public:
    Canvas c_handPos0;
    Canvas c_handPos1and2;
    explicit SettingsUi(Settings *p);

    String textField[3];

    void init();
    void updateText();
private:
    Settings *parentState;
    void updateTextFields();
};


#endif //GBGAME_SETTINGSUI_H
