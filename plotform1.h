#ifndef PLOTFORM1_H
#define PLOTFORM1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>




class plotform1: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    plotform1(double x, double y,int p);
    plotform1();
    ~plotform1();

    QGraphicsPixmapItem *item;
    QGraphicsPixmapItem *tool;
    int weight=200;
    int height=80;
    int flag=0;//for plotform2
    int clk=0;
    int tool_f=0;


public slots:
    void catch_player(double,double);
    virtual void func();
    void item_down(int);


signals:
    void catch_signal(void);
    void spring_signal(void);
    void rocket_signal(void);


};

#endif // PLOTFORM1_H
