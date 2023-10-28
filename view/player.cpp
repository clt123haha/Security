#include "player.h"

#include <QImageWriter>

Player::Player(QWidget *parent) : QWidget(parent)
{
    this->resize(600,400);
    this->initContorl();
    turnTh = new turn;
    saveTh = new savePicThreadh;
}

void Player::initContorl()
{
    w1 = new QWidget;
    w2 = new QWidget;
    w3 = new QWidget;
    scrollBar = new QScrollBar(Qt::Horizontal);
    scrollBar->setSingleStep(1);
    scrollBar->setMinimum(0);
    totalLayout = new QVBoxLayout;
    this->setLayout(totalLayout);
    totalLayout->addWidget(w1,1);
    totalLayout->addWidget(w2,8);
    totalLayout->addWidget(scrollBar,1);
    totalLayout->addWidget(w3,1);
    up = new QHBoxLayout;
    down = new QHBoxLayout;
    mid = new QHBoxLayout;
    w1->setLayout(up);
    w2->setStyleSheet("background-color:yellow");
    w3->setLayout(down);
    backbun = new QPushButton("back");
    up->addWidget(backbun);
    up->addStretch(1);

    label = new QLabel;
    w2->setLayout(mid);
    mid->addWidget(label);
    label->setScaledContents(true);
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);


    bun1 = new QPushButton("暂停");
    combobox1 = new QComboBox();
    combobox1->addItem("1.0px");
    combobox1->addItem("1.25px");
    combobox1->addItem("1.5px");
    combobox1->addItem("2.0px");
    combobox2 = new QComboBox;
    combobox2->addItems({"mp4","flv","wmv"});
    getVideoBun = new QPushButton("导出");
    takePicBun = new QPushButton("拍照");
    upBun = new QPushButton;
    downBun = new QPushButton;
    upBun->setIcon(QIcon(":/img/up.png").pixmap(QSize(30, 30)));
    downBun->setIcon(QIcon(":/img/down.png").pixmap(QSize(30, 30)));
    down->addWidget(bun1);
    down->addWidget(combobox1);
    down->addWidget(combobox2);
    down->addWidget(getVideoBun);
    down->addWidget(takePicBun);
    down->addWidget(upBun);
    down->addWidget(downBun);

    connect(scrollBar,SIGNAL(valueChanged(int)),this,SLOT(changeNum(int)));
    connect(this->bun1,SIGNAL(clicked()),this,SLOT(puase()));
    connect(this->backbun,SIGNAL(clicked()),this,SLOT(backto()));
    connect(this->takePicBun,SIGNAL(clicked()),this,SLOT(takePic()));
    connect(this->upBun,SIGNAL(clicked()),this,SLOT(sendupone()));
    connect(this->downBun,SIGNAL(clicked()),this,SLOT(senddownone()));
    connect(this->combobox1,SIGNAL(currentIndexChanged(int)),this,SLOT(changeSpead(int)));
    connect(this->getVideoBun,SIGNAL(clicked()),this,SLOT(turnVideo()));

}

void Player::play()
{
    combobox1->setCurrentIndex(0);
    combobox2->setCurrentIndex(0);
    imgsavePath = SetController::getSetController()->cheakRow().at(1);
    this->th = new PlayThread();
    ifpuase = false;
    this->bun1->setText("暂停");
    th->setPuase(true);

    connect(this->th,SIGNAL(change(QImage)),this,SLOT(changeImage(QImage)));
    connect(this->th,SIGNAL(addNum(int)),this,SLOT(getNum(int)));

    th->setPath(path.toUtf8());
    if(th->getReady() != 0)
    {
        QMessageBox::information(this,"提示","视频无法播放");
        return;
    }
    scrollBar->setMaximum(time);
    th->setPuase(false);
    th->start();
}

void Player::paintEvent(QPaintEvent *event)
{
    if(!this->img.isNull())
    {
        label->setPixmap(QPixmap::fromImage(img).scaled(this->label->size()));
        label->setScaledContents(true);
        label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }

}

Player::~Player()
{
    th->setEnd(true);
}

void Player::setPath(const QString &value)
{
    path = value;
}

void Player::setTitle(const QString &value)
{
    title = value;
    this->setWindowTitle(value);
}

void Player::setUid(int value)
{
    uid = value;
}

void Player::closeEvent(QCloseEvent *e)
{
    th->setEnd(true);
}

void Player::setEnd(bool value)
{
    th->setEnd(value);
}

void Player::setTime(int value)
{
    time = value;
}



void Player::changeImage(QImage img)
{
    if(!img.isNull())
    {
        this->img = img;
        this->update(); // 刷新界面（可选）
    }



}

void Player::puase()
{
    if(ifpuase == true){
        ifpuase = false;
        this->bun1->setText("暂停");
        th->setPuase(false);
    }
    else {
        ifpuase = true;
        this->bun1->setText("开始");
        th->setPuase(true);
    }
}

void Player::changeSpead(int index)
{
    int spead = 40 - 10*index;
    th->setWaitTime(spead);
}

void Player::backto()
{
    emit back();
}

void Player::turnVideo()
{
    QString format = combobox2->currentText();
    QRegExp rx("\\b(\\d{14})\\b");
    int pos = rx.indexIn(path);
    QString videoPath = SetController::getSetController()->cheakRow()[0];
    QString path2 = QString("%1/turn/%2.%3").arg(videoPath).arg(rx.cap(1)).arg(format);
    QString path2_ = QString("%1/turn").arg(videoPath);

    QDir dir(path2_);
    if (!dir.exists())
        dir.mkpath(path2_);

    qDebug() << path2;

    turnTh->setFilename(path);
    turnTh->setSavepath(path2);
    turnTh->getReady();
    turnTh->turnVideo();

    logController::getlogController()->creatLog(uid,"视频转码");

    QMessageBox::information(this,"提示","转码成功");

}

void Player::takePic()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyyMMddhhmmss");
    QString imgPath_ = QString("%1/%2").arg(imgsavePath).arg(title);

    QDir dir(imgPath_);
    if (!dir.exists())
        dir.mkpath(imgPath_);


    QString imgPath = QString("%1/%2.jpg").arg(imgPath_).arg(formattedDateTime);

    QImageWriter writer(imgPath);
    writer.write(img);
    ImgController::getImgController()->creatImg(imgPath,uid);
    logController::getlogController()->creatLog(uid,"截图");
    QMessageBox::information(this,"提示","截图成功");
}

void Player::getNum(int i)
{
    scrollBar->setValue(i);
    num = i;
}

void Player::changeNum(int i)
{
    th->setTarget(i);
    if(num > i)
    {
        disconnect(this->th,SIGNAL(change(QImage)),this,SLOT(changeImage(QImage)));
        disconnect(this->th,SIGNAL(addNum(int)),this,SLOT(getNum(int)));
        th->setEnd(true);
        th = new PlayThread;
        connect(this->th,SIGNAL(change(QImage)),this,SLOT(changeImage(QImage)));
        connect(this->th,SIGNAL(addNum(int)),this,SLOT(getNum(int)));
        th->setPath(path);
        th->getReady();
        th->setTarget(i);
        th->start();
    }
}

void Player::sendupone()
{
    scrollBar->setValue(0);
    combobox1->setCurrentIndex(0);
    combobox2->setCurrentIndex(0);
    ifpuase = false;
    this->bun1->setText("暂停");
    emit upone();
}

void Player::senddownone()
{
    scrollBar->setValue(0);
    combobox1->setCurrentIndex(0);
    combobox2->setCurrentIndex(0);
    ifpuase = false;
    this->bun1->setText("暂停");
    emit downone();
}
