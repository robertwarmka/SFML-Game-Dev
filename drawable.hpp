#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "general.hpp"

class Drawable : public Logger {
protected:
    Vector2f left_upper, right_lower;
    Vector2u window_size;
public:
    explicit Drawable(Vector2u window_size) {
        this->window_size = window_size;
    }
    bool Intersect(float x, float y) {
        if(x >= left_upper.x && x <= right_lower.x && y >= left_upper.y && y <= right_lower.y) {
            return true;
        } else {
            return false;
        }
    }
    virtual void Draw(RenderWindow&) = 0;
    virtual void UpdateWindowSize(Vector2u) = 0;
};

#endif // DRAWABLE_H_
