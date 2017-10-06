#ifndef EDITOR_SUITE_MENU_H_
#define EDITOR_SUITE_MENU_H_

#include "general.hpp"
#include "game_state.hpp"
#include "transition_button.hpp"
#include "transition_overlay.hpp"

class EditorSuiteMenu : public GameState {
public:
    explicit EditorSuiteMenu(RenderWindow&, ResourceManager&, ConfigHandler&);
    State Display();
};

#endif // EDITOR_SUITE_MENU_H_
