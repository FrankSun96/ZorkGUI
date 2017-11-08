#include "final.h"
#include <qDebug>

Final::Final(string pic)
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
    setBackgroundBrush(QBrush(QImage(QString::fromStdString(pic))));

    //create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,700,584);


    //make the newly created scene the scene to visualize
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(700,584);

    setCursor(QPixmap(":/images/cursor.png"));

    this->show();
}

