#include "map_handler.hpp"

MapHandler::MapHandler() {
    map_dir = path(boost::filesystem::current_path());
    map_dir += path::preferred_separator;
    map_dir += "map_data";
    map_dir += path::preferred_separator;
    // Check if map data exists. If not, create the DIR
    if(!exists(map_dir)) {
        create_directory(map_dir);
    }
    if(!LoadMapNames()) {
        logger << "ERROR: Couldn't load Map names." << endl;
    }
}

bool MapHandler::LoadMapNames() {
    map_names.clear();
    boost::filesystem::directory_iterator dir_itr;
    if(exists(map_dir) && is_directory(map_dir)) {
        vector<path> v;
        string map_name;
        copy(directory_iterator(map_dir), directory_iterator(), back_inserter(v));
        sort(v.begin(), v.end());
        for (vector<path>::const_iterator it(v.begin()); it != v.end(); ++it) {
            map_name = it->string();
            path_to_filename(map_name);
            cout << map_name << endl;
            map_names.push_back(map_name);
        }
        return true;
    }
    return false;
}

vector<string> MapHandler::GetMapNames() {
    return map_names;
}

bool MapHandler::CreateNewMap(string map_name) {
    path map(map_dir);
    ofstream map_data;
    map += map_name;
    map += ".data";
    if(!exists(map)) {
        map_data = ofstream(map.generic_string());
        map_data.close();
        LoadMapNames();
        return true;
    }
    return false;
}
