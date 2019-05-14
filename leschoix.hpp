#ifndef LESCHOIX_HPP
#define LESCHOIX_HPP

#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

#include <iostream>

namespace Y {

struct lesopt {

    lesopt(const std::string& name):name(name),value({""}){}

    lesopt(const std::string& name, const std::string& value):name(name),value({value}){}

    template<typename T>
    T Get(){
        return T{};
    }

    template<typename T>
    std::vector<T> GetArr(){
        return std::vector<T>{};
    }

    operator bool(){
        if (!value.empty())
            return !value[0].empty();

        return !value.empty();
    }

    std::string name;
    std::vector<std::string> value;
};

template<>
std::string lesopt::Get()
{
    return value.back();
}

template<>
int lesopt::Get()
{
    return std::stoi(value.back());
}

template<>
uint16_t lesopt::Get()
{
    return static_cast<uint16_t>(std::stol(value.back()));
}

template<>
double lesopt::Get()
{
    return std::stod(value.back());
}

template<>
long double lesopt::Get()
{
    return std::stold(value.back());
}

template<>
unsigned long int lesopt::Get()
{
    return static_cast<uint32_t>(std::stoul(value.back()));
}

template<>
unsigned long long int lesopt::Get()
{
    return std::stoull(value.back());
}

template<>
float lesopt::Get()
{
    return std::stof(value.back());
}

template<>
std::vector<std::string> lesopt::GetArr()
{
    return value;
}

template<>
std::vector<int> lesopt::GetArr()
{
    std::vector<int> res;

    for (auto x: value)
        res.push_back(std::stoi(x));

    return res;
}

template<>
std::vector<uint16_t> lesopt::GetArr()
{
    std::vector<uint16_t> res;

    for (auto x: value)
        res.push_back(std::stol(x));

    return res;
}

template<>
std::vector<double> lesopt::GetArr()
{
    std::vector<double> res;

    for (auto x: value)
        res.push_back(std::stod(x));

    return res;
}

template<>
std::vector<long double> lesopt::GetArr()
{
    std::vector<long double> res;

    for (auto x: value)
        res.push_back(std::stold(x));

    return res;
}

template<>
std::vector<unsigned long int> lesopt::GetArr()
{
    std::vector<unsigned long int> res;

    for (auto x: value)
        res.push_back(std::stoul(x));

    return res;
}

template<>
std::vector<unsigned long long int> lesopt::GetArr()
{
    std::vector<unsigned long long int> res;

    for (auto x: value)
        res.push_back(std::stoull(x));

    return res;
}

template<>
std::vector<float> lesopt::GetArr()
{
    std::vector<float> res;

    for (auto x: value)
        res.push_back(std::stof(x));

    return res;
}

struct LesChoix {

    LesChoix(int argc, char **argv){
        Parse2(argc, argv);
    }

    /**
     * @brief operator []
     * @param name
     * @return lesopt&
     * tries to find an option with this name
     * if option not parsed adds option name to options array
     * and returns reference to it.
     */
    lesopt& operator[](const std::string& name){
        auto p=this->find(name);

        if (p.first)
            return p.second;

        options.push_back({name});
        return options.back();
    }

    /**
     * @brief operator []
     * @param short_name
     * @return lesopt&
     * same as operator[] for string but for short option names
     */
    lesopt& operator[](const char short_name){
        return this->operator [](std::string(1, short_name));
    }

    /**
     * @brief find
     * @param n - umber of aliases
     * @return lesopt&
     * tries to find an option with any of passed names
     */
    lesopt& find(const int n...){
        va_list args;
        va_start(args, n);

        std::string s;
        char* buf;
        for (int i=n;i!=0;--i){
            buf=va_arg(args, char*);
            s=std::string(buf, strlen(buf));
            auto p=this->find(buf);
            if (p.first)
                return p.second;
        }

        va_end(args);

        return this->operator [](s);
    }

    bool Exist(const std::string& name){
        return std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        })!=options.end();
    }

    bool Exist(const char short_name){
        std::string name=std::string(1, short_name);
        return std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        })!=options.end();
    }

private:
    std::pair<bool, lesopt&> find(const std::string& name){
        auto it=std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        });

        if (it!=options.end())
            return {true, *it};

        return {false, *it};
    }

    /**
     * @brief Parse
     * @param argc - argument count
     * @param argv - pointer to corresponding argument values
     * function doesnt handle arguments with multiple values such as -p=100 200 300
     */
    void Parse(int argc, char **argv){
        std::string name;
        std::string value;
        std::string line;
        for (int i=1;i<argc;++i){

            line=std::string(argv[i], strlen(argv[i]));

			//if it is an option
            if (line.at(0)=='-'){
                if (line.at(1)=='-'){
                    //long option
					name=line.substr(2, line.size()-1);
               } else {
                    //short option
                    name=std::string(1, line.at(1));
                }

                size_t j=line.find('=');

                if (j!=std::string::npos){
//                    cout << "found '=' !\n";
                    value=line.substr(j+1, line.size()-j-1);
                    name=line.substr(line.rfind('-', j)+1, j-line.rfind('-', j)-1);
                    options.push_back({name, value});
                    continue;
                } else continue;
            }

            value=std::string(argv[i], strlen(argv[i]));

            options.push_back({name, value});
        }
    }

    void Parse2(int argc, char **argv){
        std::string name;
        std::string value;
        std::string line;
        for (int i=1;i<argc;++i){

            line=std::string(argv[i], strlen(argv[i]));

            //if it is an option
            if (line.at(0)=='-'){
                if (line.at(1)=='-'){
                    //long option
                    name=line.substr(2, line.size()-1);
               } else {
                    //short option
                    name=std::string(1, line.at(1));
                }

                size_t j=line.find('=');

                if (j!=std::string::npos){
                    value=line.substr(j+1, line.size()-j-1);
                    name=line.substr(line.rfind('-', j)+1, j-line.rfind('-', j)-1);
                    options.push_back({name, value});
                    continue;
                } else continue;
            }

            value=std::string(argv[i], strlen(argv[i]));

            options.back().value.push_back(value);
        }
    }

    std::vector<lesopt> options;
};

} //test Y namespace

#endif // LESCHOIX_HPP
