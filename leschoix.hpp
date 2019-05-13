#ifndef LESCHOIX_HPP
#define LESCHOIX_HPP

#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

#include <iostream>

namespace Y {

using namespace std;

struct Not_found: std::exception {
    virtual const char * const what() {
        return "Fuck you";
    }
};

struct lesopt {

    lesopt(const string& name):name(name),value({""}){}

    lesopt(const string& name, const string& value):name(name),value({value}){}

    template<typename T>
    T Get(){
        return T{};
    }

    template<typename T>
    vector<T> GetArr(){
        return vector<T>{};
    }

    string name;
    vector<string> value;
};

/* Добавить алиасы */
/* Добавить хранение множества значений */

template<>
string lesopt::Get()
{
    return value.back();
}

template<>
int lesopt::Get()
{
    return stoi(value.back());
}

template<>
uint16_t lesopt::Get()
{
    return static_cast<uint16_t>(stol(value.back()));
}

template<>
double lesopt::Get()
{
    return stod(value.back());
}

template<>
long double lesopt::Get()
{
    return stold(value.back());
}

template<>
unsigned long int lesopt::Get()
{
    return static_cast<uint32_t>(stoul(value.back()));
}

template<>
unsigned long long int lesopt::Get()
{
    return stoull(value.back());
}

template<>
float lesopt::Get()
{
    return stof(value.back());
}

template<>
vector<string> lesopt::GetArr()
{
    return value;
}

template<>
vector<int> lesopt::GetArr()
{
    vector<int> res;

    for (auto x: value)
        res.push_back(stoi(x));

    return res;
}

template<>
vector<uint16_t> lesopt::GetArr()
{
    vector<uint16_t> res;

    for (auto x: value)
        res.push_back(stol(x));

    return res;
}

template<>
vector<double> lesopt::GetArr()
{
    vector<double> res;

    for (auto x: value)
        res.push_back(stod(x));

    return res;
}

template<>
vector<long double> lesopt::GetArr()
{
    vector<long double> res;

    for (auto x: value)
        res.push_back(stold(x));

    return res;
}

template<>
vector<unsigned long int> lesopt::GetArr()
{
    vector<unsigned long int> res;

    for (auto x: value)
        res.push_back(stoul(x));

    return res;
}

template<>
vector<unsigned long long int> lesopt::GetArr()
{
    vector<unsigned long long int> res;

    for (auto x: value)
        res.push_back(stoull(x));

    return res;
}

template<>
vector<float> lesopt::GetArr()
{
    vector<float> res;

    for (auto x: value)
        res.push_back(stof(x));

    return res;
}

struct LesChoix {

    LesChoix(int argc, char **argv){
        Parse2(argc, argv);
    }

    lesopt& operator[](const string& name){
        auto it=std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        });

        if (it!=options.end())
            return *it;

        throw Not_found();
    }

    lesopt& operator[](const char short_name){
        string name=string(1, short_name);
        auto it=std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        });

        if (it!=options.end())
            return *it;

        throw Not_found();
    }

    bool Exist(const string& name){
        return std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        })!=options.end();
    }

    bool Exist(const char short_name){
        string name=string(1, short_name);
        return std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        })!=options.end();
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

    void Parse2(int argc, char **argv){
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

            options.back().value.push_back(value);
        }
    }

    vector<lesopt> options;
};

} //test YY namespace

#endif // LESCHOIX_HPP
