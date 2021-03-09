/**
  @file leschoix.hpp
  @author ac1dloop

  This file contains classes:

  lesopt - container for option
  LesChoix - parser that contains lesopts

  template specializations for lesopt.Get<T>()

  support functions

*/

#ifndef LESCHOIX_HPP
#define LESCHOIX_HPP

#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdarg>
#include <array>

namespace Y {

/**
  when parsing occurs we check the boolean value if it is true with help of this vector
  everything other is false
  if you want to customize what is true in textual representation
  fill this predefined vector with required values
*/
static std::vector<std::string> booleanTrue{
    {"true"},
    {"yes"},
    {"y"}
};

/**
 * @brief The lesopt struct
 * @class lesopt
 * struct that holds option name and it's value(s)
 */
struct lesopt {

    /**
     * @brief lesopt
     * @param name - name of option that is used in search functions
     * @example ./program --flag - will create lesopt struct with name "flag" and no containing value
     *
     * basic constructor with no values
     * if you dont specify value for argument this constructor is used
     */
    lesopt(const std::string& name):name(name){}

    /**
     * @brief lesopt
     * @param name - name of option that is used in search functions
     * @param value - value of option
     * @example ./program --flag=100 - will create lesopt struct with name "flag" and value "100"
     * @example ./program --flag=1,2,3 - will create lesopt struct with name "flag" and value "1,2,3" value can then be retrieved as an array with Get<T>()
     *
     * cosntructor with values
     */
    lesopt(const std::string& name, const std::string& value):name(name),values({value}){}

    /**
     * @brief Get
     * @retval T returns default value for T
     *
     * since Get<T>() specified for all fundamental types and also vectors
     * this only used when we try to Get type not supported by LesChoix
     */
    template<typename T>
    T Get(){
        return T();
    }

    /**
     * @brief Get
     * @param def - value to return if values array is empty
     * @retval T returns default value specified
     */
    template<typename T>
    T Get(T def){
        if (values.empty() || values.at(0).empty())
            return def;

        return this->Get<T>();
    }

    /**
     *
     */
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

    /**
     * @brief operator bool
     * @retval true if flag exists
     *
     * @example ./program --flag -> parser["flag"] returns true
     * @example ./program -> parser["flag"] returns false
     */
    operator bool(){
        return !name.empty();
    }

    /**
     * @brief empty
     * @return false if lesopt contains any value
     */
    bool empty(){
        return values.empty()?false:values.at(0).empty();
    }

    /* WTF is this? is this even working? */
    template<typename T>
    operator T(){
        return this->Get<T>();
    }

    std::string name;///< name of option
    std::vector<std::string> values;///< value(s) option holds
};

/**
 * @brief Get<bool>()
 *
 * template specialization for bool type
 */
template<>
inline bool lesopt::Get(){
    /* in case user uses Get<bool> by mistake not to get value but to check if argument provided */
    if (values.empty())
        return this->operator bool();

    /* legit since bool is not vector<bool> */
    auto s = values.at(0);

    /* we can add uppercase 'true' text representations to booleanTrue vecor or convert string to lowercase */
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);

    for (const auto& x: booleanTrue){
        if (s == x)
            return true;
    }

    return false;
}

/**
 * @brief Get<std::string>()
 * @return value as string
 * template specialization for std::string type
 */
template<>
inline std::string lesopt::Get(){
    return values.back();
}

/**
 * @brief Get<unsigned char>()
 * @return value as unsigned char
 * template specialization for unsigned char type
 */
template<>
inline unsigned char lesopt::Get(){
    return static_cast<unsigned char>(values.back().at(0));
}

/**
 * @brief Get<char>()
 * @return value as char
 * template specialization for char type
 */
template<>
inline char lesopt::Get(){
    return static_cast<char>(values.back().at(0));
}

/**
 * @brief Get<unsigned short>()
 * @return value as unsigned short
 * template specialization for unsigned short type
 */
template<>
inline unsigned short lesopt::Get(){
    return static_cast<unsigned short>(std::stoul(values.back()));
}

/**
 * @brief Get<short>()
 * @return value as short
 * template specialization for short type
 */
template<>
inline short lesopt::Get(){
    return static_cast<short>(std::stoi(values.back()));
}

/**
 * @brief Get<unsigned int>()
 * @return value as unsigned int
 * template specialization for unsigned int type
 */
template<>
inline unsigned int lesopt::Get(){
    return static_cast<unsigned int>(std::stoul(values.back()));
}

/**
 * @brief Get<int>()
 * @return value as int
 * template specialization for int type
 */
template<>
inline int lesopt::Get(){
    return std::stoi(values.back());
}

/**
 * @brief Get<unsigned long int>()
 * @return value as unsigned long int
 * template specialization for unsigned long int type
 */
template<>
inline unsigned long int lesopt::Get(){
    return static_cast<unsigned long int>(std::stoul(values.back()));
}

/**
 * @brief Get<long int>()
 * @return value as long int
 * template specialization for long int type
 */
template<>
inline long int lesopt::Get(){
    return static_cast<long int>(std::stol(values.back()));
}

/**
 * @brief Get<unsigned long long int>()
 * @return value as unsigned long long int
 * template specialization for unsigned long long int type
 */
template<>
inline unsigned long long int lesopt::Get(){
    return static_cast<unsigned long long int>(std::stoull(values.back()));
}

/**
 * @brief Get<long long int>()
 * @return value as long long int
 * template specialization for long long int type
 */
