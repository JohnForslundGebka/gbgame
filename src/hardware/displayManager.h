/**
 * @class DisplayManager
 * @brief Manages display operations across the entire application.
 *
 * This singleton class handles all display operations, ensuring that display access
 * is synchronized across different threads.
 *
 */

#ifndef GBGAME_DISPLAYMANAGER_H
#define GBGAME_DISPLAYMANAGER_H
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include "rtos.h"
#include "core/macros.h"
#include "ui/canvas.h"


class DisplayManager {

public:
    /**
     * @brief Retrieves the singleton instance of DisplayManager.
     * @return Reference to the singleton DisplayManager instance.
     */
    static DisplayManager& getInstance();
    // Initialize the display
    void init();

     /**
     * @brief Updates the display with contents from a specified canvas.
     * @param canvas Pointer to the canvas whose contents will be displayed.
     */
    void updateScreen(Canvas *canvas);

    // Prevent copying and assignment.
    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;

private:

    Adafruit_SSD1351 m_display = Adafruit_SSD1351(m_ScreenWidth, m_ScreenHeight, &::SPI, CS_PIN, DC_PIN, RST_PIN);
    rtos::Mutex m_displayMutex;
    //constructor
    DisplayManager();

    static constexpr uint16_t m_ScreenWidth = 128;
    static constexpr uint16_t m_ScreenHeight = 128;
    GFXcanvas16 m_canvas;
};
#endif //GBGAME_DISPLAYMANAGER_H
