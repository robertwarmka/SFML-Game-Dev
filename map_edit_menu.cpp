#include "map_edit_menu.hpp"

MapEditMenu::MapEditMenu(RenderWindow& window, ResourceManager& resources, ConfigHandler& config, MapHandler& map_handler) :
    GameState(window, resources, config),
    map_handler(map_handler) {
    ButtonTextData bt_data;
    bt_data.font = resources.GetFont();
    bt_data.char_size = 50.0f;
    bt_data.select_scale_change = 1.2f;
    bt_data.normal_color = sf::Color::White;
    bt_data.select_color = sf::Color::Yellow;
    bt_data.animation_time_millis = 100; // in ms
    pair<string, vector<string>> button_text;
    vector<string> map_names = map_handler.GetMapNames();
    OverlayData overlay_data(FloatRect(0.25, 0.1, 0.5, 0.5), Color(20, 20, 20, 255), State::MAP_EDIT, true);

    button_text = resources.FindButtonText("Back");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.75, State::EDITOR_SUITE_MENU));

    button_text = resources.FindButtonText("New Map");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.65, State::CREATE_MAP));

    bt_data.normal_color = sf::Color::Red;
    bt_data.select_color = sf::Color::Blue;
    bt_data.char_size = 35.0f;
    bt_data.select_scale_change = 1.1f;
    TransitionOverlay* transition_overlay = new TransitionOverlay(window.getSize(), this, bt_data, overlay_data);
    if(is_windows()) {
        bt_data.windows_pathfile = true;
    }
    for(unsigned int i = 0; i < map_names.size(); ++i) {
        bt_data.display_string = map_names[i];
        transition_overlay->AddButton(new ChoiceButton(bt_data, window.getSize(), 0.0, 0.0, i));
    }
    overlay = transition_overlay;
}

State MapEditMenu::Display() {
    ResizeWindow(window.getSize(), button_list, overlay);

    overlay->ClearData();
    ButtonTextData bt_data;
    vector<string> map_names = map_handler.GetMapNames();
    bt_data.font = resources.GetFont();
    bt_data.animation_time_millis = 100; // in ms
    bt_data.normal_color = sf::Color::Red;
    bt_data.select_color = sf::Color::Blue;
    bt_data.char_size = 35.0f;
    bt_data.select_scale_change = 1.1f;
    if(is_windows()) {
        bt_data.windows_pathfile = true;
    }
    for(unsigned int i = 0; i < map_names.size(); ++i) {
        bt_data.display_string = map_names[i];
        overlay->AddButton(new ChoiceButton(bt_data, window.getSize(), 0.0, 0.0, i));
    }

    Event event;
    Mouse mouse;
    Vector2i mouse_pos;
    State state = State::NO_CHANGE;
    while(true) {
        mouse_pos = mouse.getPosition(window);
        if(overlay != nullptr) {
            overlay->Animate(mouse_pos.x, mouse_pos.y);
        }
        for(auto it = button_list.begin(); it != button_list.end(); ++it) {
            (*it)->Animate(mouse_pos.x, mouse_pos.y);
        }
        while (window.pollEvent(event)) {
            if(overlay != nullptr) {
                state = overlay->Action(event);
                if(state != State::NO_CHANGE) {
                    return state;
                }
            }
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
        if(overlay != nullptr) {
            overlay->Draw(window);
        }
        // end the current frame
        window.display();
    }
}
