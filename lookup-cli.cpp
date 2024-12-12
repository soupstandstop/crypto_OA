#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
#include "util.h"
#include "config.h"
using namespace std;

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