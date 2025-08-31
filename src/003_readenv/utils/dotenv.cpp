#include "dotenv.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

#if defined(_WIN32)
    #include <windows.h>
#endif

namespace {

// trim helpers
inline std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// platform-specific setenv wrapper
inline void set_env(const std::string& key, const std::string& value, bool overwrite) {
#if defined(_WIN32)
    if (!overwrite && getenv(key.c_str())) return;
    _putenv_s(key.c_str(), value.c_str());
#else
    setenv(key.c_str(), value.c_str(), overwrite ? 1 : 0);
#endif
}

} // anonymous namespace

namespace dotenv {

void load(const std::string& path, bool overwrite) {
    std::ifstream file(path);
    if (!file) return; // silently ignore if no .env

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        auto eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key = trim(line.substr(0, eq));
        std::string val = trim(line.substr(eq + 1));

        // strip optional surrounding quotes
        if ((val.size() >= 2) &&
            ((val.front() == '"' && val.back() == '"') ||
             (val.front() == '\'' && val.back() == '\''))) {
            val = val.substr(1, val.size() - 2);
        }

        set_env(key, val, overwrite);
    }
}

std::string get(const std::string& key, const std::string& def) {
    const char* v = std::getenv(key.c_str());
    return v ? std::string(v) : def;
}

} // namespace dotenv