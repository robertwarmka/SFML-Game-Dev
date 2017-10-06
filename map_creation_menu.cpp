#include "map_creation_menu.hpp"

MapCreationMenu::MapCreationMenu(RenderWindow& window, ResourceManager& resources, ConfigHandler& config, MapHandler& map_handler) :
    GameState(window, resources, config),
    map_handler(map_handler) {
    ButtonTextData bt_data;
    bt_data.font = resources.GetFont();
    bt_data.char_size = 60.0f;
    bt_data.select_scale_change = 1.2f;
    bt_data.normal_color = sf::Color::White;
    bt_data.select_color = sf::Color::Yellow;
    bt_data.animation_time_millis = 100; // in ms
    pair<string, vector<string>> button_text;

    button_text = resources.FindButtonText("Map Name");
    bt_data.display_string = button_text.first;
    map_name_button = new TextBoxButton(bt_data, window.getSize(), 0.5, 0.25, sf::Color::Red);
    button_list.push_back(map_name_button);

    button_text = resources.FindButtonText("Back");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.75, State::MAP_EDIT_MENU));

    button_text = resources.FindButtonText("Create Map");
    bt_data.display_string = button_text.first;
    button_list.push_back(new MapCreationButton(bt_data, window.getSize(), 0.5, 0.65, State::MAIN_MENU,
        map_handler, window, *map_name_button));

    for(auto it = save_button_list.begin(); it != save_button_list.end(); ++it) {
        button_list.push_back(*it);
    }
}

State MapCreationMenu::Display() {
    ResizeWindow(window.getSize(), button_list, overlay);
    map_name_button->EraseTextData();

    Event event;
    Mouse mouse;
    Vector2i mouse_pos;
    State state = State::NO_CHANGE;
    while(true) {
        mouse_pos = mouse.getPosition(window);
        for(auto it = button_list.begin(); it != button_list.end(); ++it) {
            (*it)->Animate(mouse_pos.x, mouse_pos.y);
        }
        while (window.pollEvent(event)) {
            for(auto it = button_list.begin(); it != button_list.end(); ++it) {
                state = (*it)->Action(event);
                if(state != State::NO_CHANGE) {
                    return state;
                }
            }
            ResizeWindow(event, window, button_list, overlay);
        }
        // Render step
        window.clear(Color::Black);
        // draw everything here...
        for(auto it = button_list.begin(); it != button_list.end(); ++it) {
            (*it)->Draw(window);
        }
        // end the current frame
        window.display();
    }
}
