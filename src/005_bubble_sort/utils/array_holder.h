#ifndef ARRAY_HOLDER_H
#define ARRAY_HOLDER_H

#include <cstddef>

class ArrayHolder {
    private:
        static constexpr size_t maxSize = 26; // max capacity; actual element count tracked by `count`
        int data[maxSize];
        size_t count = 0;

    public:
        ArrayHolder();
        ~ArrayHolder();
        void bubbleSort();
        void showArray();
        void orchestrate();
};

#endif // Array_HOLDER_H
