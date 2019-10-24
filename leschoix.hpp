#ifndef LESCHOIX_HPP
#define LESCHOIX_HPP

#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdarg>
#include <array>

#include <iostream>

namespace Y {

static std::vector<std::string> booleanTrue{
    {"true"},
    {"yes"},
    {"y"}
};

/**
 * @brief The lesopt struct
 * struct that holds option name and it's value(s)
 */
struct lesopt {

    lesopt(const std::string& name):name(name){}

    lesopt(const std::string& name, const std::string& value):name(name),values({value}){}

    template<typename T>
    T Get(){
        return T();
    }

    template<typename T>
    T Get(T def){
        if (values.at(0).empty())
            return def;

        return this->Get<T>();
    }

    template<typename T>
    std::vector<T> GetArr(){
        return std::vector<T>{};
    }

    template<typename T>
    std::vector<T> GetArr(std::vector<T> def){
        if (values.empty())
            return def;

        return this->GetArr<T>();
    }

    /* если есть хотя бы одно значение то возвращаем true если оно не пустое */
    operator bool(){
        return !name.empty();
    }

    bool empty(){
        return values.empty()?true:values[0].empty();
    }

    template<typename T>
    operator T(){
        return this->Get<T>();
    }

    std::string name;
    std::vector<std::string> values;
};

template<>
inline bool lesopt::Get()
{
    if (!values.empty()){
        auto s=values.at(0);

        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        if (std::find_if(booleanTrue.begin(), booleanTrue.end(), [&s](std::string op){
                         return s.find(op.c_str())!=std::string::npos;
        })!=booleanTrue.end()){
            return true;
        } else return false;
    }

    std::cout << "returning name\n";

    return !name.empty();
}

template<>
inline std::string lesopt::Get()
{
    return values.back();
}

template<>
inline unsigned char lesopt::Get()
{
    return static_cast<unsigned char>(std::stoul(values.back()));
}

template<>
inline char lesopt::Get()
{
    return static_cast<char>(std::stoi(values.back()));
}

template<>
inline unsigned short lesopt::Get()
{
    return static_cast<unsigned short>(std::stoul(values.back()));
}

template<>
inline short lesopt::Get()
{
    return static_cast<short>(std::stoi(values.back()));
}

template<>
inline int lesopt::Get()
{
    return std::stoi(values.back());
}

template<>
inline unsigned int lesopt::Get()
{
    return static_cast<unsigned int>(std::stoul(values.back()));
}

template<>
inline unsigned long int lesopt::Get()
{
    return static_cast<unsigned long int>(std::stoul(values.back()));
}

template<>
inline long int lesopt::Get()
{
    return static_cast<long int>(std::stol(values.back()));
}

template<>
inline unsigned long long int lesopt::Get()
{
    return static_cast<unsigned long long int>(std::stoull(values.back()));
}

template<>
inline long long int lesopt::Get()
{
    return static_cast<long long int>(std::stoll(values.back()));
}

template<>
inline double lesopt::Get()
{
    return std::stod(values.back());
}

template<>
inline long double lesopt::Get()
{
    return std::stold(values.back());
}

template<>
inline float lesopt::Get()
{
    return std::stof(values.back());
}

template<>
inline std::vector<std::string> lesopt::GetArr()
{
    return values;
}

template<>
inline std::vector<char> lesopt::GetArr()
{
    std::vector<char> res;

    for (auto x: values)
        res.push_back(static_cast<char>(std::stoi(x)));

    return res;
}

template<>
inline std::vector<unsigned char> lesopt::GetArr()
{
    std::vector<unsigned char> res;

    for (auto x: values)
        res.push_back(static_cast<unsigned char>(std::stoul(x)));

    return res;
}

template<>
inline std::vector<short> lesopt::GetArr()
{
    std::vector<short> res;

    for (auto x: values)
        res.push_back(static_cast<short>(std::stoi(x)));

    return res;
}

template<>
inline std::vector<unsigned short> lesopt::GetArr()
{
    std::vector<unsigned short> res;

    for (auto x: values)
        res.push_back(static_cast<unsigned short>(std::stoul(x)));

    return res;
}

template<>
inline std::vector<int> lesopt::GetArr()
{
    std::vector<int> res;

    for (auto x: values)
        res.push_back(std::stoi(x));

    return res;
}

template<>
inline std::vector<unsigned int> lesopt::GetArr()
{
    std::vector<unsigned int> res;

    for (auto x: values)
        res.push_back(std::stoul(x));

    return res;
}

template<>
inline std::vector<long int> lesopt::GetArr()
{
    std::vector<long int> res;

    for (auto x: values)
        res.push_back(std::stol(x));

    return res;
}

template<>
inline std::vector<unsigned long int> lesopt::GetArr()
{
    std::vector<unsigned long int> res;

    for (auto x: values)
        res.push_back(std::stoul(x));

    return res;
}

template<>
inline std::vector<long long int> lesopt::GetArr()
{
    std::vector<long long int> res;

    for (auto x: values)
        res.push_back(std::stoll(x));

    return res;
}

template<>
inline std::vector<unsigned long long int> lesopt::GetArr()
{
    std::vector<unsigned long long int> res;

    for (auto x: values)
        res.push_back(std::stoull(x));

    return res;
}

template<>
inline std::vector<double> lesopt::GetArr()
{
    std::vector<double> res;

    for (auto x: values)
        res.push_back(std::stod(x));

    return res;
}

template<>
inline std::vector<long double> lesopt::GetArr()
{
    std::vector<long double> res;

    for (auto x: values)
        res.push_back(std::stold(x));

    return res;
}

template<>
inline std::vector<float> lesopt::GetArr()
{
    std::vector<float> res;

    for (auto x: values)
        res.push_back(std::stof(x));

    return res;
}

/**
 * @brief The LesChoix struct
 * Class that provides interface to parse and access values
 */
struct LesChoix {
    /**
     * @brief LesChoix
     * @param argc
     * @param argv
     *
     * Constructor
     */
    LesChoix(int argc, char **argv){
        Parse3(argc, argv);
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

        return empty;
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

private:
    /**
     * @brief find
     * @param name
     * @return std::pair<bool, lesopt&>
     * If option exists first is true so second is acessible
     */
    std::pair<bool, lesopt&> find(const std::string& name){
        auto it=std::find_if(options.begin(), options.end(), [&name](lesopt& op){
            return op.name==name;
        });

        if (it!=options.end())
            return {true, *it};

        return {false, *it};
    }

    /**
     * @brief Parse3
     * @param argc
     * @param argv
     * Same as Parse2 but works better
     */
    void Parse3(int argc, char **argv){
        std::string name{""};
        std::string value{""};
        std::string line{""};
        for (int i=1;i<argc;++i){

            line=std::string(argv[i]);

            //if it is an option
            if (line.at(0)=='-'&& (::isalpha(line.at(1)) || line.at(1)=='-') ){
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
                } else {
                    options.push_back({name});
                    continue;
                }
            }

            value=std::string(argv[i], strlen(argv[i]));

            options.back().values.push_back(value);
        }
    }

    lesopt empty{"", ""};
    std::vector<lesopt> options;
};

} //test Y namespace

#endif // LESCHOIX_HPP
