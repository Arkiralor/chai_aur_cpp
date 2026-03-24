#include "string_holder.h"

#include <format>
#include <iostream>

StringHolder::StringHolder() {
    std::cout << std::format("Enter a string (max {} characters): ", this->maxSize - 1);
    std::cin.getline(this->data, this->maxSize); // read a line of input, capped at maxSize
}

StringHolder::~StringHolder() {}

/// @brief Reverses the string in data in place.
/// Uses two pointers walking inward from each end, stopping at the middle.
/// Empty or single-character strings are left unchanged.
void StringHolder::reverse() {
    int middleIndex = (this->maxSize - 1) / 2;
    int leftPointer = 0;
    int rightPointer = this->maxSize - 2; // last char before null terminator
    /* 
    prithoo: So this is how arrays store data in continuous memeory:
    
    | index | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
    | data  | a | b | c | d | e | f |\0 |

    leftPointer starts at index 0 (pointing to 'a') and rightPointer starts at index 5 (pointing to 'f').
    They swap 'a' and 'f', then leftPointer moves to index 1 (pointing to 'b') and rightPointer moves to index 4 (pointing to 'e').
    They swap 'b' and 'e', then leftPointer moves to index 2 (pointing to 'c') and rightPointer moves to index 3 (pointing to 'd').
    They swap 'c' and 'd', then leftPointer moves to index 3 and rightPointer moves to index 2, at which point leftPointer >= middleIndex,
    so the loop breaks and the string is fully reversed to "fedcba".
    */
    char temp;
    while (leftPointer < rightPointer) {
        if (leftPointer >= middleIndex) {
            break;
        }
        temp = this->data[leftPointer];
        this->data[leftPointer] = this->data[rightPointer];
        this->data[rightPointer] = temp;
        leftPointer++;
        rightPointer--;
    }
}

void StringHolder::showString() {
    std::cout << "\n";
    std::cout << std::format("String: {}", this->data);
    std::cout << "\n";
}
