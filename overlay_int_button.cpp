#include "overlay_int_button.hpp"

OverlayIntButton::OverlayIntButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent,
                                   State transition, bool display_state, OverlayData od, GameState* game_state) :
    StateIntButton(bt, window_size, x_percent, y_percent, transition, display_state),
    overlay(window_size, game_state, bt, od, this) {
    for(unsigned int i = 0; i < bt_data.strings.size(); ++i) {
        this->bt_data.display_string = this->bt_data.strings[i];
        overlay.AddButton(new ChoiceButton(this->bt_data, window_size, 0.0, 0.0, i));
    }
    menu = game_state;
}

State OverlayIntButton::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(Intersect(event.mouseButton.x, event.mouseButton.y)) {
            if(event.mouseButton.button == sf::Mouse::Button::Left) {
                menu->overlay = &overlay;
            }
        }
    }
    return State::NO_CHANGE;
}

void OverlayIntButton::UpdateWindowSize(Vector2u window_size) {
    overlay.UpdateWindowSize(window_size);
    TextButton::UpdateWindowSize(window_size);
}
