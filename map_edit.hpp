#ifndef MAP_EDIT_H_
#define MAP_EDIT_H_

#include "general.hpp"
#include "game_state.hpp"
#include "map_handler.hpp"
#include "transition_button.hpp"

class MapEdit : public GameState {
public:
    explicit MapEdit(RenderWindow&, ResourceManager&, ConfigHandler&);
    State Display();
};

#endif // MAP_EDIT_H_
