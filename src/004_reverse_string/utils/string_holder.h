#ifndef STRING_HOLDER_H
#define STRING_HOLDER_H

#include <cstddef>

class StringHolder {
    private:
        static constexpr size_t maxSize = 26; // last char reserved for null terminator (\0); max string length is 25
        char data[maxSize];

    public:
        StringHolder();
        ~StringHolder();
        void reverse();
        void showString();
};

#endif // STRING_HOLDER_H
