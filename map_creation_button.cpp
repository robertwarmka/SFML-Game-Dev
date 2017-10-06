#include "map_creation_button.hpp"

MapCreationButton::MapCreationButton(ButtonTextData& bt, Vector2u window_size, float x_percent, float y_percent, State state,
    MapHandler& map_handler, RenderWindow& window, TextBoxButton& map_name_button) :
    TransitionButton(bt, window_size, x_percent, y_percent, state),
    map_handler(map_handler),
    window(window),
    map_name_button(map_name_button) {}

State MapCreationButton::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Button::Left) {
            if(Intersect(event.mouseButton.x, event.mouseButton.y)) {
                string map_name = map_name_button.GetData();
                cout << map_name << endl;
                if(!map_name.empty()) {
                    map_handler.CreateNewMap(map_name);
                    return state;
                }
            }
        }
    }
    return State::NO_CHANGE;
}
