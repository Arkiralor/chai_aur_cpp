#include<iostream>
#include<cstdlib>
#include <filesystem>

#include "utils/dotenv.h"
#include "utils/pathutils.h"

#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "fmt/core.h"

int main(){
    auto envPath = pathutils::env_path();
    std::cout << "Loading environment variable from\t" << envPath << std::endl;

    dotenv::load(envPath, true);
    const char* varName;

    std::string input;
    std::cout << "Enter the name of the environment variable:\t";
    std::getline(std::cin, input);
    std::cout<<"\n";
    varName = input.c_str();
    if (!varName) {
        std::cerr << "Error: Environment variable name is null." << std::endl;
        return 1;
    }


    const char* envVarValue = std::getenv(varName);
    if(envVarValue != NULL){
        std::string succcessMessage = fmt::format("{} = \"{}\"", varName, envVarValue);
        std::cout << succcessMessage << std::endl;
    } else {
        std::string failureMessage = fmt::format("{} is not set.", varName);
        std::cout << failureMessage << std::endl;
        return 1;
    }
    return 0;
}