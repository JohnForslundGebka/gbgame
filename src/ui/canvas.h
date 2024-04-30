/**
 * @class Canvas
 * @brief Manages a graphical canvas for drawing operations.
 *
 * This class encapsulates a GFXcanvas16 for rendering graphics and maintains
 * position data that can be used to manage and track rendering operations.
 */

#ifndef GBGAME_CANVAS_H
#define GBGAME_CANVAS_H
#include <Adafruit_GFX.h>

class Canvas {
public:
    //the GFXcanvas16 object that is used to draw things to the display
    GFXcanvas16 C;
    //getter and setter functions
    int16_t getX() const;
    void setX(int16_t x);
    int16_t getY() const;
    void setY(int16_t y);

    int16_t getOldX() const;
    void setOldX(int16_t oldX);
    int16_t getOldY() const;
    void setOldY(int16_t oldY);
   //update the x and y position
    void updatePos();

    /**
     * @brief Constructor initializes the canvas and position.
     * @param width Width of the canvas.
     * @param height Height of the canvas.
     * @param x Initial x-coordinate position.
     * @param y Initial y-coordinate position.
   */
    Canvas(uint16_t width, uint16_t height, int16_t x, int16_t y);
private:
    //member variables that holds the current position and the previous position
    int16_t m_x = 0;
    int16_t m_y = 0;
    int16_t m_oldX = 0;
    int16_t m_oldY = 0;
};
#endif //GBGAME_CANVAS_H
