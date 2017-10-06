#ifndef TEXT_BUTTON_H_
#define TEXT_BUTTON_H_

#include "general.hpp"
#include "button.hpp"
#include "drawable.hpp"

class TextButton : public Button {
protected:
    ButtonTextData bt_data;
    Text text;
    float x_coord, y_coord;
    float stupid_text_offset_x, stupid_text_offset_y;
    Color current_color;
    float r, g, b, a, r_diff, g_diff, b_diff, a_diff;
    float r_min, r_max, g_min, g_max, b_min, b_max, a_min, a_max;
    double animation_time, progress = 0.0; // Animation time is in microseconds
    time_point<steady_clock> start, now;
public:
    explicit TextButton(const ButtonTextData&, Vector2u, float, float);
    void UpdateTextPosition();
    void UpdateWindowSize(Vector2u);
    void UpdateTextHorizontalPosition();
    void Animate(float, float);
    void AnimateColor(bool, double);
    float CalculateColorChange(float, float, float, float, double, bool);
    void AnimateSize(bool, double);
    double AnimationPercent(double);
    FloatRect GetGlobalBounds();
    string GetString();
    String GetDisplayString();
private:
};

#endif
