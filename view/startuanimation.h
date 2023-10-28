#ifndef STARTUANIMATION_H
#define STARTUANIMATION_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "data/myitem.h"
#include <QObject>
#include "mainwin.h"

class startuanimation : public QGraphicsView
{
    Q_OBJECT
public:
    startuanimation();

private:
    QImage img;
    QGraphicsScene *mySence;
    MyItem *item1,*item2,*item3;
    QTimer *timer;
    MainWin *mainwin;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* imageItem;
    QStringList imagePaths;
    int currentIndex;

public slots:
    //打开主窗口
    void openMainWin();

signals:

};

#endif // STARTUANIMATION_H
