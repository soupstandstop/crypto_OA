#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
using namespace std;
int main(){
    YAML::Node node = YAML::LoadFile("./test.yaml");
    unordered_map<string,unordered_map<string,string>> pplInfo; // {"Alice":{"age":"18","occupation":"student"},"Bob":{...}}
    if (node.IsSequence()){
        for (int i=0; i<node.size(); ++i){
            unordered_map<string,string> subMap = node[i].as<unordered_map<string,string>>(); // extract map from vector element
            if (subMap.find("name")==subMap.end()) continue; // if no name exists, ignore this subMap
            string pplName = subMap["name"];
            pplInfo[pplName] = subMap; // key=person name, value=personal info
            pplInfo[pplName].erase("name"); // remove "person name" from personal info
        }
    }
    // for (auto ppl=pplInfo.begin(); ppl!=pplInfo.end(); ++ppl){
    //     cout << ppl->first << ":" << endl;
    //     for (auto info=ppl->second.begin(); info!=ppl->second.end(); ++info){
    //         cout << info->first << ": " << info->second << ", ";
    //     }
    //     cout << endl;
    // }
    // string inputName = "Bob";
    // string field = "occupation";
    // cout << pplInfo[inputName][field] << endl;
    return 0;
}