#include "resource_manager.hpp"

ResourceManager::ResourceManager() :
    desktop_mode(VideoMode::getDesktopMode()) {
    if (!font.loadFromFile(FONT_FILE)) {
        logger << "Failed to load font file: " << FONT_FILE << endl;
        exit(1);
    }
}

bool ResourceManager::LoadMainMenu(Language language, ConfigHandler& config) {
    main_buttons_text_map.clear();
    string button_text_file;
    switch(language) {
    case Language::BEGIN: // Should never execute, but defaults to English if it does
        button_text_file = "button_text_eng.txt";
        break;
    case Language::ENGLISH:
        button_text_file = "button_text_eng.txt";
        break;
    case Language::END: // Should never execute, but defaults to English if it does
        button_text_file = "button_text_eng.txt";
        break;
    }
    ifstream button_text_stream(button_text_file);
    if(!button_text_stream.good()) {
        return false;
    }
    vector<string> meaning_split, button_split, items, strings;
    string line, button_name, button_display_name, item;
    bool detect_bom = true;
    while(getline(button_text_stream, line)) {
        if(line.empty() || line[0] == '#') {
            continue;
        }
        // Checking for UTF-8 BOM (beware the UTF-8 BOM)
        // detect_bom flag here as a cheap trick to only check this if statement if we're looking at the first line of the
        // file, otherwise we might be messing with real data! Basically it's just a flag that will allow the if statement
        // to execute for the first line of the file, and not again afterwards
        if(detect_bom && line.size() >= 3 && (uint8_t)line[0] == 239 && (uint8_t)line[1] == 187 && (uint8_t)line[2] == 191) {
            line = line.substr(3);
        }
        // Set detect_bom to false, because UTF-8 BOM will only exist at the start of the file
        detect_bom = false;
        split(line, ':', meaning_split);
        button_name = trim(meaning_split[0]);
        if(meaning_split.size() > 1) {
            split(meaning_split[1], '|', button_split);
            button_display_name = trim(button_split[0]);
            if(button_split.size() > 1) {
                split(button_split[1], ',', items);
                for(auto it = items.begin(); it != items.end(); ++it) {
                    item = trim(*it);
                    if(!item.empty()) {
                        strings.push_back(item);
                    }
                }
            }
            main_buttons_text_map[button_name] = make_pair(button_display_name, strings);
        }
        button_name.clear();
        button_display_name.clear();
        item.clear();
        meaning_split.clear();
        button_split.clear();
        items.clear();
        strings.clear();
    }
    FilterResolution(config);
    return true;
}

pair<string, vector<string>> ResourceManager::FindButtonText(string button_name) {
    auto text = main_buttons_text_map.find(button_name);
    if(text != main_buttons_text_map.end()) {
        return text->second;
    } else {
        logger << "Could not find button text for button name: " << button_name << endl;
        return pair<string, vector<string>>();
    }
}

void ResourceManager::FilterResolution(ConfigHandler& config) {
    pair<string, vector<string>> resolutions_pair = main_buttons_text_map["Resolution"];
    vector<string> resolutions = resolutions_pair.second;
    pair<STR2INT_ERROR, STR2INT_ERROR> errs;
    Vector2u resolution_value;
    for(auto it = resolutions.begin(); it != resolutions.end(); ++it) {
        errs = config.ParseResolution((*it), resolution_value);
        if(errs.first != SUCCESS || errs.second != SUCCESS) {
            logger << "Can't parse resolution string: " << (*it) << " in FilterResolution. Errors may occur." << endl;
        }
        if(resolution_value.x > desktop_mode.width || resolution_value.y > desktop_mode.height) {
            resolutions.erase(it);
            --it;
        }
    }
    resolutions_pair.second = resolutions;
    main_buttons_text_map["Resolution"] = resolutions_pair;
}

Font& ResourceManager::GetFont() {
    return this->font;
}
