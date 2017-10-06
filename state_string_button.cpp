#include "state_string_button.hpp"

StateStringButton::StateStringButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent, State transition, bool display_state) :
    StateButton(bt, window_size, x_percent, y_percent, transition, display_state) {}

string StateStringButton::GetState() {
    return bt_data.strings[bt_data.current_state];
}
