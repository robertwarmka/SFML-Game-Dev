#ifndef BUTTON_H_
#define BUTTON_H_

#include "general.hpp"
#include "drawable.hpp"

class Button : public Drawable {
protected:
    int intial_state;
    float x_percent, y_percent;
    float current_scale_x;
    float scale_diff_x, scale_min_x, scale_max_x;
    float current_scale_y;
    float scale_diff_y, scale_min_y, scale_max_y;
    float scale_change;
public:
    explicit Button(Vector2u window_size, float x_percent, float y_percent, float x_scale, float y_scale, float scale_change) :
        Drawable(window_size) {
        this->x_percent = x_percent;
        this->y_percent = y_percent;
        this->scale_change = scale_change;
        // Will set current_scales
        SetScale(x_scale, y_scale);
    }
    virtual ~Button() {}
    virtual void Animate(float, float) = 0;
    virtual State Action(Event) = 0;
    virtual FloatRect GetGlobalBounds() = 0;
    void UpdateXPercent(float x_percent) {
        this->x_percent = x_percent;
    }
    void UpdateYPercent(float y_percent) {
        this->y_percent = y_percent;
    }
    void SetScale(float x, float y) {
        this->current_scale_x = x; // default x scale value
        this->current_scale_y = y; // default y scale value
        this->scale_diff_x = (scale_change - 1.0f) * x; // 1.0f is always default scale value, multiply by x_scale for proper scaling
        this->scale_diff_y = (scale_change - 1.0f) * y; // 1.0f is always default scale value, multiply by y_scale for proper scaling
        this->scale_min_x = min(scale_change * x, x);
        this->scale_max_x = max(scale_change * x, x);
        this->scale_min_y = min(scale_change * y, y);
        this->scale_max_y = max(scale_change * y, y);
    }
};

#endif
