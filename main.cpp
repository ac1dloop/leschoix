#include <iostream>
#include <leschoix.hpp>

using namespace std;

int main(int argc, char **argv)
{
    Y::LesChoix parser(argc, argv);

    uint16_t port=0;
    string user="";
    vector<int> vec{0};

    if (parser.Exist('p'))
        port=parser['p'].Get<uint16_t>();
    if (parser.Exist("username"))
        user=parser["username"].Get<string>();
    if (parser.Exist("values"))
        vec=parser["values"].GetArr<int>();

    cout << "port: " << port << endl;
    cout << "user: " << user << endl;
    cout << "array: ";
    for (auto x: vec)
        cout << x << " ";
    cout << endl;

	return 0;
}
