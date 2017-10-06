#ifndef GENERAL_H_
#define GENERAL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <list>
#include <memory>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <boost/filesystem.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include <SFML/Graphics.hpp>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::u32string;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::flush;
using std::vector;
using std::stringstream;
using std::istringstream;
using std::ostringstream;
using std::iterator;
using std::map;
using std::list;
using std::unique_ptr;
using std::chrono::steady_clock;
using std::chrono::time_point;
using std::min;
using std::max;
using std::pair;
using std::make_pair;
using sf::Sprite;
using sf::String;
using sf::Texture;
using sf::Vector2i;
using sf::Vector2u;
using sf::Vector2f;
using sf::RenderWindow;
using sf::Event;
using sf::Color;
using sf::Font;
using sf::Text;
using sf::FloatRect;
using sf::Time;
using sf::Mouse;
using sf::VideoMode;
using sf::View;
using sf::RectangleShape;

const string logFile = "logfile.log";

enum class State { NO_CHANGE, GAME, EXIT, MAIN_MENU, SINGLE_PLAYER, SETTINGS, CREATE_CHARACTER, MAP_EDIT_MENU, MAP_EDIT, CREATE_MAP, EDITOR_SUITE_MENU, OBJECT_EDITOR,
             CLICKED };

enum Language { BEGIN, ENGLISH, END };

enum STR2INT_ERROR { SUCCESS, INT_OVERFLOW, INT_UNDERFLOW, INCONVERTIBLE };

class ButtonTextData {
public:
    // Text-specific data
    string display_string;
    Font font;
    float char_size;
    float select_scale_change;
    vector<string> strings;
    int current_state;
    Color normal_color;
    Color select_color;
    double animation_time_millis;
    float x_scale, y_scale;
    bool windows_pathfile;

    ButtonTextData() : display_string(""),
        char_size(12),
        select_scale_change(1.2f),
        strings(),
        current_state(0),
        animation_time_millis(100),
        x_scale(1.0f),
        y_scale(1.0f),
        windows_pathfile(false) {}

    ButtonTextData(const ButtonTextData& btd) {
        this->display_string = btd.display_string;
        this->font = btd.font;
        this->char_size = btd.char_size;
        this->select_scale_change = btd.select_scale_change;
        this->strings = btd.strings;
        this->current_state = btd.current_state;
        this->normal_color = btd.normal_color;
        this->select_color = btd.select_color;
        this->animation_time_millis = btd.animation_time_millis;
        this->x_scale = btd.x_scale;
        this->y_scale = btd.y_scale;
        this->windows_pathfile = btd.windows_pathfile;
    }

    void operator=(const ButtonTextData& btd) {
        this->display_string = btd.display_string;
        this->font = btd.font;
        this->char_size = btd.char_size;
        this->select_scale_change = btd.select_scale_change;
        this->strings = btd.strings;
        this->current_state = btd.current_state;
        this->normal_color = btd.normal_color;
        this->select_color = btd.select_color;
        this->animation_time_millis = btd.animation_time_millis;
        this->x_scale = btd.x_scale;
        this->y_scale = btd.y_scale;
        this->windows_pathfile = btd.windows_pathfile;
    }

    void SetCurrentState(int state) {
        this->current_state = state;
    }
    void SetCurrentState(string str) {
        for(auto it = strings.begin(); it != strings.end(); ++it) {
            if((*it).compare(str) == 0) {
                this->current_state = it - strings.begin();
                return;
            }
        }
        current_state = 0;
    }
    int GetCurrentState() {
        return current_state;
    }
};

class OverlayData {
public:
    // Overlay-specific data
    FloatRect overlay_location;
    Color color;
    State state;
    bool always_visible;

    explicit OverlayData(const FloatRect& overlay_location, const Color color, const State state, bool always_visible) :
        overlay_location(overlay_location),
        color(color),
        state(state),
        always_visible(always_visible) {}

    OverlayData(const OverlayData& od) {
        this->overlay_location = od.overlay_location;
        this->color = od.color;
        this->state = od.state;
        this->always_visible = od.always_visible;
    }

    void operator=(const OverlayData& od) {
        this->overlay_location = od.overlay_location;
        this->color = od.color;
        this->state = od.state;
        this->always_visible = od.always_visible;
    }
private:
};

class Logger {
protected:
    Logger() {
        logger.open(logFile, ios::app);
    }
    ~Logger() {
        logger.close();
    }
    ofstream logger;
public:
    static void createLogFile() {
        ofstream open_log;
        open_log.open(logFile, ios::trunc);
        open_log.close();
    }
};

string trim(string&);
void split(const string&, char, vector<string>&);
vector<string> split(const string&, char);
void path_to_filename(string&);
STR2INT_ERROR str2int(int&, char const*, int);
time_point<steady_clock> current_time();
double micros_time_diff(time_point<steady_clock>, time_point<steady_clock>);
bool is_windows();

#endif // GENERAL_
