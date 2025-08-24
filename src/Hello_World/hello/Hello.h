#ifndef HELLO_H
#define HELLO_H

#include <string>

class Hello {
    private:
        std::string name;
    public:
        Hello();
        Hello(const std::string& name);

        void say_hello(void);
};

#endif 