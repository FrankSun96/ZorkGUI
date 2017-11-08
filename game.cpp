#include "game.h"

#include <QGraphicsTextItem>
#include <QFont>
#include <QTimer>
#include <QImage>
#include <QDebug>
Game::Game(QWidget *parent){

    //make the view frameless, translucent and no border
    QPalette  myPalette;
    QColor  myColor(100,100,100);
    myColor.setAlphaF(0.0);
    myPalette.setBrush(backgroundRole(),myColor);
    setPalette(myPalette);
    setStyleSheet("border:0px");
    setAutoFillBackground(false);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(Qt::FramelessWindowHint);
    setBackgroundBrush(QBrush(QImage(":/images/zork.png")));

    //create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,850,494);


    //make the newly created scene to visualize
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(850,494);

    //create exit button
    exit = new Button(new QPixmap(":/images/exit.png"), "exit");
    scene->addItem(exit);
    exit->setPos(720 , 30);

    //create a player
    player = new Player();
    scene->addItem(player);
    player->setPos(140, 80);

    //create the text to show the health and strength of the player
    health = new QGraphicsTextItem();
    health->setPlainText(QString("health: ") + QString::number(player->getHealth()));
    health->setDefaultTextColor(QColor(200,78,00));
    health->setFont(QFont("times", 11,QFont::Bold));
    scene->addItem(health);

    strength = new QGraphicsTextItem();
    strength->setPlainText(QString("strength: ") + QString::number(player->getStrength()));
    strength->setDefaultTextColor(QColor(200,78,00));
    strength->setFont(QFont("times", 11,QFont::Bold));
    scene->addItem(strength);

    health->setPos(590,325);
    strength->setPos(590, 355);

    //create a diary to display the information
    myDiary = new QGraphicsSimpleTextItem();
    myDiary->setText(QString("\nKitchen\n"
                             "I am in the kitchen of the white\nhouse. "
                             "A table seems to have been\nused recently for "
                             "the preparation of\nfood."
                             "\nIt seems like there are "
                             "something\non the table."));
    QFont font;
    font.setStyle(QFont::StyleItalic);
    font.setPixelSize(18);
    myDiary->setFont(font);
    scene->addItem(myDiary);
    myDiary->setPos(180, 85);

    //create four direction buttons
    up = new Button(new QPixmap(":/images/buttonUp.png"), "up");
    down = new Button(new QPixmap(":/images/buttonDown.png"), "down");
    left = new Button(new QPixmap(":/images/buttonLeft.png"), "left");
    right = new Button(new QPixmap(":/images/buttonRight.png"), "right");
    scene->addItem(up);
    scene->addItem(down);
    scene->addItem(left);
    scene->addItem(right);
    left->setPos(160,385);
    up->setPos(240,370);
    down->setPos(300,370);
    right->setPos(355,383);

    //create inventory button;
    inventory = new Button(new QPixmap(":/images/inventoryIcon.png"), "inventory");
    scene->addItem(inventory);
    inventory->setPos(460,385);

    //create items button to display the items in room
    item1 = new Button(new QPixmap(":/images/medicine.png"), "medicine");
    item2 = new Button(new QPixmap(":/images/arm.png"), "arm");
    scene->addItem(item1);
    scene->addItem(item2);
    item1->setPos(605, 105);
    item2->setPos(605, 205);

    //create enemy button to display the enemy in room
    enemy = new Button(new QPixmap(""), "");
    scene->addItem(enemy);
    enemy->setPos(430,205);

    //initialize rooms
    createRoom();

    setCursor(QPixmap(":/images/cursor.png"));

    this->show();
}

void Game::createRoom()
{

    a = new Room("Kitchen",
                 "I am in the kitchen of the white\nhouse. "
                 "A table seems to have been\nused recently for "
                 "the preparation of\nfood."
                 );
        a->addItem(new Item("medicine", "a good medicine", ":/images/medicine.png"));
        a->addItem(new Item("arm", "a good arm", ":/images/arm.png"));
        qDebug() << "a finished";
    b = new Room("Living Room",
                 "I am in the living room. The\n"
                 "mirror behind me makes me feel "
                 "weird."
                 );
        b->addItem(new Item("medicine", "a good medicine", ":/images/medicine.png"));
        b->addItem(new Item("teleportation", "teleportation", ":/images/teleportation.png"));
      qDebug() << "b finished item";
        b->addEnemy(new Enemy(3, 1, ":/images/enemy.png", false));
        qDebug() << "b finished";
    c = new Room("Gallery",
                 "This is an art gallery. Most of\n"
                 "the paintings have been stolen by\n"
                 "vandals with exceptional taste.");
        c->addItem(new Item("medicine", "a good medicine", ":/images/medicine.png"));
    d = new Room("Studio",
                 "This appears to have been an artist's\n"
                 "studio. The walls and floors are\nsplattered "
                 "with paints of 69\ndifferent colors.");
        d->addEnemy(new Enemy(3, 1, ":/images/enemy.png", false));
    e = new Room("Attic",
                 "This is the attic.");
        e->addItem(new Item("arm", "a good arm", ":/images/arm.png"));
        e->addEnemy(new Enemy(3, 1, ":/images/enemy.png", false));
    f = new Room("The Troll Room",
                 "This is a small room with passages\n"
                 "to the east and south and a\nforbidding "
                 "hole leading west.");
        f->addItem(new Item("arm", "a good arm", ":/images/arm.png"));
        f->addItem(new Item("teleportation", "teleportation", ":/images/teleportation.png"));
    g = new Room("Round Room",
                 "This is a circular stone room with\n"
                 "passages in all directions. Several\n"
                 "of them have unfortunately been\nblocked "
                 "by cave-ins.");
        g->addEnemy(new Enemy(1, 1, ":/images/enemy.png", false));
    h = new Room("Egyptian Room",
                 "This is a room which looks like\n"
                 "an Egyptian tomb");
    i = new Room("Boss Room",
                 "The exits is blocked by boss, I need to\n"
                 "kill him before I leave.");
        i->addItem(new Item("arm", "a good arm", ":/images/arm.png"));
        i->addEnemy(new Enemy(8, 3, ":/images/boss.png", true));

//             (N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(NULL, NULL, NULL, a);
    c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);

    currentRoom = a;
}
