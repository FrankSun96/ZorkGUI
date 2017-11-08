#include "inventory.h"
#include "game.h"
#include "button.h"
extern Game *game;
Inventory::Inventory(QWidget *parent)
{

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
    setBackgroundBrush(QBrush(QImage(":/images/inventory.png")));

    //create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,500,391);


    //make the newly created scene the scene to visualize
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(500,391);

    //create cancel button
    exit = new Button(new QPixmap(":/images/exitInventory.png"), "exitInventory");
    scene->addItem(exit);
    exit->setPos(450, 30);

    setCursor(QPixmap(":/images/cursor.png"));

    showMyItems();
    this->show();


}

void Inventory::showMyItems()
{
    int size = 70;
    int next = 0, next2 = 0;
    int count = 0;
    clearItems();
    for(vector<Item>::iterator i = game->player->myitemList()->begin(); i != game->player->myitemList()->end(); i++)
    {
       string picDes = ((*i).getShortDescription());
       string picLongDes = ((*i).getLongDescription());
       string picURL = ((*i).getPic());
       Button *item = new Button(new QPixmap(QString::fromStdString(picURL)), picDes);
       QGraphicsTextItem *shortDes = new QGraphicsTextItem(QString::fromStdString(picDes));
       QGraphicsTextItem *longDes = new QGraphicsTextItem(QString::fromStdString(picLongDes));
       shortDes->setDefaultTextColor(QColor(235,121,0));
       shortDes->setFont(QFont("times", 14, 75));
       longDes->setDefaultTextColor(QColor(209,108,0));
       longDes->setFont(QFont("times", 12));
       scene->addItem(item);
       scene->addItem(shortDes);
       scene->addItem(longDes);
       if(count < 3){
           item->setPos(40, 120 + next*size);
           shortDes->setPos(100, 120 + next*size);
           longDes->setPos(100, 140 + next*size);
           next++;
       }else{
           item->setPos(230, 120 + next2*size);
           shortDes->setPos(290, 120 + next2*size);
           longDes->setPos(290, 140 + next2*size);
           next2++;
       }
       count++;
    }
}

void Inventory::clearItems()
{
    QList<QGraphicsItem*> items = scene->items();
    for(int i = 0; i < items.size(); i++){
         if(typeid(*(items[i])) == typeid(Button)){
             if(static_cast<Button*>(items[i])->getName() != "exitInventory"){
                      delete items[i];
             }
         }
         if(typeid(*(items[i])) == typeid(QGraphicsTextItem)){
             delete items[i];
         }
    }
}



