#include "apply_changes_button.hpp"

ApplyChangesButton::ApplyChangesButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent, State state,
    ConfigHandler& config, RenderWindow& window, vector<StateButton*>& save_button_list, vector<Button*>& button_list) :
    TransitionButton(bt, window_size, x_percent, y_percent, state),
    config(config),
    window(window),
    save_button_list(save_button_list),
    button_list(button_list) {}

State ApplyChangesButton::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Button::Left) {
            if(Intersect(event.mouseButton.x, event.mouseButton.y)) {
                vector<pair<string, string>> update_config;
                for(auto it = save_button_list.begin(); it != save_button_list.end(); ++it) {
                    update_config.push_back(make_pair((*it)->GetString(), (*it)->GetState()));
                }
                config.UpdateConfig(update_config);
                for(auto it = button_list.begin(); it != button_list.end(); ++it) {
                    (*it)->UpdateWindowSize(window.getSize());
                }
                return state;
            }
        }
    }
    return State::NO_CHANGE;
}
