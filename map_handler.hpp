#ifndef MAP_HANDLER_H_
#define MAP_HANDLER_H_

#include "general.hpp"
#include "data_button.hpp"
#include <boost/filesystem.hpp>

using boost::filesystem::path;
using boost::filesystem::exists;
using boost::filesystem::is_directory;
using boost::filesystem::directory_iterator;
using std::string;

class MapHandler : public Logger {
protected:
    path map_dir;
    vector<string> map_names;
public:
    MapHandler();
    bool LoadMapNames();
    vector<string> GetMapNames();
    bool CreateNewMap(string);

};

#endif // MAP_HANDLER_H_
