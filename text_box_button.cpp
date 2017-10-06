#include "text_box_button.hpp"

TextBoxButton::TextBoxButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent, const Color& focused_color) :
    DataButton(bt, window_size, x_percent, y_percent),
    focused(false),
    blink(false),
    focused_color(focused_color) {
    text = Text("|", bt_data.font, bt_data.char_size);
    display_text = text;
    FloatRect rect = text.getGlobalBounds();
    x_coord = (window_size.x * x_percent) - (rect.width / 2.0f);
    y_coord = (window_size.y * y_percent) - (rect.height / 2.0f);
    // Stupid text rect origins aren't (0,0), so need to subtract the non-zero origins
    stupid_text_offset_x = rect.left;
    stupid_text_offset_y = rect.top;
    left_upper = Vector2f(x_coord, y_coord);
    right_lower = Vector2f(x_coord + rect.width, y_coord + rect.height);
    text.setPosition(x_coord - stupid_text_offset_x, y_coord - stupid_text_offset_y);
    text.setFillColor(bt_data.normal_color);
    this->blink_start = current_time();
}

State TextBoxButton::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Button::Left) {
            if(Intersect(event.mouseButton.x, event.mouseButton.y) && !focused) {
                focused = true;
            } else {
                focused = false;
            }
        }
    }
    if(focused && event.type == Event::TextEntered) {
        if(event.text.unicode == 8) { // backspace
            if(!text_data.isEmpty()) {
                text_data.erase(text_data.getSize()-1, 1);
            }
        } else if(event.text.unicode == 13) {
            focused = false;
        } else {
            text_data.insert(text_data.getSize(), event.text.unicode);
        }
    }
    return State::NO_CHANGE;
}

void TextBoxButton::Draw(RenderWindow& window) {
    display_text = text;
    if(focused) {
        if(Blink()) {
            display_text.setString(text_data + "|");
        } else {
            display_text.setString(text_data);
        }
    }
    RectangleShape box;
    box.setPosition(left_upper);
    box.setSize(right_lower - left_upper);
    box.setFillColor(Color(100, 100, 100));
    //cout << "left upper: " << left_upper.x << " " << left_upper.y << " right lower: " << right_lower.x << " " << right_lower.y << endl;
    //FloatRect global = display_text.getGlobalBounds();
    //FloatRect local = display_text.getLocalBounds();
    //cout << "display text global bounds: " << global.left << " " << global.top << " " << global.left + global.width << " " << global.top + global.height << endl;
    //cout << "display text local bounds: " << local.left << " " << local.top << " " << local.left + local.width << " " << local.top + local.height << endl;
    window.draw(box);
    window.draw(display_text);
}

void TextBoxButton::Animate(float x, float y) {
    now = current_time();
    double time_diff = micros_time_diff(start, now);
    bool selected;
    selected = (Intersect(x,y)) ? true : false;
    AnimateColor(selected, time_diff);
    if(focused) {
        text.setFillColor(focused_color);
    }
    if(focused || !text_data.isEmpty()) {
        text.setString(text_data);
    } else {
        text.setString(GetDisplayString());
    }
    UpdateTextHorizontalPosition();
    start = now;
}

bool TextBoxButton::Blink() {
    double blink_diff = micros_time_diff(blink_start, now) / 1000.0; // in millis
    if(blink_diff >= blink_animation) {
        blink = !blink;
        blink_start = now;
    }
    return blink;
}

string TextBoxButton::GetData() {
    return text_data;
}

string TextBoxButton::ConcatStrings() {
    if(text_data.isEmpty()) {
        return "";
    }
    return bt_data.display_string + ": " + text_data;
}

void TextBoxButton::EraseTextData() {
    text_data.clear();
}
