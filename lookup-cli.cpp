#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
using namespace std;
static string inputMissing = "Usage: lookup-cli <name> <output_field>";
static string nameNotFound = "Name not found";
static string fieldNotFound = "Field not found";
class YamlUtil{
    private:
        unordered_map<string,unordered_map<string,string>> pplInfo; // {"Alice":{"age":"18","occupation":"student"},"Bob":{...}}
        YAML::Node node;
        unordered_map<string,string> subMap;
        bool ifSequence(){
            return node.IsSequence();
        }
        void convertToSubMap(YAML::const_iterator it){
            subMap.clear();
            subMap = it->as<unordered_map<string,string>>();
        }
        string personInfo(string name, string field){
            return pplInfo[name][field];
        }
    public:
        YamlUtil(const string& path){
            node = YAML::LoadFile(path);
            buildPplInfo();
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
        bool validName(string name){
            if (pplInfo.find(name)==pplInfo.end()) return false; // name not found
            return true; // name exists
        }
        bool validField(string name, string field){
            if (pplInfo[name].find(field)==pplInfo[name].end()) return false; // field not found in pplInfo[name]
            return true; // field exists in pplInfo[name]
        }
        string getPersonInfo(string name, string field){
            return personInfo(name,field);
        }
};
int main(int argc, char* argv[]){
    YamlUtil* obj = new YamlUtil("./test.yaml"); // process yaml file and build people information into hashMap
    if (argc!=3) {
        cout << inputMissing << endl; // check if input missing
        return 1;
    }
    string name = argv[1];
    string field = argv[2];
    if (!obj->validName(name)) { // check if name is valid
        cout << nameNotFound << endl; 
        return 1;
    }
    if (!obj->validField(name,field)) { // check if field is valid
        cout << fieldNotFound << endl; 
        return 1;
    }
    cout << obj->getPersonInfo(name, field) << endl; // get personal info
    return 0;
}