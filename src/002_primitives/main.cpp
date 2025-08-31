#include <iostream>
#include "utils/str_utils.h"

int main(){
    // int teaLeafCount = 50;
    // float waterTemperature = 98;
    // double rateOfOneCupTea = 127.60;
    // char teaGrade = 'A';
    // bool teaIsReady = true;

    int teaLeafCount;
    float waterTemperature;
    double rateOfOneCupTea;
    char teaGrade;
    bool teaIsReady;

    std::cout<<"Enter Tea Leaf Count: ";
    std::cin>>teaLeafCount; // "\n" to consume any leading whitespace characters

    std::cout<<"Enter Water Temperature: ";
    std::cin>>waterTemperature;

    std::cout<<"Enter Rate of One Cup Tea: ";
    std::cin>>rateOfOneCupTea;

    std::cout<<"Enter Tea Grade: ";
    std::cin>>teaGrade;
    std::string teaGradeStr = std::string(1, teaGrade);
    teaGradeStr = trim(teaGradeStr);
    teaGrade = teaGradeStr.empty() ? ' ' : teaGradeStr[0];
    teaGrade = std::toupper(teaGrade);

    std::cout<<"Is Tea Ready (1 for true, 0 for false): ";
    std::cin>>teaIsReady;
    if (teaIsReady == 0){
        teaIsReady = false;
    } else {
        teaIsReady = true;
    }

    std::cout<<"Tea Leaf Count: "<<teaLeafCount<<std::endl;
    std::cout<<"Water Temperature: "<<waterTemperature<<std::endl;
    std::cout<<"Rate of One Cup Tea: "<<rateOfOneCupTea<<std::endl;
    std::cout<<"Tea Grade: "<<teaGrade<<std::endl;
    std::cout<<"Is Tea Ready: "<<teaIsReady<<std::endl;
    return 0;
}