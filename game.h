#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>

#include "player.h"
#include "button.h"
#include "room.h"

class Game:public QGraphicsView{
public:
    Room *currentRoom, *a, *b, *c, *d, *e, *f, *g, *h, *i;
    Player *player;
    QGraphicsSimpleTextItem *myDiary;
    QGraphicsTextItem *health;
    QGraphicsTextItem *strength;
    QGraphicsScene *scene;
    Button *item1;
    Button *item2;
    Button *enemy;
    Game(QWidget *parent=0);
    void createRoom();

private:
    Button *up;
    Button *down;
    Button *left;
    Button *right;
    Button *exit;
    Button *inventory;
};

#endif // GAME_H
