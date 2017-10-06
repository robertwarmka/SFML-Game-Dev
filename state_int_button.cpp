#include "state_int_button.hpp"

StateIntButton::StateIntButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent, State transition, bool display_state) :
    StateButton(bt, window_size, x_percent, y_percent, transition, display_state) {}

string StateIntButton::GetState() {
    return std::to_string(bt_data.current_state);
}
