#include "overlay.hpp"

Overlay::Overlay(Vector2u window_size, GameState* game_state, ButtonTextData& bt, OverlayData& od) :
    Drawable(window_size),
    menu(game_state),
    bt_data(bt),
    od(od) {
    // Set fill color of the overlay rectangle
    rect.setFillColor(od.color);
    // Set rectangle position to 0. Ensure rectangle fills whole screen
    rect.setPosition(0, 0);
    //UpdateWindowSize(window_size);
    x_scale = 1.0f / od.overlay_location.width;
    y_scale = 1.0f / od.overlay_location.height;
    view.setViewport(od.overlay_location);
    static_view.setViewport(od.overlay_location);
    bt_data.x_scale = x_scale;
    bt_data.y_scale = y_scale;
    // Set constraints for how far the view can scroll
    y_pos = 0.0f;
    view_top = 0.0f;
    view_bottom = 0.0f;
    view_y_center = 0.5f;
    // No button selected yet, so set to nullptr
    selected_button = nullptr;
}

Overlay::~Overlay() {
    for(auto it = buttons.begin(); it != buttons.end(); ++it) {
        delete *it;
    }
}

void Overlay::Draw(RenderWindow& window) {
    // Backup the window's current view, needs to be an object, not a reference
    // Otherwise on view restore, it will keep the overlay view (because it's a reference, duh)
    const View windowView = window.getView();
    // Change window's view to our static view for non-moving objects (borders, etc.)
    window.setView(static_view);
    // draw rectangle
    window.draw(rect);
    // Change window's view to our dynamic view for moving objects
    window.setView(view);
    // draw text choices (buttons? maybe..)
    for(auto it = buttons.begin(); it != buttons.end(); ++it) {
        (*it)->Draw(window);
    }
    // Reset window view to what it was before this drawing
    window.setView(windowView);
}

void Overlay::Animate(float x, float y) {
    if(x >= lu_x && x <= rl_x && y >= lu_y && y <= rl_y) {
        x = (x - lu_x) * x_scale;
        y = (y - lu_y) * y_scale + MouseScrollOffset();
    } else {
        // Set x and y to a large negative number so nothing on screen animates,
        // but still animate so things will un-animate when mouse outside of overlay
        x = -1000;
        y = -1000;
    }
    for(auto it = buttons.begin(); it != buttons.end(); ++it) {
        (*it)->Animate(x, y);
    }
}

void Overlay::ScrollView(float scroll) {
    if(view_bottom > 1.0) {
        scroll *= -50; // Constant number sets scroll speed. TODO: Maybe change this to a config parameter?
        view_y_center = view.getCenter().y / window_size.y;
        float y_shift = scroll / window_size.y;
        // Subtract or add 0.5f to subtract or add half the screen. Center - 0.5 -> Top, Center + 0.5 -> Bottom
        // This is a bounds check to ensure we can't scroll above the top button or below the bottom button
        if(view_y_center + y_shift - 0.5f < view_top) {
            y_shift = (view_top + 0.5f) - view_y_center;
        } else if(view_y_center + y_shift + 0.5f > view_bottom) {
            y_shift = (view_bottom - 0.5f) - view_y_center;
        }
        // convert y_shift from window percentage back into translatable pixel units
        view.move(0, y_shift * window_size.y);
        view_y_center += y_shift;
    }
}

float Overlay::MouseScrollOffset() {
    // Subtract 0.5f to subtract half the screen. Center - 0.5 -> Top
    return (view_y_center - 0.5f) * window_size.y;
}

void Overlay::ClearData() {
    for(auto it = buttons.begin(); it != buttons.end(); ++it) {
        delete *it;
    }
    buttons.clear();
    // Reset internal variables so that new buttons get proper placements in overlay
    y_pos = 0.0f;
    view_bottom = 0.0f;
    view_y_center = 0.5f;
}
