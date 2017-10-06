#include "config_menu.hpp"

ConfigMenu::ConfigMenu(RenderWindow& window, ResourceManager& resources, ConfigHandler& config) : GameState(window, resources, config) {
    ButtonTextData bt_data;
    bt_data.font = resources.GetFont();
    bt_data.char_size = 60.0f;
    bt_data.select_scale_change = 1.2f;
    bt_data.normal_color = sf::Color::White;
    bt_data.select_color = sf::Color::Red;
    bt_data.animation_time_millis = 100; // in ms
    pair<string, vector<string>> button_text;
    OverlayData overlay_data(FloatRect(0.25, 0.1, 0.5, 0.5), Color(20, 20, 20, 255), State::NO_CHANGE, false);

    button_text = resources.FindButtonText("Resolution");
    bt_data.display_string = button_text.first;
    bt_data.strings = button_text.second;
    bt_data.SetCurrentState(config.GetResolutionText());
    bt_data.normal_color = sf::Color::Red;
    bt_data.select_color = sf::Color::Blue;
    bt_data.char_size = 35.0f;
    bt_data.select_scale_change = 1.1f;
    save_button_list.push_back(new OverlayStringButton(bt_data, window.getSize(), 0.5, 0.15, State::NO_CHANGE, true, overlay_data, this));

    button_text = resources.FindButtonText("Borderless Window");
    bt_data.display_string = button_text.first;
    bt_data.strings = button_text.second;
    bt_data.SetCurrentState(config.GetBorderlessWindow());
    save_button_list.push_back(new StateIntButton(bt_data, window.getSize(), 0.5, 0.35, State::NO_CHANGE, true));

    button_text = resources.FindButtonText("Fullscreen");
    bt_data.display_string = button_text.first;
    bt_data.strings = button_text.second;
    bt_data.SetCurrentState(config.GetFullScreen());
    save_button_list.push_back(new StateIntButton(bt_data, window.getSize(), 0.5, 0.45, State::NO_CHANGE, true));

    button_text = resources.FindButtonText("Back");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.75, State::MAIN_MENU));

    button_text = resources.FindButtonText("Apply");
    bt_data.display_string = button_text.first;
    button_list.push_back(new ApplyChangesButton(bt_data, window.getSize(), 0.5, 0.65, State::MAIN_MENU, config, window, save_button_list, button_list));

    for(auto it = save_button_list.begin(); it != save_button_list.end(); ++it) {
        button_list.push_back(*it);
    }
}

State ConfigMenu::Display() {
    ResizeWindow(window.getSize(), button_list, overlay);

    Event event;
    Mouse mouse;
    Vector2i mouse_pos;
    State state = State::NO_CHANGE;
    while(true) {
        mouse_pos = mouse.getPosition(window);
        if(overlay != nullptr) {
            overlay->Animate(mouse_pos.x, mouse_pos.y);
            // Set x and y to a large negative number so nothing on screen animates if overlay
            // is selected, but still animate so things will un-animate when overlay selected
            mouse_pos.x = -1000;
            mouse_pos.y = -1000;
        }
        for(auto it = button_list.begin(); it != button_list.end(); ++it) {
            (*it)->Animate(mouse_pos.x, mouse_pos.y);
        }
        while (window.pollEvent(event)) {
            if(overlay != nullptr) {
                overlay->Action(event);
            } else {
                for(auto it = button_list.begin(); it != button_list.end(); ++it) {
                    state = (*it)->Action(event);
                    if(state != State::NO_CHANGE) {
                        return state;
                    }
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
