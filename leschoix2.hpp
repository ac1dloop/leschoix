#ifndef LESCHOIX2_HPP
#define LESCHOIX2_HPP

#include <string>
#include <vector>
#include <cstring>

namespace YY {

using namespace std;

struct lesopt {

    lesopt(const string& name, const string& value):name(name),value(value){}

    string name;
    string value;
};

struct LesChoix {

    LesChoix(int argc, char **argv){
        Parse(argc, argv);
    }

private:
    void Parse(int argc, char **argv){
        string name;
        string value;
        string line;
        for (int i=1;i<argc;++i){

            line=string(argv[i], strlen(argv[i]));

            if (line.at(0)=='-'){
                if (line.at(1)=='-'){
                    //long option
                    name=line.substr(2, line.find('=')-2);
                } else {
                    //short option
                    name=string(1, line.at(1));
                }
            }
        }
    }

    vector<lesopt> options;
};

} //test YY namespace

#endif // LESCHOIX2_HPP
