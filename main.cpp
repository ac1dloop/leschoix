#include <iostream>
#include <cstdarg>
#include <iterator>

#include <leschoix.hpp>

using namespace std;

static const std::string helpStr=R"(
        This program says hello to you
        to display this message invoke with --help argument

        ver 1.0
                                 )";

int main(int argc, char **argv)
{
    //Create instance of LesChoix
    Y::LesChoix parser(argc, argv);

    //no arguments passed
    if (parser.size() == 0)
        return 0;

    //version requested
    if (parser['v'] || parser["version"]){
        cout << helpStr << endl;

        return 0;
    }

    //we can check if option exists with empty()
    if (!parser['p'].empty()){
        auto port = parser['p'].Get<uint16_t>();

        cout << port << endl;

        return 0;
    }

    //same for long options
    if (!parser["port"].empty()){
        auto port = parser["port"].Get<uint16_t>();

        cout << port << endl;

        return 0;
    }

    return -1;
}
