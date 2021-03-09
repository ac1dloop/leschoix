#include <iostream>
#include <cstdarg>
#include <iterator>

#include <leschoix.hpp>

using namespace std;

static const std::string helpStr=R"(
        This program says hello to you

        ver 1.0
                                 )";

//TODO add tests for each fundamental type
//TODO iterators
int main(int argc, char **argv)
{
    //Create instance of LesChoix
    Y::LesChoix parser(argc, argv);

    cout << "size of LesChoix = " << sizeof(Y::LesChoix) << endl;
    cout << "size of lesopt = " << sizeof(Y::lesopt) << endl;

    //no arguments passed
    if (parser.size() == 0){
        cout << "no arguments passed" << endl;

        return 0;
    }

    //version requested
    if (parser['v'] || parser["version"]){
        cout << helpStr << endl;

        return 0;
    }

    if (parser['f']){
//        cout << "short flag: " << parser['f'].Get<char>('X') << endl;
        cout << parser['f'].Get<char>('X') << endl;

        return 0;
    }

    if (parser["flag"]){
        cout << "long flag: " << parser["flag"].Get<char>() << endl;

        return 0;
    }

    if (parser['p']){
        auto port = parser['p'].Get<uint16_t>(8080);

        cout << "short port: " << port << endl;

        return 0;
    }

    if (parser["port"]){
        auto port = parser["port"].Get<uint16_t>(1234);

        cout << "long port: " << port << endl;

        return 0;
    }

    return -1;
}
