#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "general.hpp"
#include "game_state.hpp"
#include "image_button.hpp"
#include "transition_button.hpp"
#include "state_int_button.hpp"
#include "state_string_button.hpp"

class MainMenu : public GameState {
public:
    Renderer& renderer;
    explicit MainMenu(RenderWindow&, ResourceManager&, ConfigHandler&, Renderer&);
    State Display();
};

#endif // MAIN_MENU_H
