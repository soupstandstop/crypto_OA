#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
using namespace std;
static string inputMissing = "Usage: lookup-cli <name> <output_field>";
static string nameNotFound = "Name not found";
static string fieldNotFound = "Field not found";
class strProcessor{
    private:
        vector<string> inputTokens;
    public:
        strProcessor(string wholeline, const char delim){
            istringstream iss(wholeline);
            string buff;
            while (getline(iss, buff, delim)){
                inputTokens.push_back(buff);
            }
        }
        bool sizeValid(){
            if (inputTokens.size()==2) return true;
            return false;
        }
        string getName(){
            return inputTokens[0];
        }
        string getField(){
            return inputTokens[1];
        }
};
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
        bool validName(string name){
            if (pplInfo.find(name)==pplInfo.end()) return false; // name not found
            return true; // name exists
        }
        bool validField(string name, string field){
            if (pplInfo[name].find(field)==pplInfo[name].end()) return false; // field not found in pplInfo[name]
            return true; // field exists in pplInfo[name]
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
        string getPersonInfo(string name, string field){
            if (!validName(name)) {
                return nameNotFound;
            }
            if (!validField(name,field)) {
                return fieldNotFound;
            }
            return personInfo(name,field);
        }
};
int main(){
    YamlUtil* obj = new YamlUtil("./test.yaml");
    string wholeline;
    while (true){
        getline(cin,wholeline);
        strProcessor* strProcess = new strProcessor(wholeline, ' ');
        if (!strProcess->sizeValid()) cout << inputMissing << endl;
        else {
            string name = strProcess->getName();
            string field = strProcess->getField();
            cout << obj->getPersonInfo(name, field) << endl;
        }
    }
    return 0;
}