#ifndef GBGAME_SETTINGSUI_H
#define GBGAME_SETTINGSUI_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "states/globalStates.h"

class Settings; //forward declaration

class SettingsUi {
public:
    Canvas c_canvas;
    explicit SettingsUi(Settings *p);

    String textField[5];

    void init();
    void draw();
private:
    Settings *parentState;
    void updateTextFields();
};


#endif //GBGAME_SETTINGSUI_H
