#include <iostream>
#include <string>
#include "hello/Hello.h"


int main(){
    std::string name;
    Hello obj;

    std::cout << "Please enter your name.\n";
    std::cin >> name;
    obj = Hello(name);
    obj.say_hello();
    return 0;
}
