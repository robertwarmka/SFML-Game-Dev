#include "main.hpp"

int main() {
    Logger::createLogFile();
    ResourceManager resource_manager;
    RenderWindow window;
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(0);
    ConfigHandler config_handler(window, resource_manager);
    config_handler.ApplyConfig();
    CharacterHandler character_handler;
    MapHandler map_handler;
    Renderer renderer;

    State game_state = State::MAIN_MENU;
    MainMenu main_menu(window, resource_manager, config_handler, renderer);
    Game game(window, resource_manager, config_handler);
    ConfigMenu config_menu(window, resource_manager, config_handler);
    CharacterCreationMenu char_creation_menu(window, resource_manager, config_handler, character_handler);
    EditorSuiteMenu editor_suite_menu(window, resource_manager, config_handler);
    MapEditMenu map_edit_menu(window, resource_manager, config_handler, map_handler);
    MapEdit map_edit(window, resource_manager, config_handler);
    MapCreationMenu map_creation_menu(window, resource_manager, config_handler, map_handler);
    ObjectEditor object_editor(window, resource_manager, config_handler);

    // run the program as long as the window is open
    while(game_state != State::EXIT) {
        switch(game_state) {
        case State::MAIN_MENU:
            game_state = main_menu.Display();
            break;
        case State::GAME:
            game_state = game.Display();
            break;
        case State::SETTINGS:
            game_state = config_menu.Display();
            config_handler.WriteConfig();
            break;
        case State::SINGLE_PLAYER:
            break;
        case State::CREATE_CHARACTER:
            game_state = char_creation_menu.Display();
            break;
        case State::EDITOR_SUITE_MENU:
            game_state = editor_suite_menu.Display();
            break;
        case State::MAP_EDIT_MENU:
            game_state = map_edit_menu.Display();
            break;
        case State::MAP_EDIT:
            game_state = map_edit.Display();
            break;
        case State::CREATE_MAP:
            game_state = map_creation_menu.Display();
            break;
        case State::OBJECT_EDITOR:
            game_state = object_editor.Display();
            break;
        case State::EXIT:
            break;
        case State::CLICKED:
            cout << "This should never execute here" << endl;
            break;
        case State::NO_CHANGE:
            cout << "This should never execute" << endl;
            break;
        }
    }

    return 0;
}
