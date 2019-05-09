#include <iostream>
#include <leschoix2.hpp>

using namespace std;

int main(int argc, char **argv)
{
    YY::LesChoix parser(argc, argv);

    uint16_t port;
    string user;

    port=parser['p'].Get<uint16_t>();
    user=parser["username"].Get<string>();

    cout << "port: " << port << endl;
    cout << "user: " << user << endl;

	return 0;
}
