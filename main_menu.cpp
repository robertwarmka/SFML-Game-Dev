#include "main_menu.hpp"

MainMenu::MainMenu(RenderWindow& window, ResourceManager& resources, ConfigHandler& config, Renderer& renderer) : GameState(window, resources, config), renderer(renderer) {
    ButtonTextData bt_data;
    bt_data.font = resources.GetFont();
    bt_data.char_size = 60.0f;
    bt_data.select_scale_change = 1.2f;
    bt_data.normal_color = sf::Color::Magenta;
    bt_data.select_color = sf::Color::Cyan;
    bt_data.animation_time_millis = 100; // in ms
    pair<string, vector<string>> button_text;

    button_text = resources.FindButtonText("Play");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.15, State::GAME));

    button_text = resources.FindButtonText("Settings");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.60, State::SETTINGS));

    button_text = resources.FindButtonText("Exit");
    bt_data.display_string = button_text.first;
    bt_data.normal_color = sf::Color::Green;
    bt_data.select_color = sf::Color::Blue;
    bt_data.select_scale_change = 1.2f;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.75, State::EXIT));

    button_text = resources.FindButtonText("Character Creation");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.25, State::CREATE_CHARACTER));

    button_text = resources.FindButtonText("Editor Suite");
    bt_data.display_string = button_text.first;
    button_list.push_back(new TransitionButton(bt_data, window.getSize(), 0.5, 0.5, State::EDITOR_SUITE_MENU));
}

State MainMenu::Display() {
    ResizeWindow(window.getSize(), button_list, overlay);
    renderer.Clear();
    for(auto it = button_list.begin(); it != button_list.end(); ++it) {
        renderer.AddButton(*it);
    }

    time_point<steady_clock> now, past = current_time(), one_sec = current_time();
    double micros;
    string fps_string = "";
    stringstream fps_ss;
    double fps;
    Text text(fps_string, resources.GetFont(), 60);
    text.setPosition(10.0f, 10.0f);
    text.setFillColor(Color::Blue);

    Event event;
    Mouse mouse;
    Vector2i mouse_pos;
    State state = State::NO_CHANGE;
    while(true) {
        mouse_pos = mouse.getPosition(window);
        renderer.Animate(mouse_pos);
        now = current_time();
        micros = micros_time_diff(past, now);

        fps = 1000.0 / (micros / 1000.0); // Convert micros to millis, then divide 1 second by millis-
        // If greater than 0.1 second (100K micros), update FPS counter
        if(micros_time_diff(now, one_sec) > 100000.0f) {
            fps_ss.str("");
            fps_ss.clear();
            fps_ss << fps;
            fps_string = fps_ss.str();
            text.setString(fps_string);
            one_sec = now;
        }
        if(fps < 55) {
            cout << fps << endl;
        }
        past = now;

        while (window.pollEvent(event)) {
            state = renderer.Action(event);
            if(state != State::NO_CHANGE) {
                return state;
            }
            ResizeWindow(event, window, button_list, overlay);
        }
        // Render step
        window.clear(Color::Black); // Do this in the renderer/job batcher now
        // draw everything here...

        window.draw(text);
        for(auto it = button_list.begin(); it != button_list.end(); ++it) {
            (*it)->Draw(window);
        }
        // end the current frame
        window.display();
    }
}
