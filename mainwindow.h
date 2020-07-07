#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <cstdlib>
#include <QDialog>
#include <QGridLayout>



#include "bullet.h"
#include "plotform1.h"
#include "plotform2.h"
#include "plotform3.h"
#include "monster.h"
#include "hole.h"


using namespace std;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void gen_obj();
    void init_plotform();




public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    void jump();
    void stop_jump();
    void game_over(double,double);
    void spring_jump();
    void rocket();
    void Monster_died();
    void game_over();
    void pause__slot(void);


signals:
     void dropping(double,double);
     void view_up(int);
     void player_position(double,double);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *player;
    QTimer *timer;
    int count=0;
    int spring_f;//for jump
    int rocket_f;
    int score;
    double height;
    int py=3;
    monster *Monster;
    hole *Hole;
    int pause_f;

    int pre_r;
    int Mx=0;


};


#endif // MAINWINDOW_H
