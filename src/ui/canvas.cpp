#include "canvas.h"

int16_t Canvas::getX() const {
    return m_x;
}

Canvas::Canvas(uint16_t width, uint16_t height, int16_t x, int16_t y) : C(width,height), m_x(x), m_y(y) {
    m_oldX = x;
    m_oldY = y;
}

void Canvas::setX(int16_t x) {
    Canvas::m_x = x;
}

int16_t Canvas::getY() const {
    return m_y;
}

void Canvas::setY(int16_t y) {
    Canvas::m_y = y;
}

int16_t Canvas::getOldX() const {
    return m_oldX;
}

void Canvas::setOldX(int16_t oldX) {
    Canvas::m_oldX = oldX;
}

int16_t Canvas::getOldY() const {
    return m_oldY;
}

void Canvas::setOldY(int16_t oldY) {
    Canvas::m_oldY = oldY;
}

void Canvas::updatePos() {
    m_oldX = m_x;
    m_oldY = m_y;
}
