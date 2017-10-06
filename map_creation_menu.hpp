#ifndef MAP_CREATION_MENU_H_
#define MAP_CREATION_MENU_H_

#include "general.hpp"
#include "game_state.hpp"
#include "map_handler.hpp"
#include "image_button.hpp"
#include "transition_button.hpp"
#include "data_button.hpp"
#include "text_box_button.hpp"
#include "map_creation_button.hpp"

class MapCreationMenu : public GameState {
protected:
    MapHandler& map_handler;
    TextBoxButton* map_name_button;
    vector<DataButton*> save_button_list;
public:
    explicit MapCreationMenu(RenderWindow&, ResourceManager&, ConfigHandler&, MapHandler&);
    State Display();
};

#endif // MAP_CREATION_MENU_H_
