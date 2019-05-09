#ifndef LESCHOIX2_HPP
#define LESCHOIX2_HPP

#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

#include <iostream>

namespace YY {

using namespace std;

struct lesopt {

    lesopt(const string& name):name(name){}

    lesopt(const string& name, const string& value):name(name),value(value){}

    template<typename T>
    T Get(){
        return T{};
    }

    string name;
    string value;
};

/* Добавить алиасы */
/* Добавить хранение множества значений */
/* сделать темплейты для базовых типов */
/* сделать что-то с возвращением стандартного значения */

template<>
string lesopt::Get()
{
    return value;
}

template<>
int lesopt::Get()
{
    return stoi(value);
}

template<>
uint16_t lesopt::Get()
{
    return static_cast<uint16_t>(stol(value));
}

template<>
double lesopt::Get()
{
    return stod(value);
}

template<>
long double lesopt::Get()
{
    return stold(value);
}

template<>
uint32_t lesopt::Get()
{
    return static_cast<uint32_t>(stoul(value));
}

template<>
unsigned long long int lesopt::Get()
{
    return stoull(value);
}

struct LesChoix {

    LesChoix(int argc, char **argv){
        Parse(argc, argv);
    }

    lesopt& operator[](const string& name){
        auto it=std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        });

        if (it!=options.end())
            return *it;

        options.push_back({name});

        return options.at(options.size()-1);
    }

    lesopt& operator[](const char short_name){
        string name=string(1, short_name);
        auto it=std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        });

        if (it!=options.end())
            return *it;

        options.push_back({name});

        return options.at(options.size()-1);
    }

private:
    void Parse(int argc, char **argv){
        string name;
        string value;
        string line;
        for (int i=1;i<argc;++i){

//            cout << "i: " << i << "  ";

            line=string(argv[i], strlen(argv[i]));

//            cout << line << "\n";

			//if it is an option
            if (line.at(0)=='-'){
                if (line.at(1)=='-'){
                    //long option
//                    cout << "long option: " << name << "\n";
					name=line.substr(2, line.size()-1);
               } else {
                    //short option
                    name=string(1, line.at(1));
//                    cout << "short option: " << name << "\n";
                }

                size_t j=line.find('=');

                if (j!=string::npos){
//                    cout << "found '=' !\n";
                    value=line.substr(j+1, line.size()-j-1);
                    name=line.substr(line.rfind('-', j)+1, j-line.rfind('-', j)-1);
//                    cout << "name: " << name << " value: " << value << "\n";
                    options.push_back({name, value});
                    continue;
                } else continue;
            }

			value=string(argv[i], strlen(argv[i]));

            options.push_back({name, value});
        }
    }

    vector<lesopt> options;
};

} //test YY namespace

#endif // LESCHOIX2_HPP
