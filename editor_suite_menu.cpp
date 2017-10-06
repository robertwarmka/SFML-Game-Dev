#include "editor_suite_menu.hpp"

EditorSuiteMenu::EditorSuiteMenu(RenderWindow& window, ResourceManager& resources, ConfigHandler& config) :
    GameState(window, resources, config) {
    ButtonTextData bt_data;
    bt_data.font = resources.GetFont();
    bt_data.char_size = 50.0f;
    bt_data.select_scale_change = 1.2f;
    bt_data.normal_color = sf::Color::White;
    bt_data.select_color = sf::Color::Yellow;
    bt_data.animation_time_millis = 100; // in ms
    pair<string, vector<string>> button_text;

    button_text = resources.FindButtonText("Map Editor");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.25, State::MAP_EDIT_MENU));

    button_text = resources.FindButtonText("Object Editor");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.5, State::OBJECT_EDITOR));

    button_text = resources.FindButtonText("Back");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.75, State::MAIN_MENU));
}

State EditorSuiteMenu::Display() {
    ResizeWindow(window.getSize(), button_list, overlay);

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
