#include <iostream>
#include <string>
#include "hello/Hello.h"


int main(){
    std::string name;
    std::cout << "Please enter your name.\n";
    std::getline(std::cin, name);
    Hello obj = Hello(name);
    obj.say_hello();
    return 0;
}
