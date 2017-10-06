#ifndef TRANSITION_OVERLAY_H_
#define TRANSITION_OVERLAY_H_

#include "general.hpp"
#include "drawable.hpp"
#include "list_overlay.hpp"
#include "choice_button.hpp"
#include "state_button.hpp"

class TransitionOverlay : public ListOverlay {
public:
    explicit TransitionOverlay(Vector2u, GameState*, ButtonTextData&, OverlayData&);
    State Action(Event);
};

#endif // TRANSITION_OVERLAY_H_
