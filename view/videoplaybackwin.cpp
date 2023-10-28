#include "videoplaybackwin.h"

VideoPlaybackWin::VideoPlaybackWin(QWidget *parent) : QWidget(parent)
{
    this->setWindowIcon(QIcon(":/img/fly.png"));
    this->resize(600,480);
    initContorl();
    count = 0;
    index = 0;
}

void VideoPlaybackWin::initContorl()
{
    totalLayout = new QHBoxLayout;
    this->setLayout(totalLayout);

    img1 = new ClickLabel(1);
    img2 = new ClickLabel(2);
    img3 = new ClickLabel(3);
    img4 = new ClickLabel(4);

    img1->setText("1");
    img2->setText("2");
    img3->setText("3");
    img4->setText("4");

    mesWin = new QWidget;
    mesLayout = new QVBoxLayout;
    mesWin->setLayout(mesLayout);

    calendarWidget = new QCalendarWidget;

    totalLayout->addWidget(img1,6);
    totalLayout->addWidget(mesWin,4);

    search = new QPushButton("查询");
    one = new QPushButton("1");
    two = new QPushButton("2");
    three = new QPushButton("3");
    mes1 = new QLabel;
    mes2 = new QLabel;
    mes3 = new QLabel;

    mesLayout->addWidget(search);

    rowLayout1 = new QHBoxLayout;
    rowLayout1->addWidget(img2);
    rowLayout1->addWidget(mes1);

    rowLayout2 = new QHBoxLayout;
    rowLayout2->addWidget(img3);
    rowLayout2->addWidget(mes2);

    rowLayout3 = new QHBoxLayout;
    rowLayout3->addWidget(img4);
    rowLayout3->addWidget(mes3);

    rowLayout4 = new QHBoxLayout;
    rowLayout4->addWidget(one);
    rowLayout4->addWidget(two);
    rowLayout4->addWidget(three);

    mesLayout->addLayout(rowLayout1);
    mesLayout->addLayout(rowLayout2);
    mesLayout->addLayout(rowLayout3);
    mesLayout->addLayout(rowLayout4);

    player = new Player();

    connect(one,SIGNAL(clicked()),this,SLOT(forward()));
    connect(player,SIGNAL(upone()),this,SLOT(videoUpOne()));
    connect(player,SIGNAL(downone()),this,SLOT(videoDownOne()));
    connect(player,SIGNAL(back()),this,SLOT(closePlayer()));
    connect(two,SIGNAL(clicked()),this,SLOT(back()));
    connect(three,SIGNAL(clicked()),this,SLOT(forward2()));
    connect(img1,SIGNAL(labelClicked(int)),this,SLOT(palyVideo()));
    connect(img2,SIGNAL(labelClicked(int)),this,SLOT(changeIndex(int)));
    connect(img3,SIGNAL(labelClicked(int)),this,SLOT(changeIndex(int)));
    connect(img4,SIGNAL(labelClicked(int)),this,SLOT(changeIndex(int)));
    connect(calendarWidget,SIGNAL(selectionChanged()),this,SLOT(changedata()));
     connect(search,SIGNAL(clicked()),this,SLOT(showCalendarWidget()));

}

