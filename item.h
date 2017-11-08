#ifndef ITEM_H
#define ITEM_H
//#include <map>
#include <string>
#include <iostream>


using namespace std;

class Item{
public:
    Item (string inDescription, string inLongDescription, string inPic);
    string getShortDescription();
    string getLongDescription();
    string getPic();

private:
    string description;
    string longDescription;
    string pic;

};
#endif // ITEM_H
