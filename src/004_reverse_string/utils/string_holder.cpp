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
