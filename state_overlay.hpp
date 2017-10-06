#ifndef STATE_OVERLAY_H_
#define STATE_OVERLAY_H_

#include "general.hpp"
#include "drawable.hpp"
#include "list_overlay.hpp"
#include "choice_button.hpp"
#include "state_button.hpp"

class StateOverlay : public ListOverlay {
protected:
    StateButton* button;
public:
    explicit StateOverlay(Vector2u, GameState*, ButtonTextData&, OverlayData&, StateButton*);
    State Action(Event);
};

#endif // STATE_OVERLAY_H_
