#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "general.hpp"
#include "resource_manager.hpp"
#include "config_handler.hpp"
#include "button.hpp"
#include "state_button.hpp"
#include "overlay.hpp"
#include "renderer.hpp"

class Overlay;

class GameState {
public:
    Overlay* overlay;
    bool display_overlay;
    RenderWindow& window;
    ResourceManager& resources;
    ConfigHandler& config;
    //Renderer& renderer;
    View default_view;
    vector<Button*> button_list;
    explicit GameState(RenderWindow&, ResourceManager&, ConfigHandler&);
    //explicit GameState(RenderWindow&, ResourceManager&, ConfigHandler&, Renderer&);
    ~GameState();
    virtual State Display() = 0;
    void ResizeWindow(Vector2u, vector<Button*>&, Overlay*);
    void ResizeWindow(Event, RenderWindow&, vector<Button*>&, Overlay*);
};

#endif // GAME_STATE_H
