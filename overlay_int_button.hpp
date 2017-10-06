#ifndef OVERLAY_INT_BUTTON_H_
#define OVERLAY_INT_BUTTON_H_

#include "general.hpp"
#include "state_int_button.hpp"
#include "state_overlay.hpp"
#include "game_state.hpp"

class GameState;

class OverlayIntButton : public StateIntButton {
protected:
    StateOverlay overlay;
    GameState* menu;
public:
    explicit OverlayIntButton(ButtonTextData&, Vector2u, float, float, State, bool, OverlayData, GameState*);
    State Action(Event);
    void UpdateWindowSize(Vector2u);
};

#endif
