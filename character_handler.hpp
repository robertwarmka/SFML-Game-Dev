#ifndef CHARACTER_HANDLER_H_
#define CHARACTER_HANDLER_H_

#include "general.hpp"
#include "data_button.hpp"
#include <boost/filesystem.hpp>

class CharacterHandler {
protected:
    boost::filesystem::path character_dir;
public:
    CharacterHandler();
    bool CreateNewCharacter(string, vector<DataButton*>&);
};

#endif
