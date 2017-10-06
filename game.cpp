#include "game.hpp"

Game::Game(RenderWindow& window, ResourceManager& resources, ConfigHandler& config) :
    GameState(window, resources, config) {
    // Initialization code for Game here
    ButtonTextData bt_data;
    bt_data.font = resources.GetFont();
    bt_data.char_size = 50.0f;
    bt_data.select_scale_change = 1.2f;
    bt_data.normal_color = sf::Color::White;
    bt_data.select_color = sf::Color::Yellow;
    bt_data.animation_time_millis = 100; // in ms
    pair<string, vector<string>> button_text;
    OverlayData overlay_data(FloatRect(0.0, 0.0, 1.0, 1.0), Color(0, 0, 0, 200), State::GAME, true);

    bt_data.normal_color = sf::Color::Red;
    bt_data.select_color = sf::Color::Blue;
    bt_data.char_size = 35.0f;
    bt_data.select_scale_change = 1.1f;
    button_text = resources.FindButtonText("Back");
    bt_data.display_string = button_text.first;
    bt_data.char_size = 55.0f;
    overlay = new GeneralOverlay(window.getSize(), this, bt_data, overlay_data);
    overlay->AddButton(new TransitionButton(bt_data, window.getSize(), 0.5, 0.9, State::MAIN_MENU));
}

State Game::Display() {
    ResizeWindow(window.getSize(), button_list, overlay);

    display_overlay = false;
    Event event;
    Mouse mouse;
    Vector2i mouse_pos;
    State state = State::NO_CHANGE;
    while(true) {
        mouse_pos = mouse.getPosition(window);
        if(display_overlay) {
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
            if(event.type == Event::TextEntered && event.text.unicode == 27) {
                // Flip-flop display overlay
                display_overlay = !display_overlay;
            }
            if(display_overlay) {
                state = overlay->Action(event);
                if(state != State::NO_CHANGE) {
                    return state;
                }
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
        if(display_overlay) {
            overlay->Draw(window);
        }
        // end the current frame
        window.display();
    }
}
