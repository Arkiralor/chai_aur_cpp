#include "str_utils.h"
#include <cctype>

/*
Function to convert a given string to title-case.

Example:
    input:
        The S is silent in Spain.
    output:
        The S Is Silent In Spain.
*/
std::string toTitleCase(const std::string& value){
    std::string result = value;

    bool capitalizeNext = true;

    for (char& c : result) { // Iterate through each character in the string
        if (std::isspace(c)) { // If the character is a space
            capitalizeNext = true; // Set flag to true for the next character
        } else if (capitalizeNext) { // If the flag is true (start of a new word)
            c = std::toupper(c); // Capitalize the current character
            capitalizeNext = false; // Reset the flag
        } else {
            c = std::tolower(c); // Convert subsequent characters in the word to lowercase
        }
    }

    return result;
}

/*
Function to remove only the leading and trailing whitespaces in a given string.
*/
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return ""; // string is all spaces
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}