void VideoPlaybackWin::initVideoMes()
{

    count = 0;
    index = 0;
    indexnow = 0;

    img1->clear();
    img2->clear();
    img3->clear();
    img4->clear();

    mes1->clear();
    mes2->clear();
    mes3->clear();

    VideoController *myVideoController = VideoController::getVideoController();
    videoList = myVideoController->getVideoList();
    int size = videoList.size();
    QList<ClickLabel*> ClickLabellist;
    QList<QLabel*> QLabellist;
    ClickLabellist.append(img2);
    ClickLabellist.append(img3);
    ClickLabellist.append(img4);
    QLabellist.append(mes1);
    QLabellist.append(mes2);
    QLabellist.append(mes3);
    if(videoList.size()>0)
    {
        QPixmap pixmap;
        pixmap.load(videoList.at(0).getCoverpath());
        img1->setPixmap(pixmap.scaled( QSize(334,189),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    for(int i=0;i<size&&i<3;i++)
    {
        QLabellist.at(i)->setText(videoList.at(i).getCreat_time());
        QPixmap pixmap;
        pixmap.load(videoList.at(i).getCoverpath());
        ClickLabellist.at(i)->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void VideoPlaybackWin::updateVideoMes(QString time)
{
    count = 0;
    index = 0;
    indexnow = 0;

    img1->clear();
    img2->clear();
    img3->clear();
    img4->clear();

    mes1->clear();
    mes2->clear();
    mes3->clear();

    VideoController *myVideoController = VideoController::getVideoController();
    videoList = myVideoController->getVideoList();

    QMutableListIterator<video> iter(videoList);
    while (iter.hasNext()) {
        const video& v = iter.next();
        QDateTime creatTime = QDateTime::fromString(v.getCreat_time(), "yyyyMMddhhmmss");
        QString creatTimeStr = creatTime.toString("yyyyMMdd");

        if (creatTimeStr < time)
        {
            iter.remove();
        }
    }

    int size = videoList.size();

    QList<ClickLabel*> ClickLabellist;
    QList<QLabel*> QLabellist;
    ClickLabellist.append(img2);
    ClickLabellist.append(img3);
    ClickLabellist.append(img4);
    QLabellist.append(mes1);
    QLabellist.append(mes2);
    QLabellist.append(mes3);
    if(videoList.size()>0)
    {
        QPixmap pixmap;
        pixmap.load(videoList.at(0).getCoverpath());
        img1->setPixmap(pixmap.scaled( QSize(334,189),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    for(int i=0;i<size&&i<3;i++)
    {
        QLabellist.at(i)->setText(videoList.at(i).getCreat_time());
        QPixmap pixmap;
        pixmap.load(videoList.at(i).getCoverpath());
        ClickLabellist.at(i)->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void VideoPlaybackWin::setUid(int value)
{
    uid = value;
    player->setUid(value);
}

void VideoPlaybackWin::closePlayer()
{
    player->hide();
    player->setEnd(true);
}

void VideoPlaybackWin::changeIndex(int i)
{
    if(i-1 + count*3 <= videoList.size())
    {
        index = i-2 + count*3;
    }
    else {
        return;
    }
    QPixmap pixmap;
    pixmap.load(videoList.at(index).getCoverpath());
    img1->setPixmap(pixmap.scaled( QSize(334,189),Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

void VideoPlaybackWin::palyVideo()
{
    if(!player->isVisible())
    {
        indexnow = index;
        player->setPath(videoList.at(index).getPath());

        QString filePath = videoList.at(index).getPath();
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        QString extractedString = fileName.section('.', 0, 0);

        player->setTitle(extractedString);
        player->setUid(uid);
        player->setTime(videoList.at(index).getTime());
        player->show();
        player->play();
    }

}

void VideoPlaybackWin::showCalendarWidget()
{
    calendarWidget->show();
}

void VideoPlaybackWin::videoUpOne()
{
    indexnow -= 1;
    if(indexnow >= 0)
    {
        player->setEnd(true);
        player->setPath(videoList.at(indexnow).getPath());

        QString filePath = videoList.at(indexnow).getPath();
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        QString extractedString = fileName.section('.', 0, 0);

        player->setTitle(extractedString);
        player->setUid(uid);
        player->setTime(videoList.at(indexnow).getTime());
        player->play();
    }
    else {
        QMessageBox::information(this,"提示","已经是第一个视频");
        return;
    }
}

void VideoPlaybackWin::videoDownOne()
{
    indexnow += 1;
    if(indexnow < videoList.size())
    {
        player->setEnd(true);
        player->setPath(videoList.at(indexnow).getPath());

        QString filePath = videoList.at(indexnow).getPath();
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        QString extractedString = fileName.section('.', 0, 0);

        player->setTitle(extractedString);
        player->setUid(uid);
        player->setTime(videoList.at(indexnow).getTime());
        player->play();
    }
    else {
        QMessageBox::information(this,"提示","已经是最后一个视频");
        return;
    }
}

void VideoPlaybackWin::back()
{

    if(count == 0)
    {
        if(videoList.size() <= 3)
        {
            QMessageBox::information(this,"提示"," 已经是最后一页");
            return;
        }

        img2->clear();
        img3->clear();
        img4->clear();

        mes1->clear();
        mes2->clear();
        mes3->clear();

        count++;

        QPixmap pixmap;

        if(count < videoList.size())
        {
            pixmap.load(videoList.at(count*3).getCoverpath());
            img2->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mes1->setText(videoList.at(count*3).getCreat_time());

        }

        if(1+count*3 < videoList.size())
        {
            pixmap.load(videoList.at(count*3+1).getCoverpath());
            img3->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mes2->setText(videoList.at(count*3+1).getCreat_time());
        }

        if(2+count*3 < videoList.size())
        {
            pixmap.load(videoList.at(count*3+2).getCoverpath());
            img4->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mes3->setText(videoList.at(count*3+2).getCreat_time());
        }

        if(count != 1)
        {

            one->setText(QString::number(count));
            two->setText(QString::number(count+1));
            three->setText(QString::number(count+2));
        }
    }
}

void VideoPlaybackWin::forward()
{
    if(0 == count)
    {
        QMessageBox::information(this,"提示"," 已经是第一页");
        return;
    }

    img2->clear();
    img3->clear();
    img4->clear();

    mes1->clear();
    mes2->clear();
    count--;
    QPixmap pixmap;

    if(count*3 < videoList.size())
    {
        pixmap.load(videoList.at(count*3).getCoverpath());
        img2->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
        mes1->setText(videoList.at(count*3).getCreat_time());

    }

    if(1+count*3 < videoList.size())
    {
        pixmap.load(videoList.at(count*3+1).getCoverpath());
        img3->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
        mes2->setText(videoList.at(count*3+1).getCreat_time());
    }

    if(1+count*3 < videoList.size())
    {
        pixmap.load(videoList.at(count*3+2).getCoverpath());
        img4->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
        mes3->setText(videoList.at(count*3+2).getCreat_time());
    }

    if(one->text() != "1")
    {

        one->setText(QString::number(count));
        two->setText(QString::number(count+1));
        three->setText(QString::number(count+2));
    }
}

void VideoPlaybackWin::forward2()
{
    if(count == 0)
    {
        if(count+1 >= videoList.size()/3)
        {
            QMessageBox::information(this,"提示","数据不足");
            return;
        }

        img2->clear();
        img3->clear();
        img4->clear();

        mes1->clear();
        mes2->clear();
        mes3->clear();

        count+=2;

        QPixmap pixmap;

        if(count < videoList.size())
        {
            pixmap.load(videoList.at(count*3).getCoverpath());
            img2->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mes1->setText(videoList.at(count*3).getCreat_time());

        }

        if(1+count*3 < videoList.size())
        {
            pixmap.load(videoList.at(count*3+1).getCoverpath());
            img3->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mes2->setText(videoList.at(count*3+1).getCreat_time());
        }

        if(1+count*3 < videoList.size())
        {
            pixmap.load(videoList.at(count*3+2).getCoverpath());
            img4->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mes3->setText(videoList.at(count*3+2).getCreat_time());
        }
        one->setText(QString::number(count));
        two->setText(QString::number(count+1));
        three->setText(QString::number(count+2));
    }
    else
    {
        if(count >= videoList.size()/3)
        {
            QMessageBox::information(this,"提示"," 已经是最后一页");
            return;
        }

        img2->clear();
        img3->clear();
        img4->clear();

        mes1->clear();
        mes2->clear();
        mes3->clear();

        count++;

        QPixmap pixmap;

        if(count < videoList.size())
        {
            pixmap.load(videoList.at(count*3).getCoverpath());
            img2->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mes1->setText(videoList.at(count*3).getCreat_time());

        }

        if(1+count*3 < videoList.size())
        {
            pixmap.load(videoList.at(count*3+1).getCoverpath());
            img3->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mes2->setText(videoList.at(count*3+1).getCreat_time());
        }

        if(2+count*3 < videoList.size())
        {
            pixmap.load(videoList.at(count*3+2).getCoverpath());
            img4->setPixmap(pixmap.scaled( QSize(149,84),Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mes3->setText(videoList.at(count*3+2).getCreat_time());
        }

        one->setText(QString::number(count));
        two->setText(QString::number(count+1));
        three->setText(QString::number(count+2));

    }
}

void VideoPlaybackWin::changedata()
{
    QString timeselect = calendarWidget->selectedDate().toString("yyyyMMdd");
    updateVideoMes(timeselect);
    calendarWidget->hide();
}


