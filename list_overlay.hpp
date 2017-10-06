#ifndef LIST_OVERLAY_H_
#define LIST_OVERLAY_H_

#include "general.hpp"
#include "overlay.hpp"

class ListOverlay : public Overlay {
public:
    explicit ListOverlay(Vector2u, GameState*, ButtonTextData&, OverlayData&);
    void AddButton(Button*);
    void UpdateWindowSize(Vector2u);
};

#endif // LIST_OVERLAY_H_
