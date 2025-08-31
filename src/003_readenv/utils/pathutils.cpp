#include "pathutils.h"

namespace pathutils {

std::filesystem::path source_dir() {
    // __FILE__ expands to the *current file* in this translation unit.
    // Since we’re compiling pathutils.cpp, we can hardcode main.cpp location
    // OR better: let the caller pass __FILE__.
    // To keep it automatic for main.cpp, we inline __FILE__ here.
    static std::filesystem::path source_file = __FILE__;
    return source_file.parent_path().parent_path(); 
    // because __FILE__ here is ".../src/utils/pathutils.cpp"
    // so parent_path() = ".../src/utils"
    // parent_path() again = ".../src"
}

std::filesystem::path env_path() {
    return source_dir() / ".env";
}

}