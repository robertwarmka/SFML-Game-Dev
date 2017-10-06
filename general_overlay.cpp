#include "general_overlay.hpp"

GeneralOverlay::GeneralOverlay(Vector2u window_size, GameState* game_state, ButtonTextData& bt_data, OverlayData& od) :
    Overlay(window_size, game_state, bt_data, od) {
    UpdateWindowSize(window_size);
}

State GeneralOverlay::Action(Event event) {
    if(event.type == Event::MouseButtonPressed) {
        if(Intersect(event.mouseButton.x, event.mouseButton.y)) {
            if(event.mouseButton.button == sf::Mouse::Button::Left) {
                // Defining these because I am way too lazy to write the long-ass if statement with the full event variable name
                float mb_x = event.mouseButton.x;
                float mb_y = event.mouseButton.y;
                if(mb_x >= lu_x && mb_x <= rl_x && mb_y >= lu_y && mb_y <= rl_y) {
                    // Subtract the lower bounds from it to account for overlay offset inside window
                    // Multiply by overlay scale to accommodate scaling
                    mb_x = (mb_x - lu_x) * x_scale;
                    mb_y = (mb_y - lu_y) * y_scale + MouseScrollOffset();
                    event.mouseButton.x = mb_x;
                    event.mouseButton.y = mb_y;
                    State state;
                    for(auto it = buttons.begin(); it != buttons.end(); ++it) {
                        state = (*it)->Action(event);
                        // If button transitions to something, go there
                        if(state != State::NO_CHANGE) {
                            //selected_button = (*it);
                            return state;
                        }
                    }
                }
            }
        } else if(!od.always_visible) {
            menu->overlay = nullptr;
        }
    } else if(event.type == Event::MouseWheelScrolled) {
        ScrollView(event.mouseWheelScroll.delta);
    }
    return State::NO_CHANGE;
}

void GeneralOverlay::AddButton(Button* button) {
    button->SetScale(x_scale, y_scale);
    buttons.push_back(button);
}

void GeneralOverlay::UpdateWindowSize(Vector2u window_size) {
    this->window_size = window_size;
    // update rectangle position
    rect.setSize(Vector2f(window_size.x, window_size.y));
    view.setSize(Vector2f(window_size.x, window_size.y));
    view.setCenter(window_size.x / 2, window_size.y / 2);
    static_view.setSize(Vector2f(window_size.x, window_size.y));
    static_view.setCenter(window_size.x / 2, window_size.y / 2);
    lu_x = od.overlay_location.left * window_size.x;
    lu_y = od.overlay_location.top * window_size.y;
    rl_x = lu_x + (od.overlay_location.width * window_size.x);
    rl_y = lu_y + (od.overlay_location.height * window_size.y);
    left_upper = Vector2f(lu_x, lu_y);
    right_lower = Vector2f(rl_x, rl_y);
    // call updatewindowsize on all buttons
    for(auto it = buttons.begin(); it != buttons.end(); ++it) {
        (*it)->UpdateWindowSize(window_size);
    }
}
