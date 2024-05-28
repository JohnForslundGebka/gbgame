#ifndef GBGAME_WIFI_MENU_UI_H
#define GBGAME_WIFI_MENU_UI_H
#include "ui/canvas.h"
#include "core/macros.h"
#include "core/state.h" // Include State but forward-declare DistanceGame

class WifiMenu; // Forward declaration

class WifiMenuUI {
public:

    explicit WifiMenuUI(WifiMenu *pGame);

    WifiMenu *parentState;
    Canvas c_main;

    void init();
    
    void drawScreen1();           // Draws the first screen
    void drawScreen2();           // Draws new wifi screen
    void drawScreen3();           // Draws set name screen
    void drawScreen4();           // Draws connecting screen
    void drawScreenNetworks();           // Draws connecting screen
    void drawNetworks();

    char m_menuOptions[3][12] = {
        " Lobby",
        "  New",
        "Finished"
    };

private:
    //Bitmap of wifi symbol
    unsigned char PROGMEM image_wifi_3_bars_bits[48] = {0x01,0xf0,0x00,0x06,0x0c,0x00,0x18,0x03,0x00,0x21,0xf0,
                                              0x80,0x46,0x0c,0x40,0x88,0x02,0x20,0x10,0xe1,0x00,0x23,
                                              0xf8,0x80,0x07,0x1c,0x00,0x0c,0x46,0x00,0x05,0xf4,0x00,
                                              0x03,0xb8,0x00,0x01,0x50,0x00,0x00,0xe0,0x00,0x00,0x40,
                                              0x00,0x00,0x00,0x00};

    unsigned char PROGMEM image_music_fast_backward_bits[34] = {0x1f,0xf0,0x08,0x20,0x04,0x40,0x04,0x40,0x02,0x80,0x02,0x80,
                                                              0x01,0x00,0x01,0x00,0x00,0x00,0x1f,0xf0,0x08,0x20,0x04,0x40,
                                                              0x04,0x40,0x02,0x80,0x02,0x80,0x01,0x00,0x01,0x00};

    unsigned char PROGMEM image_music_fast_backward_1_bits[34] = {0x00,0x80,0x00,0x80,0x01,0x40,0x01,0x40,0x02,0x20,0x02,
                                                                0x20,0x04,0x10,0x0f,0xf8,0x00,0x00,0x00,0x80,0x00,0x80,0x01,
                                                                0x40,0x01,0x40,0x02,0x20,0x02,0x20,0x04,0x10,0x0f,0xf8};                                          

};

#endif //GBGAME_WIFI_MENU_UI_H
