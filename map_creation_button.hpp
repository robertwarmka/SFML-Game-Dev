#ifndef MAP_CREATION_BUTTON_H_
#define MAP_CREATION_BUTTON_H_

#include "general.hpp"
#include "transition_button.hpp"
#include "map_handler.hpp"
#include "state_button.hpp"
#include "text_box_button.hpp"

class MapCreationButton : public TransitionButton {
public:
    explicit MapCreationButton(ButtonTextData&, Vector2u, float, float, State,
        MapHandler&, RenderWindow&, TextBoxButton&);
    State Action(Event);
protected:
    MapHandler& map_handler;
    RenderWindow& window;
    TextBoxButton& map_name_button;
};

#endif // MAP_CREATION_BUTTON_H_
