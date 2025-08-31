#pragma once
#include <string>
#include <unordered_map>

namespace dotenv {

    // Load .env from a file path (default: ".env" in cwd)
    void load(const std::string& path = ".env", bool overwrite = true);

    // Get a variable, with optional default fallback
    std::string get(const std::string& key, const std::string& def = "");

} // namespace dotenv