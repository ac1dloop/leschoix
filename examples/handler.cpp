/**
  @example With handler
  */

#include <leschoix.hpp>
#include <iostream>
#include <functional>

using namespace std;

//define static member and how to parse
vector<Y::lesopt> Y::LesChoix::values{
    //short name    long name       default value
//zero if no name
    {'p',           "port",         "9999"},
    {0,             "array",            ""},
    {'v',           "value",        "0.0322"},
    {0,             "name",         "Vasya"}
};

void test_handler(string opt, vector<string> args)
{
    if (opt=="p"||opt=="port")
        cout << "port is " << args.at(0) << endl;

    if (opt=="array"){
        cout << "array" << endl;
        for (auto x: args)
            cout << x << " ";
    }
}

auto lambda_handler = [](string opt, vector<string> args){
    cout << "opt: " << opt;

    if (opt=="p"||opt=="port")
        cout << "port is " << args.at(0) << endl;

    if (opt=="array"){
        cout << "array" << endl;
        for (auto x: args)
            cout << x << " ";
    }
};

int main(int argc, char *argv[])
{
    Y::LesChoix parser(argc, argv, test_handler);

    return 0;
}
