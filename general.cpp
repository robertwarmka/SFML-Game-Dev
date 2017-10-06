#include "general.hpp"

string trim(string& str) {
    if(str.empty()) {
        return "";
    }
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if(first == string::npos || last == string::npos) {
        return "";
    }
    return str.substr(first, (last-first+1));
}

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

void path_to_filename(string& file_path) {
    unsigned int pos;
    pos = file_path.find_last_of(boost::filesystem::path::preferred_separator, string::npos);
    if(pos > file_path.length()) {
        return;
    }
    file_path.erase(0, pos + 1); // Last character not erased by default. Need to add 1 to erase final system separator
    pos = file_path.find_first_of(".");
    if(pos > file_path.length()) {
        return;
    }
    file_path.erase(pos, string::npos);
}

STR2INT_ERROR str2int(int &i, char const *s, int base = 0) {
    char *end;
    long  l;
    errno = 0;
    l = strtol(s, &end, base);
    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
        return INT_OVERFLOW;
    }
    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
        return INT_UNDERFLOW;
    }
    if (*s == '\0' || *end != '\0') {
        return INCONVERTIBLE;
    }
    i = l;
    return SUCCESS;
}

time_point<steady_clock> current_time() {
    return steady_clock::now();
}

double micros_time_diff(time_point<steady_clock> start, time_point<steady_clock> end) {
    // Return the absolute value of the time duration, to prevent negative time values
    return abs(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
}

bool is_windows() {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    return true;
    #else
    return false;
    #endif
}
