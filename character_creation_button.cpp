#include "character_creation_button.hpp"

CharacterCreationButton::CharacterCreationButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent, State state,
    CharacterHandler& char_handler, RenderWindow& window, TextBoxButton& character_name_button, vector<DataButton*>& save_button_list) :
    TransitionButton(bt, window_size, x_percent, y_percent, state),
    char_handler(char_handler),
    window(window),
    character_name_button(character_name_button),
    save_button_list(save_button_list) {}

State CharacterCreationButton::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Button::Left) {
            if(Intersect(event.mouseButton.x, event.mouseButton.y)) {
                for(auto it = save_button_list.begin(); it != save_button_list.end(); ++it) {
                    cout << (*it)->ConcatStrings() << endl;
                    //update_config.push_back(make_pair((*it)->GetDisplayString(), (*it)->GetState()));
                }
                string character_name = character_name_button.GetData();
                cout << character_name << endl;
                if(!character_name.empty()) {
                    char_handler.CreateNewCharacter(character_name, save_button_list);
                    return state;
                }
            }
        }
    }
    return State::NO_CHANGE;
}
