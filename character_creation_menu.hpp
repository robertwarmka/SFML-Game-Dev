#ifndef CHARACTER_CREATION_MENU_H
#define CHARACTER_CREATION_MENU_H

#include "general.hpp"
#include "game_state.hpp"
#include "character_handler.hpp"
#include "image_button.hpp"
#include "transition_button.hpp"
#include "data_button.hpp"
#include "text_box_button.hpp"
#include "character_creation_button.hpp"

class CharacterCreationMenu : public GameState {
protected:
    CharacterHandler& character_handler;
    TextBoxButton* character_name_button;
    vector<DataButton*> save_button_list;
public:
    explicit CharacterCreationMenu(RenderWindow&, ResourceManager&, ConfigHandler&, CharacterHandler&);
    State Display();
};

#endif // CHARACTER_CREATION_MENU_H
