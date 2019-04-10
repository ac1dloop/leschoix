#include <iostream>
#include "leschoix.hpp"
#include "leschoix_v2.hpp"

using namespace std;

void testhandler(string opt, vector<string> args){
    cout << "opt: " << opt << endl;

    cout << "args: ";
    for (auto x: args){
        cout << x << " ";
    }
    cout << endl;
}

vector<YY::lesopt> YY::LesChoix::values{
{'p', "", "8080"},
{'a', "option", "option"},
};

int main(int argc, char **argv)
{
    auto handle=[](string opt, vector<string> args)->void{
        if (opt=="port"){
            cout << "yes it is port " << args.at(0) << endl;
        }
    };

//    Y::LesChoix choix2(argc, argv);
    YY::LesChoix choix(argc, argv);

//    for (auto x: choix.values){
//        cout << "opt: " << x.opt << " alias: " << x.alias << " values: ";
//        for (auto j: x.strArgs())
//            cout << j << " ";
//        cout << endl;
//    }

    unsigned port=choix['p'].getArg<uint16_t>();
    string option=choix["option"].getArg();

    cout << "port: " << port << endl;
    cout << "option: " << option << endl;

//    cout << choix2["port"].get<uint32_t>();

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
