#ifndef GAME_H_
#define GAME_H_

#include "general.hpp"
#include "game_state.hpp"
#include "transition_button.hpp"
#include "general_overlay.hpp"

class Game : public GameState {
public:
    explicit Game(RenderWindow&, ResourceManager&, ConfigHandler&);
    State Display();
};

#endif // GAME_H_
