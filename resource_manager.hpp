#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "general.hpp"
#include "config_handler.hpp"

class ConfigHandler;

const string FONT_FILE = "arial.ttf";

class ResourceManager : public Logger {
public:
    ResourceManager();
    bool LoadMainMenu(Language, ConfigHandler&);
    pair<string, vector<string>> FindButtonText(string);
    void FilterResolution(ConfigHandler&);
    Font& GetFont();
private:
    map<string, pair<string, vector<string>>> main_buttons_text_map;
    map<string, Texture> main_buttons_texture_map;
    Font font;
    VideoMode desktop_mode;
};

#endif
