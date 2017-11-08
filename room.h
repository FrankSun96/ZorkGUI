#ifndef ROOM_H
#define ROOM_H
#include <map>
#include <string>
#include <vector>

#include "item.h"
#include "button.h"
#include "enemy.h"

class Room{
public:
    Room(string description, string longDes);
    void setExits(Room *north, Room *east, Room *south, Room *west);
    string shortDescription();
    string longDescription();
    Room* nextRoom(string direction);
    void addItem(Item *inItem);
    void addEnemy(Enemy *enemy);
    void removeItem(Item *removed);
    bool showCurrentItems();
    bool isEnemy();
    void killEnemy();
    Enemy *getCurrentEnemy();
private:
    string description;
    string longDes;
    map<string, Room*> exits;
    string exitString();
    vector <Item> itemsInRoom;
    vector <Enemy> enemyInRoom;
};

#endif // ROOM_H
