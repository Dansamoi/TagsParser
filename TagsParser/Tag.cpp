#include "Tag.h"

Tag::Tag(string name)
{
	this->name = name;
}

Tag::~Tag()
{
    for (auto inTag : tags) {
        delete inTag;
    }
}

void Tag::printTagData()
{
    cout << "[TAG INFO]" << endl;
    if (tags.size()) {
        cout << "Has the tags:\n";
        for (auto inTag : tags) {
            cout << "\t" << inTag->name << endl;
        }
        cout << endl;
    }
    if(!attr.empty()){
        cout << "Has the attributes:\n";
        for (auto attrPair : attr) {
            cout << "\t" << attrPair.first << " = " << attrPair.second << endl;
        }
        cout << endl;
    }
}
