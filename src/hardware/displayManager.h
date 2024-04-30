#ifndef GBGAME_DISPLAYMANAGER_H
#define GBGAME_DISPLAYMANAGER_H
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include "rtos.h"
#include "core/macros.h"
#include "ui/canvas.h"

using namespace rtos;
class DisplayManager {

public:
    static DisplayManager& getInstance();
    // Initialize the display
    void init();
    // Update the entire screen based on the provided GFXcanvas16
    void updateScreen(Canvas *canvas);

    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;

private:
    Adafruit_SSD1351 m_display = Adafruit_SSD1351(m_ScreenWidth, m_ScreenHeight, &::SPI, CS_PIN, DC_PIN, RST_PIN);
    Mutex m_displayMutex;

    DisplayManager();

    static constexpr uint16_t m_ScreenWidth = 128;
    static constexpr uint16_t m_ScreenHeight = 128;
    GFXcanvas16 m_canvas;
};
#endif //GBGAME_DISPLAYMANAGER_H
