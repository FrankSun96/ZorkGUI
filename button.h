#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "item.h"
using namespace std;
class Button :public QGraphicsPixmapItem{
public :
    Button(QPixmap *pic, string des);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    string getName();
    void setName(string name);
private:
    string name;
};
#endif // BUTTON_H
