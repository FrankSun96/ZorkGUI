#ifndef FINAL_H
#define FINAL_H
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <string>
using namespace std;

class Final: public QGraphicsView{
public:
    Final(string pic);
private:
    QGraphicsScene *scene;
};

#endif // FINAL_H
