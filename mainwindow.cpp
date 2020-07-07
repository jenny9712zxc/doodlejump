#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 500, 600)),
    timer(new QTimer)
    {
        ui->setupUi(this);
        ui->graphicsView->setScene(scene);
        player = new QGraphicsPixmapItem(QPixmap(":/res/doodle0.png").scaled(50, 100));
        scene->addItem(player);
        player->setPos(200, 540);
        timer->start(10);
        connect(timer, SIGNAL(timeout()), this, SLOT(jump()));
        connect(this, SIGNAL(dropping(double,double)), this, SLOT(game_over(double,double)));


        score=0;
        height=player->y()-110;
        ui->score_label->setText(QString::number(0));

        spring_f=0;
        rocket_f=0;
        setFocusPolicy(Qt::StrongFocus);
        pause_f=0;
        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pause__slot()));


        init_plotform();

        //Monster->exist=0;
        Monster=NULL;


        Monster=new  monster(200);
        scene->addItem(Monster->item);
        connect(this, SIGNAL(view_up(int)), Monster, SLOT(item_down(int)));
        connect(Monster, SIGNAL(died()), this, SLOT(Monster_died()));

        connect(this, SIGNAL(player_position(double,double)), Monster, SLOT(collision(double,double)));
        connect(Monster, SIGNAL(collision_signal()), this, SLOT(game_over()));

        //Hole->exist=0;
        Hole=NULL;


        Hole=new hole();
        scene->addItem(Hole->item);
        connect(this, SIGNAL(view_up(int)), Hole, SLOT(item_down(int)));
        connect(this, SIGNAL(player_position(double,double)), Hole, SLOT(collision(double,double)));
        connect(Hole, SIGNAL(collision_signal()), this, SLOT(game_over()));

    }


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

    double x,y;
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        y=player->y() - 10;
        //cout<<y<<endl;
        if(y<-40)
            y=-40;
        player->setPos(player->x(), y);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        y=player->y() +10;
        //cout<<y<<endl;
        if(y>540)
            y=540;
        player->setPos(player->x(), y);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        x=player->x() - 10;
        //cout<<x<<endl;
        if(x<-20)
            x=470;
        player->setPos(x, player->y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        x=player->x() + 10;
        //cout<<x<<endl;
        if(x>470)
            x=-20;
        player->setPos(x, player->y());
        break;

    case Qt::Key_F:
        spring_f=1;
        count=0;
        break;
    case Qt::Key_P:
        cout<<"x:"<<player->x()<<"  y:"<<player->y()<<"   height:"<<height<<"   count:"<<count<<endl;
        break;
    case Qt::Key_Z:
        count=0;
        break;
    case Qt::Key_X:
        count=80;
        break;

    }
    if(e->key() == Qt::Key_H)
    {
        if(Hole != NULL)
        {
            cout<<"Hole y      "<<Hole->item->y()<<endl;
            cout<<"Hole exist  "<<Hole->exist<<endl;
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    bullet *b = new bullet;

    b->setPixmap(QPixmap(":/res/bullet.png").scaled(80, 180));
    b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
    b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
    if(Monster!=NULL)
        connect(b, SIGNAL(attack(double,double)), Monster, SLOT(attacked(double,double)));
}

void MainWindow::jump()
{
    if(count<0)  return;//stop timer for count

    if(spring_f==1 &&  count<80)
    {
        player->setPos(player->x(), player->y()-2);
    }
    else if (rocket_f==1)
    {
        if(count>80)//make player stop in screen
            player->setPos(player->x(), player->y()-2);
        if(count>100)
        {
           rocket_f=0;
           gen_obj();
           init_plotform();
           height=player->y();
        }

        score+=5;
        ui->score_label->setText(QString::number(score));
        emit view_up(10);
    }

    if(player->y()<-40)//prevent item exceed boundary
    {
        count=80;//make droping
    }


    if(count<80)
        player->setPos(player->x(), player->y()-2);
    else
    {
        player->setPos(player->x(), player->y()+2);
        dropping(player->x(), player->y());
    }

    count++;

    emit player_position(player->x(), player->y());


    return;
}


void MainWindow::stop_jump()
{
    //count=0;
    spring_f=0;
    int diff=round(height-player->y());


    if(diff>0)
    {

        for(int i=-2; i<(diff/100); ++i)
            gen_obj();
        height=player->y()+diff;

        //cout<<"diff "<<diff<<endl;
        score+=diff;
        ui->score_label->setText(QString::number(score));
        emit view_up(diff);
        player->setPos(player->x(),height);
    }

    if(height < 300)
    {
        //cout<<"height < 300"<<endl;
        for(int i=0; i<6; ++i)
        {
            plotform1 *p=new plotform1(i*90-50,i*100-300,0);
            scene->addItem(p->item);

            connect(timer, SIGNAL(timeout()), p, SLOT(func()));
            connect(this, SIGNAL(dropping(double,double)), p, SLOT(catch_player(double,double)));
            connect(p, SIGNAL(catch_signal()),this, SLOT(stop_jump()));
            connect(this, SIGNAL(view_up(int)), p, SLOT(item_down(int)));
        }

        height+=200;
        score+=200;
        ui->score_label->setText(QString::number(score));
        emit view_up(200);
    }
    count=0;
    return;
}



void MainWindow::game_over(double x,double y)
{
    if(y>560)
    {
        game_over();
    }
    return;
}

void MainWindow::game_over()
{

    //cout<<"game over"<<endl;
    count=-10;

    QDialog *Q=new  QDialog(this);
    QLabel *L= new  QLabel();
    QString text = "score: " + QString::number( score );
    L->setText(text);
    Q->setWindowTitle(tr("game over"));
    Q->resize(250, 100);
    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(2);
    layout->setMargin(2);
    Q->setLayout(layout);
    layout->addWidget(L, 0, 0);

    Q->show();
    return;
}

void MainWindow::spring_jump()
{
    spring_f=1;
}

void MainWindow::gen_obj(void)
{
    srand( time(NULL) );
    int r ;//= rand())%10;
    int x = (rand()+150*pre_r)%500-50;
    plotform1 *p;

    r=pre_r;
    pre_r=(pre_r+1)%30;



    if(Monster==NULL)
    {
        Monster=new  monster(Mx);
        scene->addItem(Monster->item);
        connect(this, SIGNAL(view_up(int)), Monster, SLOT(item_down(int)));
        connect(Monster, SIGNAL(died()), this, SLOT(Monster_died()));

        connect(this, SIGNAL(player_position(double,double)), Monster, SLOT(collision(double,double)));
        connect(Monster, SIGNAL(collision_signal()), this, SLOT(game_over()));


        Mx=(Mx+50)%201;
    }
    if (Hole->exist == 0)//(Hole==NULL )
    {
        Hole=new hole();
        scene->addItem(Hole->item);
        connect(this, SIGNAL(view_up(int)), Hole, SLOT(item_down(int)));
        connect(this, SIGNAL(player_position(double,double)), Hole, SLOT(collision(double,double)));
        connect(Hole, SIGNAL(collision_signal()), this, SLOT(game_over()));
    }



    int y=(py-2)*100;

    //cout<<r<<"  "<<x<<"   "<<y<<endl;

    if(r==0)
        p=new plotform3(x,y);
    else if(r==1)
        p=new plotform2(x,y);
    else if(r==3)//rocket
    {
        p=new plotform1(x,y,2);
        connect(p, SIGNAL(rocket_signal()),this, SLOT(rocket()));
        scene->addItem(p->tool);
    }
    else if(r==2)//spring
    {
        p=new plotform1(x,y,1);
        connect(p, SIGNAL(spring_signal()),this, SLOT(spring_jump()));
        scene->addItem(p->tool);
    }
    else
        p=new plotform1(x,y,0);


    py=(1+py)%5;

    connect(timer, SIGNAL(timeout()), p, SLOT(func()));

    scene->addItem(p->item);

    connect(this, SIGNAL(dropping(double,double)), p, SLOT(catch_player(double,double)));
    connect(p, SIGNAL(catch_signal()),this, SLOT(stop_jump()));
    connect(this, SIGNAL(view_up(int)), p, SLOT(item_down(int)));

    return;
}

void MainWindow::rocket(void)
{
    rocket_f=1;
}

void MainWindow::init_plotform(void)
{
    int r = 0;
    plotform1 *p;


    for(r=0;r<8;++r){
        if(r==0)
            p=new plotform3(0,100);
        else if(r==1)
            p=new plotform2(200,0);
        else
        {
            int rr = (r-2);

            if(rr==1)//spring
            {
                p=new plotform1(0,300,1);
                connect(p, SIGNAL(spring_signal()),this, SLOT(spring_jump()));
                scene->addItem(p->tool);
            }

            else if(rr==0)//rocket
            {
                p=new plotform1(300,150,2);
                connect(p, SIGNAL(rocket_signal()),this, SLOT(rocket()));
                scene->addItem(p->tool);
            }
            else if(rr==2)
                p=new plotform1(100,500,0);
            else if(rr==3)
                p=new plotform1(300,400,0);
            else if(rr==4)
                p=new plotform1(-50,400,0);
            else if(rr==5)
                p=new plotform1(250,250,0);


        }


        connect(timer, SIGNAL(timeout()), p, SLOT(func()));

        scene->addItem(p->item);

        connect(this, SIGNAL(dropping(double,double)), p, SLOT(catch_player(double,double)));
        connect(p, SIGNAL(catch_signal()),this, SLOT(stop_jump()));
        connect(this, SIGNAL(view_up(int)), p, SLOT(item_down(int)));
    }
    return;
}

void MainWindow::Monster_died()
{
    //cout<<"Monster_died()"<<endl;


    if(Monster!=NULL)
    {
        //cout<<"Monster!=NULL"<<endl;
        Monster->exist=0;
        Monster->item->setPos(0, 800);
    }

    Monster=NULL;

    //delete Monster;

    if(Hole != NULL)
    {
        cout<<"Hole y      "<<Hole->item->y()<<endl;
        cout<<"Hole exist  "<<Hole->exist<<endl;
    }

}

void MainWindow::pause__slot()
{
    if(pause_f==0)
        count=-10;//stop
    else
        count=80;//drop

    pause_f=(pause_f+1)%2;

}
