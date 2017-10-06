#include "text_button.hpp"

TextButton::TextButton(const ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent) :
    Button(window_size, x_percent, y_percent, bt.x_scale, bt.y_scale, bt.select_scale_change) {
    this->bt_data = bt;
    this->current_color = bt_data.normal_color;
    this->animation_time = bt_data.animation_time_millis * 1000; // convert to micros
    if(this->animation_time <= 0) {
        this->animation_time = 1.0; // no divide by 0 or negative animation times allowed
    }
    this->r = this->current_color.r;
    this->g = this->current_color.g;
    this->b = this->current_color.b;
    this->a = this->current_color.a;
    this->r_diff = (float)bt_data.select_color.r - (float)bt_data.normal_color.r;
    this->g_diff = (float)bt_data.select_color.g - (float)bt_data.normal_color.g;
    this->b_diff = (float)bt_data.select_color.b - (float)bt_data.normal_color.b;
    this->a_diff = (float)bt_data.select_color.a - (float)bt_data.normal_color.a;
    this->r_min = min(bt_data.normal_color.r, bt_data.select_color.r);
    this->r_max = max(bt_data.normal_color.r, bt_data.select_color.r);
    this->g_min = min(bt_data.normal_color.g, bt_data.select_color.g);
    this->g_max = max(bt_data.normal_color.g, bt_data.select_color.g);
    this->b_min = min(bt_data.normal_color.b, bt_data.select_color.b);
    this->b_max = max(bt_data.normal_color.b, bt_data.select_color.b);
    this->a_min = min(bt_data.normal_color.a, bt_data.select_color.a);
    this->a_max = max(bt_data.normal_color.a, bt_data.select_color.a);

    this->start = current_time();
    this->now = current_time();
}

void TextButton::UpdateTextPosition() {
    // Set scale first so getGlobalBounds gets the right sized rectangle
    text.setScale(current_scale_x, current_scale_y);
    // Need global bounds for x_coord positioning (global will adjust text rect width with scale changes)
    FloatRect global_rect = text.getGlobalBounds();
    // Need local bounds for stupid text offset calculation. Text not set to 0,0 locally, need to scale local offset with scale changes too
    FloatRect local_rect = text.getLocalBounds();
    stupid_text_offset_x = local_rect.left * current_scale_x;
    stupid_text_offset_y = local_rect.top * current_scale_y;
    x_coord = (window_size.x * x_percent) - (global_rect.width / 2.0f);
    y_coord = (window_size.y * y_percent) - (global_rect.height / 2.0f);
    // Stupid text rect origins aren't (0,0), so need to subtract the non-zero origins
    text.setPosition(x_coord - stupid_text_offset_x, y_coord - stupid_text_offset_y);
    left_upper = Vector2f(x_coord, y_coord);
    right_lower = Vector2f(x_coord + global_rect.width, y_coord + global_rect.height);
    //cout << "setting text position to: " << x_coord - stupid_text_offset_x << " " << y_coord - stupid_text_offset_y << endl;
    //cout << "lu: " << left_upper.x << " " << left_upper.y << " rl: " << right_lower.x << " " << right_lower.y << endl;
}

void TextButton::UpdateWindowSize(Vector2u window_size) {
    // NOTE: Seriously consider merging duplicated code in UpdateWindowSize, UpdateText, and AnimateSize into one function that all 3 can call
    this->window_size = window_size;
    UpdateTextPosition();
}

void TextButton::UpdateTextHorizontalPosition() {
    // Set scale first so getGlobalBounds gets the right sized rectangle
    text.setScale(current_scale_x, current_scale_y);
    // Need global bounds for x_coord positioning (global will adjust text rect width with scale changes)
    FloatRect global_rect = text.getGlobalBounds();
    // Need local bounds for stupid text offset calculation. Text not set to 0,0 locally, need to scale local offset with scale changes too
    FloatRect local_rect = text.getLocalBounds();
    // Only want to change x offset and x position here.
    // This function only called when we don't want the Y position to move, so don't change the y offset or the y position
    stupid_text_offset_x = local_rect.left * current_scale_x;
    x_coord = (window_size.x * x_percent) - (global_rect.width / 2.0f);
    // Stupid text rect origins aren't (0,0), so need to subtract the non-zero origins
    text.setPosition(x_coord - stupid_text_offset_x, y_coord - stupid_text_offset_y);
    left_upper = Vector2f(x_coord, y_coord);
    right_lower = Vector2f(x_coord + global_rect.width, y_coord + global_rect.height);
}

void TextButton::Animate(float x, float y) {
    now = current_time();
    double time_diff = micros_time_diff(start, now);
    bool selected;
    selected = (Intersect(x,y)) ? true : false;
    AnimateColor(selected, time_diff);
    AnimateSize(selected, time_diff);
    start = now;
}

void TextButton::AnimateColor(bool selected, double time_diff) {
    r = CalculateColorChange(r, r_diff, r_min, r_max, time_diff, selected);
    g = CalculateColorChange(g, g_diff, g_min, g_max, time_diff, selected);
    b = CalculateColorChange(b, b_diff, b_min, b_max, time_diff, selected);
    a = CalculateColorChange(a, a_diff, a_min, a_max, time_diff, selected);
    current_color.r = r;
    current_color.g = g;
    current_color.b = b;
    current_color.a = a;
    text.setFillColor(current_color);
}

float TextButton::CalculateColorChange(float val, float val_diff, float val_min, float val_max, double time_diff, bool selected) {
    double animation_percent = AnimationPercent(time_diff);
    if(animation_percent > 1.0) {
        animation_percent = 1.0;
    }
    if(selected) {
        val += val_diff * animation_percent;
    } else {
        val -= val_diff * animation_percent;
    }
    if(val < val_min) {
        val = val_min;
    } else if(val > val_max) {
        val = val_max;
    }
    return val;
}

void TextButton::AnimateSize(bool selected, double time_diff) {
    double animation_percent = AnimationPercent(time_diff);
    // Increase or decrease scale if selected or not, respectively
    if(selected) {
        current_scale_x += scale_diff_x * animation_percent;
        current_scale_y += scale_diff_y * animation_percent;
    } else {
        current_scale_x -= scale_diff_x * animation_percent;
        current_scale_y -= scale_diff_y * animation_percent;
    }
    // Bounds check x current scale
    if(current_scale_x < scale_min_x) {
        current_scale_x = scale_min_x;
    } else if(current_scale_x > scale_max_x) {
        current_scale_x = scale_max_x;
    }
    // Bounds check y current scale
    if(current_scale_y < scale_min_y) {
        current_scale_y = scale_min_y;
    } else if(current_scale_y > scale_max_y) {
        current_scale_y = scale_max_y;
    }
    UpdateTextPosition();
}

double TextButton::AnimationPercent(double time_diff) {
    return (time_diff / animation_time > 1.0) ? 1.0 : time_diff / animation_time;
}

FloatRect TextButton::GetGlobalBounds() {
    return text.getGlobalBounds();
}

string TextButton::GetString() {
    return bt_data.display_string;
}

String TextButton::GetDisplayString() {
    string s = bt_data.display_string;
    if(bt_data.windows_pathfile) {
        return String::fromUtf16(s.begin(), s.end());
    } else {
        return String::fromUtf8(s.begin(), s.end());
    }
}
