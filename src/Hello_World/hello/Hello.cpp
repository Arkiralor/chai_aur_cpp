#include <iostream>
#include <algorithm>
#include "Hello.h"
#include "../utils/str_utils.h"

Hello::Hello(){
    this->name = "World";
}

Hello::Hello(const std::string& name){
    if (!name.empty()){
        std::string clean_name = name;
        // clean_name = trim(clean_name);
        this->name = toTitleCase(trim(clean_name));
    } else {
        this->name = "World";
    }
}

void Hello::say_hello(void){
    std::cout<<"Hello, "<<this->name<<".\n";
}
