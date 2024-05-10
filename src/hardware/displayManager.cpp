#include "displayManager.h"

/**
 * @brief Private constructor to initialize the canvas.
 */
DisplayManager::DisplayManager() : m_canvas(128,128) {
}

/**
 * @brief Retrieves the singleton instance of the DisplayManager.
 *
 * This function provides access to the singleton instance of the DisplayManager,
 * creating it if it does not already exist.
 *
 * @return Reference to the singleton instance of DisplayManager.
 */

DisplayManager& DisplayManager::getInstance() {
    static DisplayManager instance;
    return instance;
}
/**
 * @brief Initializes the display hardware.
 *
 * Sets up the SPI communication and initializes the display with a set clock rate,
 * and clears the display to a black screen. You can adjust the SPI clock rate if necessary
 */

void DisplayManager::init() {
    ::SPI.begin();
    m_display.begin(17000000); // Initialize display with a specific clock rate
    m_display.fillScreen(BLACK);
}

/**
 * @brief Updates the display with the content from a canvas.
 *
 * Locks the display mutex to prevent concurrent access, then updates the display
 * with the content from the specified canvas. This method handles clearing the
 * old content and drawing new content.
 *
 * @param canvas Pointer to the canvas containing new screen content.
 */
void DisplayManager::updateScreen(Canvas *canvas) {
    m_displayMutex.lock();
    m_canvas.fillRect(canvas->getOldX(),canvas->getOldY(),canvas->C.width(),canvas->C.height(),BLACK);
    m_canvas.drawRGBBitmap(canvas->getX(), canvas->getY(), canvas->C.getBuffer(), canvas->C.width(), canvas->C.height());

    m_display.drawRGBBitmap(0, 0, m_canvas.getBuffer(), m_canvas.width(), m_canvas.height());
    m_displayMutex.unlock();
}
