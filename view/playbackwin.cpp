#include "playbackwin.h"

PlaybackWin::PlaybackWin()
{
    this->resize(640,480);
    this->initContorl();
}

void PlaybackWin::initContorl()
{
    totalLayout = new QHBoxLayout;
    totalLayout->setContentsMargins(10,0,0,10);
    this->setLayout(totalLayout);
    leftWin = new QWidget;
    rightWin = new QWidget;
    leftLayout = new QVBoxLayout;
    rightLayout = new QStackedLayout;
    leftWin->setStyleSheet("background-color:yellow");
    leftWin->setLayout(leftLayout);
    rightWin->setLayout(rightLayout);
    totalLayout->addWidget(leftWin,1);
    totalLayout->addWidget(rightWin,6);

    bun1 = new QPushButton("视频回放");
    bun2 = new QPushButton("照片列表");

    leftLayout->addWidget(bun1);
    leftLayout->addWidget(bun2);

    page1 = new VideoPlaybackWin;
    page2 = new ImgShowWin;

    rightLayout->addWidget(page1);
    rightLayout->addWidget(page2);

    connect(bun1,SIGNAL(clicked()),this,SLOT(turntoPage1()));
    connect(bun2,SIGNAL(clicked()),this,SLOT(turntoPage2()));
}

void PlaybackWin::setUid(int value)
{
    uid = value;
    page2->setUid(value);
    page1->setUid(value);
}

void PlaybackWin::turntoPage1()
{
    page1->initVideoMes();
    rightLayout->setCurrentIndex(0);
}

void PlaybackWin::turntoPage2()
{
    page2->showPicture();
    rightLayout->setCurrentIndex(1);
}
