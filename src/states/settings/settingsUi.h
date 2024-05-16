#ifndef GBGAME_SETTINGSUI_H
#define GBGAME_SETTINGSUI_H
#include "ui/canvas.h"
#include "ui/images.h"
#include "core/state.h"
#include "states/globalStates.h"

class Settings; //forward declaration

class SettingsUi {
public:
    /**
      *
      * @brief canvases that will be used to draw gfx on the display
      *
      * @param c_handPos0
      * @param c_handPos1and2
      */
    Canvas c_handPos0;
    Canvas c_handPos1and2;

    explicit SettingsUi(Settings *p);

    String textField[3];

    void init();
    void updateText();
    void drawHandPos1();
    void drawHandPos2();

private:
    Settings *parentState;
    void updateTextFields();
};


#endif //GBGAME_SETTINGSUI_H
