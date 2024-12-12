#ifndef UTIL_H
#define UTIL_H

#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
using namespace std;

class YamlUtil{
    private:
        unordered_map<string,unordered_map<string,string>> pplInfo; // {"Alice":{"age":"18","occupation":"student"},"Bob":{...}}
        YAML::Node node;
        unordered_map<string,string> subMap;
        bool ifSequence();
        void convertToSubMap(YAML::const_iterator it);
        string personInfo(string name, string field);
    public:
        YamlUtil(const string& path);
        void buildPplInfo();
        bool validName(string name);
        bool validField(string name, string field);
        string getPersonInfo(string name, string field);
};

#endif