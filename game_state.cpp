#include "game_state.hpp"

GameState::GameState(RenderWindow& window, ResourceManager& resources, ConfigHandler& config) :
    overlay(nullptr),
    display_overlay(false),
    window(window),
    resources(resources),
    config(config),
    default_view(window.getView()) {}

/*GameState::GameState(RenderWindow& window, ResourceManager& resources, ConfigHandler& config, Renderer& renderer) :
    overlay(nullptr),
    display_overlay(false),
    window(window),
    resources(resources),
    config(config),
    renderer(renderer),
    default_view(window.getView()) {}*/

GameState::~GameState() {
    // Delete allocated Button pointers - all buttons should be part of button list so only delete this master list
    // so that we never hit a double delete
    for(auto it = button_list.begin(); it != button_list.end(); ++it) {
        delete *it;
    }
    if(overlay != nullptr) {
        delete overlay;
    }
}

void GameState::ResizeWindow(Vector2u window_size, vector<Button*>& button_list, Overlay* overlay) {
    // This function assumes the window size is a valid size. If this isn't true, this'll have to change
    if(overlay != nullptr) {
        overlay->UpdateWindowSize(window_size);
    }
    for(auto it = button_list.begin(); it != button_list.end(); ++it) {
        (*it)->UpdateWindowSize(window_size);
    }
    window.setView(View(FloatRect(0, 0, window_size.x, window_size.y)));
}

void GameState::ResizeWindow(Event event, RenderWindow& window, vector<Button*>& button_list, Overlay* overlay) {
    if(event.type == Event::Resized) {
        unsigned int x, y;
        x = (event.size.width < min_window_width) ? min_window_width : event.size.width;
        y = (event.size.height < min_window_height) ? min_window_height : event.size.height;
        window.setSize(Vector2u(x, y));
        Vector2u window_size(event.size.width, event.size.height);
        if(overlay != nullptr) {
            overlay->UpdateWindowSize(window_size);
        }
        for(auto it = button_list.begin(); it != button_list.end(); ++it) {
            (*it)->UpdateWindowSize(window_size);
        }
        window.setView(View(FloatRect(0, 0, event.size.width, event.size.height)));
    }
}
