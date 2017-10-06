#ifndef OBJECT_EDITOR_H_
#define OBJECT_EDITOR_H_

#include "general.hpp"
#include "game_state.hpp"
#include "transition_button.hpp"
#include "general_overlay.hpp"

class ObjectEditor : public GameState {
public:
    explicit ObjectEditor(RenderWindow&, ResourceManager&, ConfigHandler&);
    State Display();
};

#endif // OBJECT_EDITOR_H_
