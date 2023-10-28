#include "monitorwin.h"

#include <QImageWriter>

MonitorWin::MonitorWin()
{
    this->resize(640,480);
    this->initContorl();
    number = 0;
}

void MonitorWin::initContorl()
{
    isLogin = false;

    totalLayout = new QHBoxLayout;
    this->setLayout(totalLayout);
    leftWin = new QWidget;
    rightWin = new QWidget;
    leftLayout = new QVBoxLayout;
    rightLayout = new QVBoxLayout;
    leftWin->setStyleSheet("background-color:yellow");
    leftWin->setLayout(leftLayout);
    rightWin->setLayout(rightLayout);
    totalLayout->addWidget(leftWin,1);
    totalLayout->addWidget(rightWin,6);


    gridWin = new QWidget;
    gridLayout = new QGridLayout;
    gridWin->setLayout(gridLayout);
    camera1 = new ClickLabel(1);
    camera2 = new ClickLabel(2);
    camera3 = new ClickLabel(3);
    camera4 = new ClickLabel(4);
    camera1->resize(300,150);
    camera2->resize(300,150);
    camera3->resize(300,150);
    camera4->resize(300,150);
    gridLayout->addWidget(camera1, 0, 0, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    gridLayout->addWidget(camera2, 0, 1, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    gridLayout->addWidget(camera3, 1, 0, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    gridLayout->addWidget(camera4, 1, 1, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);

    bunWin = new QWidget;
    bunLayout = new QHBoxLayout;
    bunWin->setLayout(bunLayout);
    onebun = new QPushButton;
    onebun->setIcon(QPixmap(":/img/one.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    bunLayout->addWidget(onebun);
    fourbun = new QPushButton;
    fourbun->setIcon(QPixmap(":/img/four.png").scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    bunLayout->addWidget(fourbun);
    teakPictureBun = new QPushButton("拍照");
    onebun->setMaximumSize(QSize(25,25));
    fourbun->setMaximumSize(QSize(25,25));
    teakPictureBun->setMaximumSize(QSize(50,25));
    bunLayout->addWidget(teakPictureBun);
    bunLayout->setMargin(10);
    bunLayout->setContentsMargins(10,0,0,10);
    rightLayout->addWidget(gridWin,9);
    rightLayout->addWidget(bunWin,1);

    th1 = new DecodingThread;
    th2 = new DecodingThread;
    th3 = new DecodingThread;
    th4 = new DecodingThread;

    connect(camera1,SIGNAL(labelClicked(int)),this,SLOT(ChangeGrid(int)));
    connect(camera2,SIGNAL(labelClicked(int)),this,SLOT(ChangeGrid(int)));
    connect(camera3,SIGNAL(labelClicked(int)),this,SLOT(ChangeGrid(int)));
    connect(camera4,SIGNAL(labelClicked(int)),this,SLOT(ChangeGrid(int)));
    connect(onebun,SIGNAL(clicked()),this,SLOT(ChangeGrid()));
    connect(fourbun,SIGNAL(clicked()),this,SLOT(SeeAllGrid()));  
    connect(teakPictureBun,SIGNAL(clicked()),this,SLOT(takingPicture()));
}

void MonitorWin::openCamera()
{
    namelist = SetController::getSetController()->cheakRow().at(3).split(";", QString::SkipEmptyParts);
    imgpath  = SetController::getSetController()->cheakRow().at(1);
    videopath  = SetController::getSetController()->cheakRow().at(0);

    signalMapper = new QSignalMapper(this);

    for (int i = 0; i < namelist.size(); i++) {
        QPushButton* tempButton = new QPushButton();
        QLabel* label = new QLabel(namelist.at(i));
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);

        QVBoxLayout* layout = new QVBoxLayout(tempButton);
        layout->addWidget(label);
        tempButton->setLayout(layout);
        tempButton->setFixedSize(80, 50);

        layout->setAlignment(Qt::AlignTop); // 设置控件靠上边

        connect(tempButton, &QPushButton::clicked, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
        signalMapper->setMapping(tempButton, i);

        leftLayout->addWidget(tempButton);
    }

    connect(signalMapper, SIGNAL(mapped(int)), this,SLOT(ChangeGridBun(int)));

    int n = namelist.size();
    if(n > 0)
    {
        th1->setName(namelist.at(0));
        if(th1->getReady() != 0)
        {
            QMessageBox::information(this,"提示","摄像头无法打开");
            logController::getlogController()->creatLog(-1,"设备故障");
            return;
        }
        logController::getlogController()->creatLog(-1,"设备正常");
        th1->start();
        connect(th1,SIGNAL(change(QImage)),this,SLOT(getImg1(QImage)));
    }
    if(n > 1)
    {
        th2->setName(namelist.at(1));
        if(th2->getReady() != 0)
        {
            QMessageBox::information(this,"提示","摄像头无法打开");
            logController::getlogController()->creatLog(-1,"设备故障");
            return;
        }
        logController::getlogController()->creatLog(-1,"设备正常");
        th2->start();
        connect(th2,SIGNAL(change(QImage)),this,SLOT(getImg2(QImage)));
    }
    if(n > 2)
    {
        th3->setName(namelist.at(2));
        if(th3->getReady() != 0)
        {
            QMessageBox::information(this,"提示","摄像头无法打开");
            logController::getlogController()->creatLog(-1,"设备故障");
            return;
        }
        logController::getlogController()->creatLog(-1,"设备正常");
        th3->start();
        connect(th3,SIGNAL(change(QImage)),this,SLOT(getImg3(QImage)));
    }
    if(n > 3)
    {
        th4->setName(namelist.at(3));
        if(th4->getReady() != 0)
        {
            QMessageBox::information(this,"提示","摄像头无法打开");
            logController::getlogController()->creatLog(-1,"设备故障");
            return;
        }
        logController::getlogController()->creatLog(-1,"设备正常");
        th4->start();
        connect(th4,SIGNAL(change(QImage)),this,SLOT(getImg4(QImage)));
    }
}

int MonitorWin::cheakGrid()
{
    if(camera1->isVisible() && !camera2->isVisible() && !camera3->isVisible()  && !camera4->isVisible())
        return 1;
    if(!camera1->isVisible() && camera2->isVisible() && !camera3->isVisible()  && !camera4->isVisible())
        return 2;
    if(!camera1->isVisible() && !camera2->isVisible() && camera3->isVisible()  && !camera4->isVisible())
        return 3;
    if(!camera1->isVisible() && !camera2->isVisible() && !camera3->isVisible()  && camera4->isVisible())
        return 4;
    return 0;
}

void MonitorWin::setIsLogin(bool value)
{
    isLogin = value;
}

void MonitorWin::setUid(int value)
{
    uid = value;
    this->th1->setUid(uid);
    this->th2->setUid(uid);
    this->th3->setUid(uid);
    this->th4->setUid(uid);
}

void MonitorWin::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    if(number == 0)
    {
        camera1->resize(200,100);
        camera2->resize(200,100);
        camera3->resize(200,100);
        camera4->resize(200,100);
    }

    else {
        if(number == 1)
            camera1->resize(500,250);
        else if(number == 2)
            camera2->resize(500,250);
        else if(number == 3)
            camera3->resize(500,250);
        else if(number == 4)
            camera4->resize(500,250);
    }

    if (!img1.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img1);
        camera1->setPixmap(pixmap.scaled(camera1->size(), Qt::KeepAspectRatio));
    }

    if (!img2.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img2);
        camera2->setPixmap(pixmap.scaled(camera2->size(), Qt::KeepAspectRatio));
    }
    if (!img3.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img3);
        camera3->setPixmap(pixmap.scaled(camera3->size(), Qt::KeepAspectRatio));
    }
    if (!img4.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img4);
        camera4->setPixmap(pixmap.scaled(camera4->size(), Qt::KeepAspectRatio));
    }
}

void MonitorWin::saveVideo()
{
    int n = namelist.size();
    if(n > 0)
        th1->saveVideo();
    if(n > 1)
        th2->saveVideo();
    if(n > 2)
        th3->saveVideo();
    if(n > 3)
        th4->saveVideo();
}


void MonitorWin::ChangeGrid(int id)
{
    int temp;
    if(number != 0)
    {
        SeeAllGrid();
        return;
    }
    QList<ClickLabel *> name;
    name.append(camera1);
    name.append(camera2);
    name.append(camera3);
    name.append(camera4);

    for(int i=0;i<4;i++)
    {
        if(id == i+1)
        {
            temp = i;
        }
        name.at(i)->setVisible(false);
    }
    name.at(temp)->setVisible(true);

     number = id;
}

void MonitorWin::ChangeGridBun(int id)
{
    if(number != 0)
    {
        QMessageBox::information(this,"提示","图像已经放大");
        return;
    }
    int temp;
    QList<ClickLabel *> name;
    name.append(camera1);
    name.append(camera2);
    name.append(camera3);
    name.append(camera4);
    if(number != 0)
    {
        number = 0;
        update();
    }

    for(int i=0;i<4;i++)
    {
        if(id == i)
        {
            temp = i;
        }
        name.at(i)->setVisible(false);
    }
    name.at(temp)->setVisible(true);
    number = id+1;
}

void MonitorWin::ChangeGrid()
{
    if(number != 0)
    {
        QMessageBox::information(this,"提示","图像已经放大");
        return;
    }

        QList<ClickLabel *> name;

        name.append(camera2);
        name.append(camera3);
   name.append(camera4);
   for(int i=0;i<3;i++)
   {
   name.at(i)->setVisible(false);
   }
   if(number != 0)
   {
       number = 0;
       update();
   }camera1->setVisible(true);
   number = 1;

}

void MonitorWin::SeeAllGrid()
{
    if(number != 0)
    {
        number = 0;
        QList<ClickLabel *> name;
        name.append(camera1);
        name.append(camera2);
        name.append(camera3);
        name.append(camera4);

        for(int i=0;i<4;i++)
        {
            name.at(i)->setVisible(false);
        }

        for(int i=0;i<4;i++)
        {
            name.at(i)->setVisible(true);
        }
    }


}

void MonitorWin::takingPicture()
{
    if(isLogin)
    {
        int res = number;
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString formattedDateTime = currentDateTime.toString("yyyyMMddhhmmss");
        QString path_ = QString("%2/%1").arg(namelist.at(res-1)).arg(imgpath);

        QDir dir(path_);
        if (!dir.exists())
            dir.mkpath(path_);

        QString path = QString("%3/%1/%2.jpg").arg(namelist.at(res-1)).arg(formattedDateTime).arg(imgpath);
        if(res == 0)
            return;
        else if(res == 1)     
        {
            QImageWriter writer(path);
            writer.write(img1);
            ImgController::getImgController()->creatImg(path,uid);
        }
        else if(res == 2)
        {
            QImageWriter writer(path);
            writer.write(img2);
            ImgController::getImgController()->creatImg(path,uid);
        }
        else if(res == 3)
        {
            QImageWriter writer(path);
            writer.write(img3);
            ImgController::getImgController()->creatImg(path,uid);
        }
        else if(res == 4)
        {
            QImageWriter writer(path);
            writer.write(img4);
            ImgController::getImgController()->creatImg(path,uid);
        }

        logController::getlogController()->creatLog(uid,"拍照");

        QMessageBox::information(this,"提示","拍照成功");
    }
    else
    {
        QMessageBox::information(this,"提示","请先登录");
    }
}

void MonitorWin::getImg1(QImage img)
{
    img1 = img;
    this->update();
}

void MonitorWin::getImg2(QImage img)
{
    img2 = img;
    this->update();
}

void MonitorWin::getImg3(QImage img)
{
    img3 = img;
    this->update();
}

void MonitorWin::getImg4(QImage img)
{
    img4 = img;
    this->update();
}

