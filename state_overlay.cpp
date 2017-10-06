#include "state_overlay.hpp"

StateOverlay::StateOverlay(Vector2u window_size, GameState* game_state, ButtonTextData& bt, OverlayData& od, StateButton* overlay_button) :
    ListOverlay(window_size, game_state, bt, od) {
    // Set state button to track for Action function
    button = overlay_button;
}

State StateOverlay::Action(Event event) {
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
                        if(state == State::CLICKED) {
                            // set button text data
                            button->UpdateState(((ChoiceButton*)(*it))->GetState());
                            menu->overlay = nullptr;
                            break;
                        }
                    }
                }
            }
        } else {
            menu->overlay = nullptr;
        }
    } else if(event.type == Event::MouseWheelScrolled) {
        ScrollView(event.mouseWheelScroll.delta);
    }
    return State::NO_CHANGE;
}
