#pragma once
#include <map>
#include <iostream> 
#include <sstream> 
#include <vector>
#include <string>

using namespace std;

class Tag {
public:
    string name;
    map<string, string> attr;
    vector<Tag*> tags;
    Tag* inside = 0;

    Tag(string name = "");

    ~Tag();

    void printTagData();

};

