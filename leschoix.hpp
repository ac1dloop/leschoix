#ifndef LESCHOIX_V2_HPP
#define LESCHOIX_V2_HPP

#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace Y {

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
     * @param string value to keep
     */
    OptArg(const string& str):opt(str){}

    /**
     * @brief actual value
     */
    string opt;

    /**
     * @brief get value converted to T
     * @return T - any of arithmetic types
     */
    template <typename T>
    T get(){
        if (is_same<T, uint8_t>::value||is_same<T, uint16_t>::value||is_same<T, uint32_t>::value)
            return stoul(opt);
        else if (is_same<T, uint64_t>::value||is_same<T, unsigned long long>::value)
            return stoull(opt);
        else if (is_same<T, int8_t>::value||is_same<T, int16_t>::value||is_same<T, int32_t>::value)
            return stoi(opt);
        else if (is_same<T, int64_t>::value)
            return stol(opt);
        else if (is_same<T, long long>::value)
            return stoll(opt);
        else if (is_same<T, double>::value)
            return stod(opt);
        else if (is_same<T, long double>::value)
            return stold(opt);
        else if (is_same<T, long double>::value)
            return stof(opt);
        else if (is_same<T, char>::value)
            return opt.at(0);
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
     * @param alias - full oprtion name ( --port )
     */
    lesopt(char opt=0, string alias=""):opt(opt), alias(alias){
        if (opt&&!::isalnum(opt))
            throw std::logic_error("option must be a valid ascii characted from latin alphabet");
    }

    /**
     * @brief Constructor with default value
     * @param opt - option that we parse ( -p )
     * @param alias - full oprtion name ( --port )
     * @param default_value - value that will be used if nothing is parsed
     */
    lesopt(char opt=0, string alias="", string default_value=""):opt(opt), alias(alias), default_value(default_value){
        if (opt&&!::isalnum(opt))
            throw std::logic_error("option must be a valid ascii characted from latin alphabet");
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
    string getArg(){ return args.at(0).opt; }

    /**
     * @brief getArg
     * @return first argument from array converted to T
     */
    template<typename T>
    T getArg(){ return args.at(0).get<T>(); }

    /**
     * @brief strArgs
     * @return array of arguments
     */
    vector<string> strArgs(){
        vector<string> res;

        for (auto x: args)
            res.push_back(x.opt);

        return res;
    }

    /**
     * @brief getArgs
     * @return array<T> of arguments. each converted to T
     */
    template<typename T>
    vector<T> getArgs(){
        vector<T> res;

        for (auto x: args)
            res.push_back(x.get<T>());

        return res;
    }

    char opt; ///< option name ( -p )
    string alias; ///< full option name ( --port-name )
    vector<OptArg> args; ///< array of arguments
    string default_value; ///< default_value that is used in case no args provided
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

        cout << "LesChoix()" << endl;

        for (lesopt& it: values){
            if (it.args.empty())
                it.args.push_back(it.default_value);
        }
    }

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

                if (it!=values.end()&&!line.empty())
                    (*it).args.push_back(line);

            } else {
                if (it!=values.end())
                    (*it).args.push_back(line);
            }
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

    static vector<lesopt> values; ///< array that holds parsed values
};

}//YY testing namespace

#endif // LESCHOIX_V2_HPP
