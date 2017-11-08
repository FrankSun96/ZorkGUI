#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <string>
#include <vector>
#include <QGraphicsScene>
#include <time.h>

#include "item.h"
#include "player.h"
#include "inventory.h"
#include "button.h"
#include "enemy.h"
#include "final.h"

class Player : public QGraphicsPixmapItem{
public :
    Player(QGraphicsItem *parent=0);

    int getHealth();
    int getStrength();
    void checkAction(Button *button);
    vector<Item> *myitemList();
private:   
    void writeDiary(string sentence);
    void clearDiary();
    void goRoom(string direction);
    void addItem(Item* item);
    void useItem(Item* itemUsed);
    bool attack(Enemy *enemy);
    int health;
    int strength;
    vector <Item> myItem;
    Inventory *inven;
};
#endif // PLAYER_H
