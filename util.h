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
        unordered_map<string,string> subMap; // {"age":"18","occupation":"student","name":"Alice"}
        bool ifSequence(); // check if yaml type is sequence
        void convertToSubMap(YAML::const_iterator it); // convert each person's info to hashMap
        void buildPplInfo(); // convert personal info to 2d hashMap pplInfo
    public:
        YamlUtil(const string& path); // Load yaml file & convert personal info to 2d hashMap pplInfo
        bool validName(string name); // valid input name
        bool validField(string name, string field); // valid input field
        string getPersonInfo(string name, string field); // get info by (name,field)
};

#endif