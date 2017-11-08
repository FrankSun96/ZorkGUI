#include "Room.h"
#include "game.h"

extern Game *game;
Room::Room(string description, string longDes) {
    this->description = description;
    this->longDes = longDes;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
    if (north != NULL)
        exits["north"] = north;
    if (east != NULL)
        exits["east"] = east;
    if (south != NULL)
        exits["south"] = south;
    if (west != NULL)
        exits["west"] = west;
}

string Room::shortDescription() {
    return description;
}

string Room::longDescription() {
    return description + "\n" + longDes;
}

Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
    if (next == exits.end())
        return NULL; // if exits.end() was returned, there's no room in that direction.
    return next->second; // If there is a room, remove the "second" (Room*)
                // part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(*inItem);
}

void Room::addEnemy(Enemy *enemy)
{
    enemyInRoom.push_back(*enemy);
}

void Room::removeItem(Item *removed)
{
    for(int i = 0; i < itemsInRoom.size(); i++){
       if(itemsInRoom[i].getShortDescription() == removed->getShortDescription())
       {
           itemsInRoom.erase(itemsInRoom.begin() + i);
           i--;
       }
    }
}

//every room has at most 2 items and 1 enemy
bool Room::showCurrentItems()
{
    if(itemsInRoom.size() == 0){
        game->item1->setPixmap(QString::fromStdString(""));
        game->item1->setName("");
        game->item2->setPixmap(QString::fromStdString(""));
        game->item2->setName("");
        return false;
    }else if(itemsInRoom.size() == 1){
        string picDes = ((*(itemsInRoom.begin())).getShortDescription());
        string picURL = ((*(itemsInRoom.begin())).getPic());
        game->item1->setPixmap(QString::fromStdString(picURL));
        game->item1->setName(picDes);
        game->item2->setPixmap(QString::fromStdString(""));
        game->item2->setName("");
        return true;
    }else if(itemsInRoom.size() == 2){
        string picDes1 = ((*(itemsInRoom.begin())).getShortDescription());
        string picURL1 = ((*(itemsInRoom.begin())).getPic());
        string picDes2 = ((*(itemsInRoom.end()-1)).getShortDescription());
        string picURL2 = ((*(itemsInRoom.end()-1)).getPic());
        game->item1->setPixmap(QString::fromStdString(picURL1));
        game->item1->setName(picDes1);
        game->item2->setPixmap(QString::fromStdString(picURL2));
        game->item2->setName(picDes2);
        return true;
    }
}

bool Room::isEnemy()
{
    if(enemyInRoom.size() == 0){
        game->enemy->setPixmap(QString::fromStdString(""));
        game->enemy->setName("");
        return false;
    }else{
        string EnemyPic = ((*(enemyInRoom.begin())).getPic());
        game->enemy->setPixmap(QString::fromStdString(EnemyPic));
        game->enemy->setName("enemy");
        return true;
    }
}

void Room::killEnemy()
{
    game->enemy->setPixmap(QString::fromStdString(""));
    game->enemy->setName("");
    enemyInRoom.clear();
}

Enemy *Room::getCurrentEnemy()
{
    return (&(*(enemyInRoom.begin())));
}






