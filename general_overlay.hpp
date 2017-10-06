#ifndef GENERAL_OVERLAY_H_
#define GENERAL_OVERLAY_H_

#include "general.hpp"
#include "overlay.hpp"

class GeneralOverlay : public Overlay {
public:
    explicit GeneralOverlay(Vector2u, GameState*, ButtonTextData&, OverlayData&);
    State Action(Event);
    void AddButton(Button*);
    void UpdateWindowSize(Vector2u);
};

#endif // GENERAL_OVERLAY_H_
