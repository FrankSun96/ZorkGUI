#include "button.h"
#include "game.h"

extern Game *game;
Button::Button(QPixmap *pic, string des)
{
    setPixmap(*pic);
    name = des;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        game->player->checkAction(this);
    }
}

string Button::getName()
{
    return name;
}

void Button::setName(string name)
{
    this->name = name;
}
