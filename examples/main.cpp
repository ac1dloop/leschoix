/**
  @example How to use this
  */

#include <iostream>
#include "leschoix.hpp"

using namespace std;

//define static member and how to parse
vector<Y::lesopt> Y::LesChoix::values{
    //short name    long name       default value
    {'p',           "port",         "", true},
    {0,             "array",            ""},
    {'v',           "value",        "0.0322"},
    {0,             "name",         "", true}
};

int main(int argc, char **argv)
{
    try {
        uint16_t port;
        double value;
        vector<int> petite_array;
        string name;

        //classic
        Y::LesChoix lesparse(argc, argv);

        //use templated getArg to get arithmetic value
        port=lesparse['p'].getArg<uint16_t>();
        cout << "port: " << port << "\n";

        value=lesparse["value"].getArg<double>();
        cout << "value: " << value << "\n";

        //use non-templated getArg to get string value
        name=lesparse["name"].getArg();
        cout << "name: " << name << "\n";

        petite_array=lesparse["array"].getArgs<int>();
        cout << "array: ";
        for (auto x: petite_array)
            cout << x << " ";
        cout << endl;
    } catch (std::exception& e){
        cout << e.what() << "\n";
    }

    return 0;
}
