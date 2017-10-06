#include "state_button.hpp"

StateButton::StateButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent, State transition, bool display_state) :
    DataButton(bt, window_size, x_percent, y_percent),
    state(transition),
    display_state(display_state) {
    if(display_state == true) {
        text = Text(ConcatDisplayStrings(), bt_data.font, (unsigned int)bt_data.char_size);
    } else {
        text = Text(GetDisplayString(), bt_data.font, (unsigned int)bt_data.char_size);
    }
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
}

State StateButton::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(Intersect(event.mouseButton.x, event.mouseButton.y)) {
            if(bt_data.strings.size() > 0) {
                if(event.mouseButton.button == sf::Mouse::Button::Left) {
                    bt_data.current_state = ((bt_data.current_state + 1) % bt_data.strings.size());
                } else if(event.mouseButton.button == sf::Mouse::Button::Right) {
                    // If state < 0, state = string size (-1 for array access), else state -= 1
                    bt_data.current_state = (bt_data.current_state - 1 < 0) ? bt_data.strings.size() - 1 : bt_data.current_state - 1;
                }
                if(display_state == true) {
                    text.setString(ConcatDisplayStrings());
                } else {
                    text.setString(GetDisplayString());
                }
            }
        }
    }
    return state;
}

void StateButton::Draw(RenderWindow& window) {
    window.draw(text);
}

void StateButton::UpdateState(int new_state) {
    bt_data.current_state = new_state;
    if(display_state == true) {
        text.setString(ConcatDisplayStrings());
    } else {
        text.setString(GetDisplayString());
    }
}

string StateButton::ConcatStrings() {
    if((unsigned int)bt_data.current_state < bt_data.strings.size()) {
        return bt_data.display_string + ": " + bt_data.strings[bt_data.current_state];
    } else {
        return bt_data.display_string + ": ";
    }
}

String StateButton::ConcatDisplayStrings() {
    string s;
    if((unsigned int)bt_data.current_state < bt_data.strings.size()) {
        s = bt_data.display_string + ": " + bt_data.strings[bt_data.current_state];
    } else {
        s = bt_data.display_string + ": ";
    }
    return String::fromUtf8(s.begin(), s.end());
}
