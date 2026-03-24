#include "array_holder.h"

#include <format>
#include <iostream>
#include <string>

ArrayHolder::ArrayHolder() {
    std::cout << std::format("How many numbers? (max {}): ", this->maxSize - 1);
    std::cin >> this->count;
    if (this->count >= this->maxSize) {
        this->count = this->maxSize - 1;
    }
    std::cout << "Enter " << this->count << " numbers:\n";
    for (size_t i = 0; i < this->count; i++) {
        std::cin >> this->data[i];
    }
    std::cout << "\n";
    std::cout << "The input array is: ";
    this->showArray();
}

ArrayHolder::~ArrayHolder() {}

void ArrayHolder::bubbleSort() {
    int temp;
    for (size_t i = 0; i < this->count - 1; i++) {
        for (size_t j = 0; j < this->count - i - 1; j++) {
            if (this->data[j] > this->data[j + 1]) {
                temp = this->data[j];
                this->data[j] = this->data[j + 1];
                this->data[j + 1] = temp;
            }
        }
    }
}

void ArrayHolder::showArray() {
    std::cout << "\n";
    std::string formatted_array = "[";
    for (size_t i = 0; i < this->count; i++) {
        formatted_array += std::format("{}", this->data[i]);
        if (i < this->count - 1) formatted_array += ", ";
    }
    formatted_array += "]";
    std::cout << std::format("Array: {}\n", formatted_array);
}

void ArrayHolder::orchestrate() {
    std::cout << "\n Now proceeding to sort the array using bubble sort...";
    this->bubbleSort();
    std::cout << "\n The sorted array is: ";
    this->showArray();
}