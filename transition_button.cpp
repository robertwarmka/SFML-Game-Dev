#include "transition_button.hpp"

TransitionButton::TransitionButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent, State state) :
    TextButton(bt, window_size, x_percent, y_percent) {
    text = Text(GetDisplayString(), bt_data.font, bt_data.char_size);
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
    this->state = state;
}

State TransitionButton::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Button::Left) {
            if(Intersect(event.mouseButton.x, event.mouseButton.y)) {
                return state;
            }
        }
    }
    return State::NO_CHANGE;
}

void TransitionButton::Draw(RenderWindow& window) {
    window.draw(text);
}
