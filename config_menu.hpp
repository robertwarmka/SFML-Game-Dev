#ifndef CONFIGURATION_MENU_H
#define CONFIGURATION_MENU_H

#include "general.hpp"
#include "game_state.hpp"
#include "image_button.hpp"
#include "transition_button.hpp"
#include "state_int_button.hpp"
#include "state_string_button.hpp"
#include "apply_changes_button.hpp"
#include "overlay_string_button.hpp"

class ConfigMenu : public GameState {
protected:
    vector<StateButton*> save_button_list;
public:
    explicit ConfigMenu(RenderWindow&, ResourceManager&, ConfigHandler&);
    State Display();
};

#endif // CONFIGURATION_MENU_H
