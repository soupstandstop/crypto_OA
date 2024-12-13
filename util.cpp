#include "util.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
using namespace std;

YamlUtil::YamlUtil(const string& path) {
    node = YAML::LoadFile(path);
    buildPplInfo();
}
bool YamlUtil::ifSequence(){
    return node.IsSequence();
}
void YamlUtil::convertToSubMap(YAML::const_iterator it){
    subMap.clear();
    subMap = it->as<unordered_map<string,string>>();
}
void YamlUtil::buildPplInfo(){
    if (ifSequence()){
        for (YAML::const_iterator it=node.begin(); it!=node.end(); ++it){
            convertToSubMap(it);
            if (subMap.find("name")==subMap.end()) continue; // if no name exists, ignore this subMap
            string pplName = subMap["name"];
            pplInfo[pplName] = subMap; // key=person name, value=personal info
            pplInfo[pplName].erase("name"); // remove "person name" from personal info
        }
    }
}
bool YamlUtil::validName(string name){
    if (pplInfo.find(name)==pplInfo.end()) return false; // name not found
    return true; // name exists
}
bool YamlUtil::validField(string name, string field){
    if (pplInfo[name].find(field)==pplInfo[name].end()) return false; // field not found in pplInfo[name]
    return true; // field exists in pplInfo[name]
}
string YamlUtil::getPersonInfo(string name, string field){
    return pplInfo[name][field];
}