#ifndef HOLE_H
#define HOLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class hole: public QObject
{
    Q_OBJECT

public:
    hole();
    QGraphicsPixmapItem *item;
    int exist;

public slots:
    void collision(double x,double y);
    void item_down(int);

signals:
    void collision_signal(void);
};

#endif // HOLE_H
