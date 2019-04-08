#include <iostream>
#include "leschoix.hpp"

using namespace std;

void testhandler(string opt, vector<string> args){
    cout << "opt: " << opt << endl;

    cout << "args: ";
    for (auto x: args){
        cout << x << " ";
    }
    cout << endl;
}

std::map<std::string, std::function<void()>> Y::LesChoix::special_handlers{
{"help", [](){
    cout << "Default help message" << endl;
}},
                                             };

int main(int argc, char **argv)
{
    auto handle=[](string opt, vector<string> args)->void{
        if (opt=="port"){
            cout << "yes it is port " << args.at(0) << endl;
        }
    };

    Y::LesChoix choix2(argc, argv);

    cout << choix2["port"].get<uint32_t>();

//    cout << typeid(uint8_t).name() << "\n";
//    cout << typeid(uint16_t).name() << "\n";
//    cout << typeid(uint32_t).name() << "\n";
//    cout << typeid(uint64_t).name() << "\n";
//    cout << typeid(unsigned long long).name() << "\n";
//    cout << typeid(int8_t).name() << "\n";
//    cout << typeid(int16_t).name() << "\n";
//    cout << typeid(int32_t).name() << "\n";
//    cout << typeid(long).name() << "\n";
//    cout << typeid(long long).name() << "\n";
//    cout << typeid(double).name() << "\n";
//    cout << typeid(long double).name() << "\n";
//    cout << typeid(float).name() << "\n";
//    cout << typeid(char).name() << "\n";

    return 0;
}
