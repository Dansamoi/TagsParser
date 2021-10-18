#include <iostream> 
#include <sstream>
#include <fstream>
#include "Tag.h"

using namespace std;

Tag* findTag(vector<Tag*> tags, string name) {
    for (auto tag : tags) {
        if (tag->name == name) return tag;
    }
    return 0;
}

int main() {
    //file content
    ifstream fh("some.txt");
    string fileContents;
    string fileLine;

    while (getline(fh, fileLine)) {
        if (!fileLine.empty()) {
            fileContents.append(fileLine);
            fileContents.append("\n");
        }
    }
    fh.close();

    cout << fileContents << endl << endl;

    stringstream file(fileContents);

    Tag* base = new Tag(); //base tag
    Tag* now = base; //moving pointer
    Tag* t;

    string line, tagName, attrN, attrV, eq;
    int nameSize;
    //creating tag tree
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> tagName;
        nameSize = tagName.length();
        t = new Tag();
        if (tagName[1] != '/') {//if not tag closing
            if (tagName[nameSize - 1] != '>') {
                t->name = tagName.substr(1, nameSize - 1);
                while (iss) {
                    iss >> attrN >> eq >> attrV;
                    attrV = attrV.substr(1, attrV.length() - 1);
                    int symI = attrV.find('"');
                    attrV = attrV.substr(0, symI);
                    t->attr.insert({ attrN,attrV });
                }
            }
            else t->name = tagName.substr(1, nameSize - 2);
            now->tags.push_back(t);
            t->inside = now;
            now = t;
        }
        else {//if tag closing
            now = now->inside;
        }
    }

    now = base;
    string command, tagRequest, name, param;

    while (true) {
        now = base;
        bool theTag = true;

        //command
        cout << ">>";
        cin >> command;
        if (command == "exit") break;

        stringstream inCommand(command);
        getline(inCommand, tagRequest, '~');

        stringstream inRequset(tagRequest);
        while (getline(inRequset, name, '.')) {
            now = findTag(now->tags, name);
            if (!now) {
                cout << "The Tag doesn't exist!" << endl;
                theTag = false;
                break;
            }
        }
        if (!theTag) continue;

        getline(inCommand, param);
        if (param.empty()) now->printTagData();
        else {
            bool flag = false;
            for (auto pair : now->attr) {
                if (pair.first == param) {
                    cout << pair.second << endl;
                    flag = true;
                    break;
                }
            }
            if (!flag) cout << "The Tag doesn't have this parameter!" << endl;
        }
    }
    delete base;

    return 0;
}
