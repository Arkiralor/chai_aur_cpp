#pragma once
#include <filesystem>

namespace pathutils {
    // Returns the directory where main.cpp lives (compile-time via __FILE__)
    std::filesystem::path source_dir();

    // Returns the .env path next to main.cpp
    std::filesystem::path env_path();
}