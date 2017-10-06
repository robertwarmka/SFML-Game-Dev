#ifndef MAP_EDIT_MENU_H_
#define MAP_EDIT_MENU_H_

#include "general.hpp"
#include "game_state.hpp"
#include "map_handler.hpp"
#include "image_button.hpp"
#include "transition_button.hpp"
#include "data_button.hpp"
#include "transition_overlay.hpp"

class MapEditMenu : public GameState {
protected:
    MapHandler& map_handler;
public:
    explicit MapEditMenu(RenderWindow&, ResourceManager&, ConfigHandler&, MapHandler&);
    State Display();
};

#endif // MAP_EDIT_MENU_H_
