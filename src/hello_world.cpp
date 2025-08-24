#include <iostream>

using namespace std;

class Hello{
    private:
        string name;

    public:
        Hello(void){
            this->name = "World";
        }

        Hello(string name){
            if (name != ""){
                this->name = name;
            }
            else{
                this->name = "World";
            }
        }
        
        void say_hello();
};

int main(){
    string name;
    Hello obj;

    cout << "Please enter your name.\n";
    cin >> name;
    obj = Hello(name);
    obj.say_hello();
    return 0;
}

void Hello::say_hello(void){
    cout << "Hello, " << this->name << ".\n";
}
