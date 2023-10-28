#include "startuanimation.h"

startuanimation::startuanimation()
{
    mainwin = new MainWin;
    this->setFixedSize(361,197);
    this->setWindowTitle("开机动画");
    this->setWindowIcon(QIcon(":/img/fly.png"));
    this->setBackgroundBrush(QBrush(QPixmap(":/img/star_background.jpg")));
    mySence = new QGraphicsScene;
    this->setScene(this->mySence);
    this->setSceneRect(0,0,this->width()-2,this->height()-2);
    this->item1 = new MyItem(":/img/ball.png",1,1);
    this->mySence->addItem(this->item1);
    this->item1->setPos(50,this->height()/2);

    this->item2 = new MyItem(":/img/ball.png",1,-1);
    this->mySence->addItem(this->item2);
    this->item2->setPos(this->width()-50,this->height()/2);

    timer = new QTimer();
    timer->start(100);
    connect(timer,SIGNAL(timeout()),this->mySence,SLOT(advance()));
    connect(this->item1,SIGNAL(boom()),this,SLOT(openMainWin()));
}

void startuanimation::openMainWin()
{
    this->hide();
    mainwin->cheakSetWin();
    disconnect(this->item1,SIGNAL(boom()),this,SLOT(openMainWin()));
}
