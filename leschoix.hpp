#ifndef LESCHOIX_V2_HPP
#define LESCHOIX_V2_HPP

#include <string>
#include <vector>
#include <functional>
#include <algorithm>

#include <iostream>

namespace Y {

class lesopt;

using options=std::vector<Y::lesopt>;

using namespace std;

/**
 * @struct The OptArg struct
 *
 * OptArg stands for options argument
 * This structure holds exactly one argument value
 */

struct OptArg {

    /**
     * @brief OptArg() constructor
     * @param str value to keep
     */
    OptArg(const string& str):data(str){}

    /**
     * @brief actual value
     */
    string data;

    /**
     * @brief get value converted to T
     * @return T - any of arithmetic types
     */
    template <typename T>
    T get(){
        if (is_same<T, uint8_t>::value||is_same<T, uint16_t>::value||is_same<T, uint32_t>::value)
            return stoul(data);
        else if (is_same<T, uint64_t>::value||is_same<T, unsigned long long>::value)
            return stoull(data);
        else if (is_same<T, int8_t>::value||is_same<T, int16_t>::value||is_same<T, int32_t>::value)
            return stoi(data);
        else if (is_same<T, int64_t>::value)
            return stol(data);
        else if (is_same<T, long long>::value)
            return stoll(data);
        else if (is_same<T, double>::value)
            return stod(data);
        else if (is_same<T, long double>::value)
            return stold(data);
        else if (is_same<T, long double>::value)
            return stof(data);
        else if (is_same<T, char>::value)
            return data.at(0);
    }
};

/**
 * @brief The lesopt struct
 *
 *
 */

struct lesopt {

    /**
     * @brief Constructor
     * @param opt - option that we parse ( -p )
     * @param alias - full option name ( --port )
     */
    lesopt(char opt, string alias):opt(opt), alias(alias){
        check_opt(opt);
    }

    /**
     * @brief Constructor with default value
     * @param opt - option that we parse ( -p )
     * @param alias - full oprtion name ( --port )
     * @param default_value - value that will be used if nothing is parsed
     */
    lesopt(char opt, string alias, string default_value):opt(opt), alias(alias), default_value(default_value){
        check_opt(opt);
    }

    lesopt(char opt, string alias, string default_value, bool argRequired):opt(opt), alias(alias),
                                                                                         default_value(default_value),
                                                                                         argRequired(argRequired){

        check_opt(opt);
    }

    /**
     * @brief getOpt
     * @return option name
     */
    string getOpt(){
        if (opt==0)
            return alias;
        else return string(1, opt);
    }

    /**
     * @brief getArg
     * @return first argument from array
     */
    string getArg(){
        if (args.at(0).data.empty())
            throw std::logic_error(string((opt?string(1, opt):alias) + ": Argument is required but not provided"));

        return args.at(0).data;
    }

    /**
     * @brief getArg
     * @return first argument from array converted to T
     */
    template<typename T>
    T getArg(){
        if (args.at(0).data.empty())
            throw std::logic_error(string((opt?string(1, opt):alias) + ": Argument is required but not provided"));

        return args.at(0).get<T>();
    }

    /**
     * @brief strArgs
     * @return array of arguments
     */
    vector<string> strArgs(){
        if (args.empty()||args.at(0).data.empty())
            if (argRequired)
                throw std::logic_error(string((opt?string(1, opt):alias) + ": Argument is required but not provided"));
            else return vector<string>{};

        vector<string> res;

        for (auto x: args)
            res.push_back(x.data);

        return res;
    }

    /**
     * @brief getArgs
     * @return array<T> of arguments. each converted to T
     */
    template<typename T>
    vector<T> getArgs(){
        if (args.empty()||args.at(0).data.empty())
            if (argRequired)
                throw std::logic_error(string((opt?string(1, opt):alias) + ": Argument is required but not provided"));
            else return vector<T>{};

        vector<T> res;

        for (auto x: args)
            res.push_back(x.get<T>());

        return res;
    }

    bool argRequired{false};
    bool exist{false};
    char opt; ///< option name ( -p )
    string alias; ///< full option name ( --port-name )
    vector<OptArg> args; ///< array of arguments
    string default_value; ///< default_value that is used in case no args provided

private:
    void check_opt(char opt){
        if (opt&&!::isalnum(opt))
            throw std::logic_error("option must be a valid ascii characted from latin alphabet");
    }
};

/**
 * @brief Entry point to parse.
 * This class should be instantiated with argc and argv
 * When instantiated it parser input
 *
 * Here goes long description
 */

struct LesChoix {

    /**
     * @brief LesChoix constructor
     * @param argc count of arguments
     * @param argv values of arguments
     *
     * Parses argv to array of lesopts.
     * If any of them empty - applies default value
     */
    LesChoix(int argc, char **argv){
        Parse(argc, argv);

        for (lesopt& it: values){
            if (it.args.empty())
                it.args.push_back(it.default_value);
        }
    }

    LesChoix(int argc, char **argv, std::function<void(string, vector<string>)> handler){
        this->handler=handler;

        Parse(argc, argv);

        handle();
    }

    void setHandler(std::function<void(string, vector<string>)> handler){ this->handler=handler; }

    /**
     * @brief Parse
     * @param argc count of arguments
     * @param argv values of arguments
     */
    void Parse(int argc, char **argv){
        string line;
        string opt;
        vector<lesopt>::iterator it=values.end();
        for (int i=1;i<argc;++i){
            line=argv[i];

            if (line.at(0)=='-'){
                size_t j=1;
                if (line.at(1)=='-')
                    j=2;

                line=line.substr(j, line.size()-1);
                j=line.find('=');
                opt=line;

                if (j!=string::npos){
                    opt=line.substr(0, j);
                    line=line.substr(j+1, line.size()-1);
                } else {
                    line.clear();
                }

                if (opt.size()==1){
                    it=find_if(values.begin(), values.end(), [&opt](const lesopt& x){
                        return x.opt==opt.at(0);
                    });
                } else {
                    it=find_if(values.begin(), values.end(), [&opt](const lesopt& x){
                        return x.alias==opt;
                    });
                }

                if (it!=values.end()&&!line.empty()){
                    it->args.push_back(line);
                    it->exist=true;
                }

            } else {
                if (it!=values.end()){
                    it->args.push_back(line);
                    it->exist=true;
                }
            }
        }
    }

    void handle(){
        for (lesopt& x: values){
            if (x.exist)
                handler(x.getOpt(), x.strArgs());
        }
    }

    /**
     * @brief fast access to lesopt
     * @param str name of option
     */
    auto operator[](const string& str){
        auto it=find_if(values.begin(), values.end(), [&str](const lesopt& x){
            return !x.alias.empty()&&x.alias==str;
        });

        if (it!=values.end())
            return *it;
        else throw std::logic_error("no such option");
    }

    /**
     * @brief overload for short option name
     * @param str name of option
     */
    auto operator[](const char& c){
        auto it=find_if(values.begin(), values.end(), [&c](const lesopt& x){
            return x.opt&&x.opt==c;
        });

        if (it!=values.end())
            return *it;
        else throw std::logic_error("no such option");
    }

    function<void(string, std::vector<string>)> handler{ [](string, vector<string>){} };
    static options values; ///< array that holds parsed values
};

}//YY testing namespace

#endif // LESCHOIX_V2_HPP
