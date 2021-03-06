#include "overlay_string_button.hpp"

OverlayStringButton::OverlayStringButton(ButtonTextData& bt_data, Vector2u window_size, float x_percent, float y_percent,
                                         State transition, bool display_state, OverlayData od, GameState* game_state) :
    StateStringButton(bt_data, window_size, x_percent, y_percent, transition, display_state),
    overlay(window_size, game_state, bt_data, od, this) {
    for(unsigned int i = 0; i < bt_data.strings.size(); ++i) {
        bt_data.display_string = bt_data.strings[i];
        overlay.AddButton(new ChoiceButton(bt_data, window_size, 0.0, 0.0, i));
    }
    menu = game_state;
}

State OverlayStringButton::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(Intersect(event.mouseButton.x, event.mouseButton.y)) {
            if(event.mouseButton.button == sf::Mouse::Button::Left) {
                menu->overlay = &overlay;
            }
        }
    }
    return State::NO_CHANGE;
}

void OverlayStringButton::UpdateWindowSize(Vector2u window_size) {
    overlay.UpdateWindowSize(window_size);
    TextButton::UpdateWindowSize(window_size);
}
