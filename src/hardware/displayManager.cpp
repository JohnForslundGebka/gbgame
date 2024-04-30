#include "displayManager.h"

// Private constructor definition
DisplayManager::DisplayManager() : m_canvas(128,128) {
}

DisplayManager& DisplayManager::getInstance() {
    static DisplayManager instance;
    return instance;
}

void DisplayManager::init() {
    ::SPI.begin();
    m_display.begin(17000000); // Initialize display with a specific clock rate
    m_display.fillScreen(BLACK);
}

void DisplayManager::updateScreen(Canvas *canvas) {
    m_displayMutex.lock();
    m_canvas.fillRect(canvas->getOldX(),canvas->getOldY(),canvas->C.width(),canvas->C.height(),BLACK);
    m_canvas.drawRGBBitmap(canvas->getX(), canvas->getY(), canvas->C.getBuffer(), canvas->C.width(), canvas->C.height());

    m_display.drawRGBBitmap(0, 0, m_canvas.getBuffer(), m_canvas.width(), m_canvas.height());
    m_displayMutex.unlock();
}
