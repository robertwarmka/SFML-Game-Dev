#include "character_handler.hpp"

CharacterHandler::CharacterHandler() {
    character_dir = boost::filesystem::path(boost::filesystem::current_path());
    character_dir += boost::filesystem::path::preferred_separator;
    character_dir += "character_data";
    character_dir += boost::filesystem::path::preferred_separator;
    // Check if character data exists. If not, create the DIR
    if(!boost::filesystem::exists(character_dir)) {
        boost::filesystem::create_directory(character_dir);
    }
}

bool CharacterHandler::CreateNewCharacter(string character_name, vector<DataButton*>& save_button_list) {
    boost::filesystem::path character(character_dir);
    ofstream char_data;
    character += character_name;
    character += ".data";
    if(!boost::filesystem::exists(character)) {
        char_data = ofstream(character.generic_string());
        for(auto it = save_button_list.begin(); it != save_button_list.end(); ++it) {
            char_data << (*it)->ConcatStrings() << endl;
        }
        char_data.close();
        return true;
    }
    return false;
}
