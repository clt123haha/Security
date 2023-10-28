#ifndef PLAYBACKWIN_H
#define PLAYBACKWIN_H

#include <QWidget>
#include <QDebug>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QTimer>
#include <QGridLayout>
#include <QStackedLayout>
#include "videoplaybackwin.h"
#include "imgshowwin.h"

class PlaybackWin : public QWidget
{
    Q_OBJECT
public:
    PlaybackWin();
    void initContorl();
    void setUid(int value);

private:
    QPushButton *bun1,*bun2;
    QStackedLayout *rightLayout;
    QWidget *leftWin,*rightWin;
    QHBoxLayout *totalLayout;
    QVBoxLayout *leftLayout;
    ImgShowWin *page2;
    VideoPlaybackWin *page1;
    int uid;

signals:

public slots:
    //打开界面1
    void turntoPage1();
    //打开界面2
    void turntoPage2();
};

#endif // PLAYBACKWIN_H
