#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


class monster: public QObject//, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    monster(int x);
    QGraphicsPixmapItem *item;
    int exist;

public slots:
    void attacked(double x,double y);
    void collision(double x,double y);
    void item_down(int);

signals:
    void died(void);
    void collision_signal(void);


};

#endif // MONSTER_H
