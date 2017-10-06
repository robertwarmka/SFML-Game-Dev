#include "config_handler.hpp"

ConfigHandler::ConfigHandler(RenderWindow& window, ResourceManager& resource_manager) :
    desktop_mode(VideoMode::getDesktopMode()),
    window(window),
    resource_manager(resource_manager) {
    ConfigMapDefaults();
    logger << "Checking configuration file: " << CONFIG_FILE_NAME << endl;
    if(!ReadConfig()) {
        logger << "Couldn't open configuration file, using default values" << endl;
    }
}

bool ConfigHandler::ReadConfig() {
    ifstream read_config(CONFIG_FILE_NAME);
    if(!read_config.good()) {
        return false;
    }
    vector<string> elems;
    string line, config_name, config_value;
    vector<string>::iterator iter;
    while(getline(read_config, line)) {
        if(line.empty() || line[0] == '#') {
            continue;
        }
        split(line, ':', elems);
        config_name = trim(elems[0]);
        if(elems.size() > 1) {
            config_value = trim(elems[1]);
            config_map[config_name] = config_value;
        }
        config_name.clear();
        config_value.clear();
        elems.clear();
    }
    read_config.close();
    return true;
}

// Save config when transitioning out of config menu. Then config only lost if abnormal exit in config menu screen.
bool ConfigHandler::WriteConfig() {
    ofstream write_config(CONFIG_FILE_NAME, ios::trunc);
    if(!write_config.good()) {
        logger << "Couldn't write configuration file. Next open of program might have default values." << endl;
        return false;
    }
    // Write configuration values
    for(auto it = config_map.begin(); it != config_map.end(); ++it) {
        write_config << it->first << ": " << it->second << endl;
    }
    write_config.close();
    return true;
}

void ConfigHandler::UpdateConfig(vector<pair<string, string>> update_list) {
    for(auto it = update_list.begin(); it != update_list.end(); ++it) {
        config_map[it->first] = it->second;
    }
    ApplyConfig();
}

void ConfigHandler::ApplyConfig() {
    Vector2u resolution = GetResolution();
    if(GetFullScreen()) {
        window.create(VideoMode(resolution.x, resolution.y), "Phoenix Risen", sf::Style::Fullscreen);
        window.setVerticalSyncEnabled(true);
        //window.setFramerateLimit(0);
    } else {
        if(GetBorderlessWindow()) {
            window.create(VideoMode(desktop_mode.width, desktop_mode.height), "Phoenix Risen", sf::Style::None);
            window.setVerticalSyncEnabled(true);
            //window.setFramerateLimit(0);
        } else {
            window.create(VideoMode(resolution.x, resolution.y), "Phoenix Risen", sf::Style::Resize);
            window.setVerticalSyncEnabled(true);
            //window.setFramerateLimit(0);
        }
    }
    if(resource_manager.LoadMainMenu(GetLanguage(), *this) != true) {
        logger << "Resource manager wasn't able to load data, crash likely imminent" << endl;
    }
}

VideoMode ConfigHandler::GetDesktopMode() {
    return desktop_mode;
}

Vector2u ConfigHandler::GetResolution() {
    Vector2u screen_res;
    pair<STR2INT_ERROR, STR2INT_ERROR> errs;
    errs = ParseResolution(config_map["Resolution"], screen_res);
    if(errs.first != SUCCESS || errs.second != SUCCESS) {
        logger << "Unknown param entry for Resolution. Allowed values are: <integer>x<integer>." << endl;
        logger << "Width must be >= 640, Height must be >= 480. Example: 1920x1080" << endl;
    }
    return screen_res;
}

pair<STR2INT_ERROR, STR2INT_ERROR> ConfigHandler::ParseResolution(const string& resolution_string, Vector2u& screen_res) {
    vector<string> elems;
    STR2INT_ERROR err1, err2;
    int x, y;
    split(resolution_string, 'x', elems);
    err1 = str2int(x, elems[0].c_str(), 0);
    err2 = str2int(y, elems[1].c_str(), 0);
    if(err1 == SUCCESS && err2 == SUCCESS && x >= min_window_width && y >= min_window_height) {
        screen_res.x = x;
        screen_res.y = y;
    } else {
        // Couldn't understand width of window size, log error, take default window sizes
        logger << "Unknown resolution. Allowed values are: <integer>x<integer>." << endl;
        logger << "Width must be >= " << min_window_width << ", Height must be >= " << min_window_height <<". Example: 1920x1080" << endl;
        screen_res.x = min_window_width;
        screen_res.y = min_window_height;
    }
    return make_pair(err1, err2);
}

string ConfigHandler::GetResolutionText() {
    return config_map["Resolution"];
}

bool ConfigHandler::GetFullScreen() {
    bool fullscreen;
    STR2INT_ERROR err1 = StringToBool(config_map["Fullscreen"], fullscreen);
    if(err1 != SUCCESS) {
        // Couldn't understand config_name entry, log error, take default fullscreen param
        logger << "Unknown param entry for: Fullscreen. Allowed values are: 0 (false), 1 (true)" << endl;
        fullscreen = fullscreen_default;
    }
    return fullscreen;
}

bool ConfigHandler::GetBorderlessWindow() {
    bool borderless_window;
    STR2INT_ERROR err1 = StringToBool(config_map["Borderless Window"], borderless_window);
    if(err1 != SUCCESS) {
        logger << "Unknown param entry for: Borderless Window. Allowed values are: 0 (false), 1 (true)" << endl;
        borderless_window = borderless_window_default;
    }
    return borderless_window;
}

Language ConfigHandler::GetLanguage() {
    Language language;
    string fullscreen_string = config_map["Language"];
    int temp;
    STR2INT_ERROR err1;
    err1 = str2int(temp, fullscreen_string.c_str(), 0);
    if(err1 == SUCCESS && temp > Language::BEGIN && temp < Language::END) {
        language = (Language)temp;
    } else {
        // Couldn't understand config_name entry, log error, take default language param
        logger << "Unknown param entry for: Language. Allowed values are: 1 (English)" << endl;
        language = language_default;
    }
    return language;
}

void ConfigHandler::ConfigMapDefaults() {
    config_map.emplace("Resolution", "800x600");
    config_map.emplace("Fullscreen", "0");
    config_map.emplace("Language", "1"); // Default is English=1
}

STR2INT_ERROR ConfigHandler::StringToBool(string& str, bool& val) {
    int temp;
    STR2INT_ERROR err1;
    err1 = str2int(temp, str.c_str(), 0);
    val = (temp == 0) ? false : true;
    return err1;
}
