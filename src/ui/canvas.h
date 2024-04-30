#ifndef GBGAME_CANVAS_H
#define GBGAME_CANVAS_H
#include <Adafruit_GFX.h>

class Canvas {
public:
    GFXcanvas16 C;
    int16_t getX() const;

    void setX(int16_t x);

    int16_t getY() const;

    void setY(int16_t y);

    int16_t getOldX() const;

    void setOldX(int16_t oldX);

    int16_t getOldY() const;

    void setOldY(int16_t oldY);

    void updatePos();

    //constructor
    Canvas(uint16_t width, uint16_t height, int16_t x, int16_t y);
private:
    int16_t x = 0;
    int16_t y = 0;
    int16_t oldX = 0;
    int16_t oldY = 0;
};
#endif //GBGAME_CANVAS_H
