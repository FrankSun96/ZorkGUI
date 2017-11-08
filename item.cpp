#include "item.h"

Item::Item(string inDescription, string inLongDescription, string inPic)
{
    description = inDescription;
    longDescription = inLongDescription;
    pic = inPic;
}

string Item::getShortDescription()
{
    return description;
}

string Item::getLongDescription()
{
    return longDescription;
}

string Item::getPic()
{
    return pic;
}
