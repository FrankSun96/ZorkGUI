#ifndef INVENTORY_H
#define INVENTORY_H
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <vector>


#include "button.h"
using namespace std;
class Inventory: public QGraphicsView{
public:
    Inventory(QWidget *parent=0);
    void showMyItems();
    void clearItems();
private:
    QGraphicsScene *scene;
    Button *exit;
};

#endif // INVENTORY_H
