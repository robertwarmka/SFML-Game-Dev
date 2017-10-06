#ifndef CONFIG_HANDLER_H_
#define CONFIG_HANDLER_H_

#include <fstream>
#include <sstream>
#include <string>
#include "general.hpp"
#include "resource_manager.hpp"

class ResourceManager;

const int min_window_width = 800, min_window_height = 600;
const bool fullscreen_default = false;
const bool borderless_window_default = false;
const Language language_default = ENGLISH;

const string CONFIG_FILE_NAME = "config_file.txt";

class ConfigHandler : public Logger {
public:
    ConfigHandler(RenderWindow&, ResourceManager&);
    bool ReadConfig();
    bool WriteConfig();
    void UpdateConfig(vector<pair<string, string>>);
    void ApplyConfig();
    VideoMode GetDesktopMode();
    Vector2u GetResolution();
    pair<STR2INT_ERROR, STR2INT_ERROR> ParseResolution(const string&, Vector2u&);
    string GetResolutionText();
    bool GetFullScreen();
    bool GetBorderlessWindow();
    Language GetLanguage();
    void ConfigMapDefaults();
    STR2INT_ERROR StringToBool(string&, bool&);
private:
    map<string, string> config_map;
    VideoMode desktop_mode;
    RenderWindow& window;
    ResourceManager& resource_manager;
};

#endif // CONFIG_HANDLER_H_
