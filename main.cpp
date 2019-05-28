#include <iostream>
#include <cstdarg>

//Include header
#include <leschoix.hpp>

using namespace std;

//try output with parameters -a=123 -p=9999 --values=1 2 3 4 5 --flowers=lillie dandelion tulip

int main(int argc, char **argv)
{
    //Create instance of LesChoix
    Y::LesChoix parser(argc, argv);

    //create parameters that we want to parse
    uint16_t port;
    string user;
    vector<int> vec;
    vector<string> flowers;
    int aliased;
    bool flag=false;

    //then just get it.
    //dont forget to provide default values if you dont want program to throw

    /* get array of strings */
    flowers=parser["flowers"].GetArr<string>({""});

    /* find element of any of three */
    aliased=parser.find(3, "aliased", "a", "ultravalue").Get<int>(0);

    /* get array of ints. throws if not found */
    vec=parser["values"].GetArr<int>({-10, -20});

    /* get string */
    user=parser["username"].Get<string>("Dmitry");

    /* get uint16_t. */
    port=parser['p'].Get<uint16_t>(0);

    /* check flag. nothrow anytime */
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
