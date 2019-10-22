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

    if (parser["help"] || parser['h']){
        cout << helpStr;
        return 0;
    }

//    bool daemon=parser['d'].Get<bool>();

//    if (daemon)
//        clog << "pid=0";
//    else cout << "bonjour world";

//    //petite types may be implicitly converted
//    string ip_addr=parser["ip"];
//    uint16_t port=parser["port"];

//    //vectors of things
    auto flowers=parser["flowers"].GetArr<string>();
//    auto intergers69=parser["values"].GetArr<int>();

//    cout << "addr: " << ip_addr << " port: " << port << '\n';

    std::copy(flowers.begin(), flowers.end(), std::ostream_iterator<string>(cout, " is nice "));


	return 0;
}
