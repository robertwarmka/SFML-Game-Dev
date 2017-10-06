#include "choice_button.hpp"

ChoiceButton::ChoiceButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent, int state) :
    TextButton(bt, window_size, x_percent, y_percent) {
    this->state = state;
    text = Text(GetDisplayString(), bt_data.font, (unsigned int)bt_data.char_size);
    UpdateTextPosition();
    text.setFillColor(bt_data.normal_color);
}

ChoiceButton::ChoiceButton(const ChoiceButton& c_button) :
    TextButton(c_button.bt_data, c_button.window_size, c_button.x_percent, c_button.y_percent) {
    text = Text(bt_data.display_string, bt_data.font, (unsigned int)bt_data.char_size);
    UpdateTextPosition();
    text.setFillColor(bt_data.normal_color);
    this->state = c_button.state;
}

State ChoiceButton::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(Intersect(event.mouseButton.x, event.mouseButton.y)) {
            if(event.mouseButton.button == sf::Mouse::Button::Left) {
                return State::CLICKED;
            }
        }
    }
    return State::NO_CHANGE;
}

void ChoiceButton::Draw(RenderWindow& window) {
    // Might leave this code commented here. It's good for debugging intersection boxes
    /*RectangleShape rect;
    rect.setPosition(left_upper.x, left_upper.y);
    rect.setSize(Vector2f(right_lower.x - left_upper.x, right_lower.y - left_upper.y));
    window.draw(rect);*/
    window.draw(text);
}

int ChoiceButton::GetState() {
    return this->state;
}
