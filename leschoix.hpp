#ifndef LESCHOIX_HPP
#define LESCHOIX_HPP

#include <string>
#include <vector>
#include <functional>
#include <map>
#include <iostream>

namespace Y {
using namespace std;

struct OptArg {

    OptArg(const string& str):opt(str){}

    string opt="0";

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

struct lesopt {

    string getOpt(){ return name; }
    string getArg(){ return args.at(0).opt; }
    vector<string> strArgs(){
        vector<string> res;

        for (auto x: args)
            res.push_back(x.opt);

        return res;
    }

    string name;
    vector<OptArg> args;
};

struct LesChoix {

    LesChoix(int argc, char **argv){
        Parse(argc, argv);
    }

    void Parse(int argc, char **argv){
        string line;
        string opt;
        for (int i=1;i<argc;++i){
            line=argv[i];

            if (line.at(0)=='-'){
                size_t j=1;
                if (line.at(1)=='-')
                    j=2;

                line=line.substr(j, line.size()-1);
                j=line.find('=');
                opt=line;

                auto it=special_handlers.find(opt);
                if (it!=special_handlers.end()){
                    it->second();
                    continue;
                }

                if (j!=string::npos){
                    opt=line.substr(0, j);

                    vec.push_back({opt, {line.substr(j+1, line.size()-1)} });

                } else vec.push_back({line, {}});

            } else {
                vec.back().args.push_back(line);
            }
        }
    }

    OptArg& operator[](const string& name){
        for (int i=0;i<vec.size();++i){
            if (vec[i].name==name)
                return vec[i].args.at(0);
        }

        throw std::logic_error("No such opt");
    }

    void process(function<void(string, vector<string>)> handler){
        for (auto x: vec){
            handler(x.name, x.strArgs());
        }
    }

    void process(function<void(string, vector<OptArg>)> handler){
        for (auto x: vec)
            handler(x.name, x.args);
    }

private:
    static map<string, function<void()>> special_handlers;
    vector<lesopt> vec;
};

}//Y namespace

#endif // LESCHOIX_HPP
