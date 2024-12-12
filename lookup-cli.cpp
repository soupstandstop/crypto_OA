#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
using namespace std;
class YamlUtil{
    private:
        unordered_map<string,unordered_map<string,string>> pplInfo; // {"Alice":{"age":"18","occupation":"student"},"Bob":{...}}
        YAML::Node node;
        unordered_map<string,string> subMap;
    public:
        YamlUtil(const string& path){
            node = YAML::LoadFile(path);
            buildPplInfo();
        }
        bool ifSequence(){
            return node.IsSequence();
        }
        void convertToSubMap(YAML::const_iterator it){
            subMap.clear();
            subMap = it->as<unordered_map<string,string>>();
        }
        void buildPplInfo(){
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
        void lookup(string name, string field){
            cout << pplInfo[name][field] << endl;
        }
};
int main(){
    YamlUtil yamlUtil("./test.yaml");
    yamlUtil.lookup("Alice","age");
    return 0;
}