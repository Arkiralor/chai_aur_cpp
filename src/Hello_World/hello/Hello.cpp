#include <iostream>
#include "Hello.h"

Hello::Hello(){
    this->name = "World";
}

Hello::Hello(const std::string& name){
    if (!name.empty()){
        this->name = name;
    } else {
        this->name = "World";
    }
}

void Hello::say_hello(void){
    std::cout<<"Hello, "<<this->name<<".\n";
}
