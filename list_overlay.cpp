#include "list_overlay.hpp"

ListOverlay::ListOverlay(Vector2u window_size, GameState* game_state, ButtonTextData& bt, OverlayData& od) :
    Overlay(window_size, game_state, bt, od) {
    UpdateWindowSize(window_size);
}

void ListOverlay::AddButton(Button* button) {
    if(y_pos == 0.0f) {
        y_pos = ((bt_data.char_size / 1.9f) / window_size.y) * y_scale;
    }
    button->UpdateXPercent(0.5);
    button->UpdateYPercent(y_pos);
    button->SetScale(x_scale, y_scale);
    float y_delta = ((bt_data.char_size * 1.0f) / window_size.y) * y_scale;
    view_bottom = y_pos + ((bt_data.char_size / 1.9f) / window_size.y) * y_scale;
    y_pos += y_delta;
    buttons.push_back(button);
}

void ListOverlay::UpdateWindowSize(Vector2u window_size) {
    this->window_size = window_size;
    // update rectangle position
    rect.setSize(Vector2f(window_size.x, window_size.y));
    view.setSize(Vector2f(window_size.x, window_size.y));
    view.setCenter(window_size.x / 2, window_size.y / 2);
    view_y_center = view.getCenter().y / window_size.y;
    static_view.setSize(Vector2f(window_size.x, window_size.y));
    static_view.setCenter(window_size.x / 2, window_size.y / 2);
    lu_x = od.overlay_location.left * window_size.x;
    lu_y = od.overlay_location.top * window_size.y;
    rl_x = lu_x + (od.overlay_location.width * window_size.x);
    rl_y = lu_y + (od.overlay_location.height * window_size.y);
    left_upper = Vector2f(lu_x, lu_y);
    right_lower = Vector2f(rl_x, rl_y);
    // Calculate new y_pos and y_delta for new window size
    float y_pos = ((bt_data.char_size / 1.9f) / window_size.y) * y_scale;
    // Space text out just a little bit more than the text size
    float y_delta = ((bt_data.char_size * 1.0f) / window_size.y) * y_scale;
    // call updatewindowsize on all buttons
    for(auto it = buttons.begin(); it != buttons.end(); ++it) {
        (*it)->UpdateYPercent(y_pos);
        (*it)->UpdateWindowSize(window_size);
        y_pos += y_delta;
    }
    view_bottom = y_pos + ((bt_data.char_size / 1.9f) / window_size.y) * y_scale;
}