template<>
inline long long int lesopt::Get(){
    return static_cast<long long int>(std::stoll(values.back()));
}

/**
 * @brief Get<double>()
 * @return value as double
 * template specialization for double type
 */
template<>
inline double lesopt::Get(){
    return std::stod(values.back());
}

/**
 * @brief Get<long double>()
 * @return value as long double
 * template specialization for long double type
 */
template<>
inline long double lesopt::Get(){
    return std::stold(values.back());
}

/**
 * @brief Get<float>()
 * @return value as float
 * template specialization for float type
 */
template<>
inline float lesopt::Get(){
    return std::stof(values.back());
}

/**
 * @brief GetArr<std::vector<std::string>>()
 * @return value as vector of std::strings
 * template specialization for std::vector<std::string> type
 */
template<>
inline std::vector<std::string> lesopt::GetArr(){
    return values;
}

/**
 * @brief GetArr<char>
 * @return values as array of chars
 * template specialization for std::vector<char> type
 */
template<>
inline std::vector<char> lesopt::GetArr(){
    std::vector<char> res;

    for (auto x: values)
        res.push_back(static_cast<char>(std::stoi(x)));

    return res;
}

/**
 * @brief GetArr<unsigned char>
 * @return values as array of unsigned chars
 * template specialization for std::vector<unsigned char> type
 */
template<>
inline std::vector<unsigned char> lesopt::GetArr(){
    std::vector<unsigned char> res;

    for (auto x: values)
        res.push_back(static_cast<unsigned char>(std::stoul(x)));

    return res;
}

/**
 * @brief GetArr<short>
 * @return values as array of shorts
 * template specialization for std::vector<short> type
 */
template<>
inline std::vector<short> lesopt::GetArr(){
    std::vector<short> res;

    for (auto x: values)
        res.push_back(static_cast<short>(std::stoi(x)));

    return res;
}

/**
 * @brief GetArr<unsigned short>
 * @return values as array of unsigned shorts
 * template specialization for std::vector<unsigned short> type
 */
template<>
inline std::vector<unsigned short> lesopt::GetArr(){
    std::vector<unsigned short> res;

    for (auto x: values)
        res.push_back(static_cast<unsigned short>(std::stoul(x)));

    return res;
}

/**
 * @brief GetArr<int>
 * @return values as array of ints
 * template specialization for std::vector<int> type
 */
template<>
inline std::vector<int> lesopt::GetArr(){
    std::vector<int> res;

    for (auto x: values)
        res.push_back(std::stoi(x));

    return res;
}

/**
 * @brief GetArr<unsigned int>
 * @return values as array of unsigned ints
 * template specialization for std::vector<unsigned int> type
 */
template<>
inline std::vector<unsigned int> lesopt::GetArr(){
    std::vector<unsigned int> res;

    for (auto x: values)
        res.push_back(std::stoul(x));

    return res;
}

/**
 * @brief GetArr<long int>
 * @return values as array of long ints
 * template specialization for std::vector<long int> type
 */
template<>
inline std::vector<long int> lesopt::GetArr(){
    std::vector<long int> res;

    for (auto x: values)
        res.push_back(std::stol(x));

    return res;
}

/**
 * @brief GetArr<unsigned long int>
 * @return values as array of unsigned long ints
 * template specialization for std::vector<unsigned long int> type
 */
template<>
inline std::vector<unsigned long int> lesopt::GetArr(){
    std::vector<unsigned long int> res;

    for (auto x: values)
        res.push_back(std::stoul(x));

    return res;
}

/**
 * @brief GetArr<unsigned long long int>
 * @return values as array of unsigned long long ints
 * template specialization for std::vector<unsigned long long int> type
 */
template<>
inline std::vector<unsigned long long int> lesopt::GetArr(){
    std::vector<unsigned long long int> res;

    for (auto x: values)
        res.push_back(std::stoull(x));

    return res;
}

/**
 * @brief GetArr<long long int>
 * @return values as array of long long ints
 * template specialization for std::vector<long long int> type
 */
template<>
inline std::vector<long long int> lesopt::GetArr(){
    std::vector<long long int> res;

    for (auto x: values)
        res.push_back(std::stoll(x));

    return res;
}

/**
 * @brief GetArr<double>
 * @return values as array of doubles
 * template specialization for std::vector<double> type
 */
template<>
inline std::vector<double> lesopt::GetArr()
{
    std::vector<double> res;

    for (auto x: values)
        res.push_back(std::stod(x));

    return res;
}

/**
 * @brief GetArr<long double>
 * @return values as array of long doubles
 * template specialization for std::vector<long double> type
 */
template<>
inline std::vector<long double> lesopt::GetArr()
{
    std::vector<long double> res;

    for (auto x: values)
        res.push_back(std::stold(x));

    return res;
}

/**
 * @brief GetArr<float>
 * @return values as array of floats
 * template specialization for std::vector<float> type
 */
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
 * @class LesChoix
 * Class that provides interface to parse and to access parsed values
 */
struct LesChoix {
    /**
     * @brief LesChoix
     * @param argc - arguments count
     * @param argv - array of char* arguments
     *
     * Basic constructor that automatically parses
     */
    LesChoix(int argc, char **argv){
        Parse3(argc, argv);
    }

    /**
     * @brief operator []
     * @param name - name of option
     * @return lesopt with name equal to name
     *
     * tries to find an option with this name
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

    size_t size(){ return options.size(); }

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

} //Y namespace

#endif // LESCHOIX_HPP
