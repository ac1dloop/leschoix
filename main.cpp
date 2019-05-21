#include <iostream>
#include <cstdarg>

//Include header
#include <leschoix.hpp>

using namespace std;

//output with parameters -a=123 -p=9999 --values=1 2 3 4 5 --flowers=lillie dandelion tulip

int main(int argc, char **argv)
{
    //Create instance of LesChoix
    Y::LesChoix parser(argc, argv);

    //parameters that we want to parse
    uint16_t port=0;
    string user="";
    vector<int> vec{0};
    vector<string> flowers;
    int aliased=0;
    bool flag=false;

    //before accessing option it is better to check for existence
    //code doesn't make any assertions about returning type or containing value
    //if option doesn't exist or value cannot be converted it will result in undefined behaviour
    if (parser['p'])
        port=parser['p'].Get<uint16_t>(123);
    if (parser["username"])
        user=parser["username"].Get<string>();
    if (parser["values"])
        vec=parser["values"].GetArr<int>();
    if (parser.find(3, "aliased", "a", "ultravalue"))
        aliased=parser.find(3, "aliased", "a", "ultravalue").Get<int>();
    if (parser["flowers"])
        flowers=parser["flowers"].GetArr<string>();

    flag=parser['f'].Get<bool>();

    cout << "port: " << port << endl;
    cout << "user: " << user << endl;
    cout << "aliased: " << aliased << endl;

    cout << "array: ";
    for (auto x: vec)
        cout << x << " ";
    cout << endl;

    cout << "flowers: ";
    for (auto x: flowers)
        cout << x << " ";
    cout << endl;

    cout << "flag is " << (flag?"set":"unset") << endl;

	return 0;
}
