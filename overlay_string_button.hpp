#ifndef OVERLAY_STRING_BUTTON_H_
#define OVERLAY_STRING_BUTTON_H_

#include "general.hpp"
#include "state_string_button.hpp"
#include "state_overlay.hpp"
#include "game_state.hpp"

class GameState;

class OverlayStringButton : public StateStringButton {
protected:
    StateOverlay overlay;
    GameState* menu;
public:
    explicit OverlayStringButton(ButtonTextData&, Vector2u, float, float, State, bool, OverlayData, GameState*);
    State Action(Event);
    void UpdateWindowSize(Vector2u);
};

#endif // OVERLAY_STRING_BUTTON_H_
