#include "imgshowwin.h"


ImgShowWin::ImgShowWin(QWidget *parent) : QWidget(parent)
{
    this->setWindowIcon(QIcon(":/img/fly.png"));
    this->resize(600,480);
    initContorl();
    isMagnify = false;
    count = 0;
    magnifyid = 0;
}

void ImgShowWin::initContorl()
{
    pictureLayout = new QGridLayout;
    totalLayout = new QHBoxLayout;
    messageLayout = new QVBoxLayout;

    picWin = new QWidget;
    mesWin = new QWidget;
    picWin->setStyleSheet("background-color:yellow");
    picWin->setLayout(pictureLayout);
    mesWin->setLayout(messageLayout);

    this->setLayout(totalLayout);
    totalLayout->addWidget(picWin,8);
    totalLayout->addWidget(mesWin,2);


    p1 = new ClickLabel(1);
    p2 = new ClickLabel(2);
    p3 = new ClickLabel(3);
    p4 = new ClickLabel(4);
    p5 = new ClickLabel(5);
    p6 = new ClickLabel(6);
    p7 = new ClickLabel(7);
    p8 = new ClickLabel(8);
    p9 = new ClickLabel(9);

    calendarWidget = new QCalendarWidget;
    calendarBun = new QPushButton("查询");

    messageLayout->addWidget(calendarBun);

    pictureLayout->addWidget(p1,1,0, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    pictureLayout->addWidget(p2,1,1, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    pictureLayout->addWidget(p3,1,2, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    pictureLayout->addWidget(p4,2,0, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    pictureLayout->addWidget(p5,2,1, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    pictureLayout->addWidget(p6,2,2, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    pictureLayout->addWidget(p7,3,0, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    pictureLayout->addWidget(p8,3,1, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);
    pictureLayout->addWidget(p9,3,2, 1, 1, Qt::AlignCenter | Qt::AlignVCenter | Qt::AlignHCenter);

    connect(calendarBun,SIGNAL(clicked()),this,SLOT(showCalendarWidget()));
    connect(calendarWidget,SIGNAL(selectionChanged()),this,SLOT(changedata()));
}

void ImgShowWin::setUid(int value)
{
    uid = value;
}

void ImgShowWin::showPicture()
{
    count = 0;

    imglist = ImgController::getImgController()->getImgList(uid);

    isMagnify = false;

    p1->clear();
    p2->clear();
    p3->clear();
    p4->clear();
    p5->clear();
    p6->clear();
    p7->clear();
    p8->clear();
    p9->clear();

    img1.fill(Qt::yellow);
    img2.fill(Qt::yellow);
    img3.fill(Qt::yellow);
    img4.fill(Qt::yellow);
    img5.fill(Qt::yellow);
    img6.fill(Qt::yellow);
    img7.fill(Qt::yellow);
    img8.fill(Qt::yellow);
    img9.fill(Qt::yellow);

    QLayoutItem* item;
    while ((item = messageLayout->takeAt(1)) != nullptr) {
        delete item->widget();
        delete item;
    }
    int size = imglist.size();
    if(size>0)
    {
        img1 = (imglist.at(0).getImg());
        QString str = imglist.at(0).getPath();
        int lastIndex = str.lastIndexOf("/");
        QString result = str.mid(lastIndex + 1);
        int size = result.size();
        for(int i=10;i<size;i+=10)
        {
            result.insert(i, "\n");
        }
        QLabel *label = new QLabel(result);
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);
        messageLayout->addWidget(label);
        label->setFixedSize(80, 100);
        messageLayout->addWidget(new QLabel(QString("%1\n%2").arg("宽度").arg(QString::number(imglist.at(0).getImg().width()))));
        messageLayout->addWidget(new QLabel(QString("%1:\n%2").arg("长度").arg(QString::number(imglist.at(0).getImg().height()))));
        messageLayout->addWidget(new QLabel(QString("%1:\n%2kb").arg("大小").arg(QString::number(imglist.at(0).getImg().byteCount()/1024/1024))));
    }
    if(size>1)
        img2 = (imglist.at(1).getImg());
    if(size>2)
        img3 = (imglist.at(2).getImg());
    if(size>3)
        img4 = (imglist.at(3).getImg());
    if(size>4)
        img5 = (imglist.at(4).getImg());
    if(size>5)
        img6 = (imglist.at(5).getImg());
    if(size>6)
        img7 = (imglist.at(6).getImg());
    if(size>7)
        img8 = (imglist.at(7).getImg());
    if(size>8)
        img9 = (imglist.at(8).getImg());

    update();

    roll = new QScrollBar(Qt::Horizontal);
    roll->setSingleStep(1);
    int max = size/9;
    if(size%9 == 0)
        max -= 1;
    roll->setMaximum(max);
    roll->setMinimum(0);
    connect(roll,SIGNAL(valueChanged(int)),this,SLOT(changePage(int)));
    connect(p1,SIGNAL(labelClickedTwice(int)),this,SLOT(magnify(int)));
    connect(p2,SIGNAL(labelClickedTwice(int)),this,SLOT(magnify(int)));
    connect(p3,SIGNAL(labelClickedTwice(int)),this,SLOT(magnify(int)));
    connect(p4,SIGNAL(labelClickedTwice(int)),this,SLOT(magnify(int)));
    connect(p5,SIGNAL(labelClickedTwice(int)),this,SLOT(magnify(int)));
    connect(p6,SIGNAL(labelClickedTwice(int)),this,SLOT(magnify(int)));
    connect(p7,SIGNAL(labelClickedTwice(int)),this,SLOT(magnify(int)));
    connect(p8,SIGNAL(labelClickedTwice(int)),this,SLOT(magnify(int)));
    connect(p9,SIGNAL(labelClickedTwice(int)),this,SLOT(magnify(int)));

    connect(p1,SIGNAL(labelClicked(int)),this,SLOT(changeMes(int)));
    connect(p2,SIGNAL(labelClicked(int)),this,SLOT(changeMes(int)));
    connect(p3,SIGNAL(labelClicked(int)),this,SLOT(changeMes(int)));
    connect(p4,SIGNAL(labelClicked(int)),this,SLOT(changeMes(int)));
    connect(p5,SIGNAL(labelClicked(int)),this,SLOT(changeMes(int)));
    connect(p6,SIGNAL(labelClicked(int)),this,SLOT(changeMes(int)));
    connect(p7,SIGNAL(labelClicked(int)),this,SLOT(changeMes(int)));
    connect(p8,SIGNAL(labelClicked(int)),this,SLOT(changeMes(int)));
    connect(p9,SIGNAL(labelClicked(int)),this,SLOT(changeMes(int)));

    pictureLayout->addWidget(roll,4,1);
    roll->setVisible(true);
}

void ImgShowWin::paintEvent(QPaintEvent *event)
{
    ClickLabel* labels[] = { p1, p2, p3, p4, p5, p6, p7, p8, p9 };
    if(magnifyid != 0)
    {
        for(int i=0;i<9;i++)
        {
            if(i == this->magnifyid - 1)
                labels[i]->resize(447,252);
            else
                labels[i]->resize(0,0);
        }
        roll->setVisible(false);
    }
    else {
        for(int i=0;i<9;i++)
        {
                labels[i]->resize(149,84);
        }
        roll->setVisible(true);
    }
    QWidget::paintEvent(event);
    QPainter painter(this);
    if(!img1.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img1);
        p1->setPixmap(pixmap.scaled(p1->size(), Qt::KeepAspectRatio));
    }
    if(!img2.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img2);
        p2->setPixmap(pixmap.scaled(p2->size(), Qt::KeepAspectRatio));
    }
    if(!img3.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img3);
        p3->setPixmap(pixmap.scaled(p3->size(), Qt::KeepAspectRatio));
    }
    if(!img4.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img4);
        p4->setPixmap(pixmap.scaled(p4->size(), Qt::KeepAspectRatio));
    }
    if(!img5.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img5);
        p5->setPixmap(pixmap.scaled(p5->size(), Qt::KeepAspectRatio));
    }
    if(!img6.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img6);
        p6->setPixmap(pixmap.scaled(p6->size(), Qt::KeepAspectRatio));
    }
    if(!img7.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img7);
        p7->setPixmap(pixmap.scaled(p7->size(), Qt::KeepAspectRatio));
    }
    if(!img8.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img8);
        p8->setPixmap(pixmap.scaled(p8->size(), Qt::KeepAspectRatio));
    }
    if(!img9.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(img9);
        p9->setPixmap(pixmap.scaled(p9->size(), Qt::KeepAspectRatio));
    }


}

void ImgShowWin::changePage(int index)
{
    count = index;

    ClickLabel* labels[] = { p1, p2, p3, p4, p5, p6, p7, p8, p9 };

    img1.fill(Qt::yellow);
    img2.fill(Qt::yellow);
    img3.fill(Qt::yellow);
    img4.fill(Qt::yellow);
    img5.fill(Qt::yellow);
    img6.fill(Qt::yellow);
    img7.fill(Qt::yellow);
    img8.fill(Qt::yellow);
    img9.fill(Qt::yellow);

    for (int i = 0; i < 9; ++i) {
        labels[i]->clear();
    }

    QLayoutItem* item;
    while ((item = messageLayout->takeAt(1)) != nullptr) {
        delete item->widget();
        delete item;
    }

    int size = imglist.size();

    if(size>0 + index*9)
    {
        img1 = (imglist.at(0 + index*9).getImg());
        QString str = imglist.at(0).getPath();
        int lastIndex = str.lastIndexOf("/");
        QString result = str.mid(lastIndex + 1);
        int size = result.size();
        for(int i=10;i<size;i+=10)
        {
            result.insert(i, "\n");
        }
        QLabel *label = new QLabel(result);
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);
        messageLayout->addWidget(label);
        label->setFixedSize(80, 100);
        messageLayout->addWidget(new QLabel(QString("%1\n%2").arg("宽度").arg(QString::number(imglist.at(0 + index*9).getImg().width()))));
        messageLayout->addWidget(new QLabel(QString("%1:\n%2").arg("长度").arg(QString::number(imglist.at(0 + index*9).getImg().height()))));
        messageLayout->addWidget(new QLabel(QString("%1:\n%2kb").arg("大小").arg(QString::number(imglist.at(0 + index*9).getImg().byteCount()/1024))));
    }
    if(size>1 + index*9)
        img2 = (imglist.at(1 + index*9).getImg());
    if(size>2 + index*9)
        img3 = (imglist.at(2 + index*9).getImg());
    if(size>3 + index*9)
        img4 = (imglist.at(3 + index*9).getImg());
    if(size>4 + index*9)
        img5 = (imglist.at(4 + index*9).getImg());
    if(size>5 + index*9)
        img6 = (imglist.at(5 + index*9).getImg());
    if(size>6 + index*9)
        img7 = (imglist.at(6 + index*9).getImg());
    if(size>7 + index*9)
        img8 = (imglist.at(7 + index*9).getImg());
    if(size>8 + index*9)
        img9 = (imglist.at(8 + index*9).getImg());
    update();
}

void ImgShowWin::magnify(int index)
{
    ClickLabel* labels[] = { p1, p2, p3, p4, p5, p6, p7, p8, p9 };
    if(!isMagnify)
    {
        for (int i = 0; i < 9; ++i) {
            if(index != i+1)
            {
                labels[i]->setVisible(false);
            }
        }
        roll->setVisible(false);
        magnifyid = index;
    }
    else
    {
        magnifyid = 0;
        for (int i = 0; i < 9; ++i) {
            labels[i]->setVisible(true);
        }
        roll->setVisible(true);
    }
    update();
    isMagnify = !isMagnify;
}

void ImgShowWin::changeMes(int index)
{
    QLayoutItem* item;
    while ((item = messageLayout->takeAt(1)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    QString str = imglist.at(count*9 + index-1).getPath();
    int lastIndex = str.lastIndexOf("/");
    QString result = str.mid(lastIndex + 1);
    int size = result.size();
    for(int i=10;i<size;i+=10)
    {
        result.insert(i, "\n");
    }
    QLabel *label = new QLabel(result);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    messageLayout->addWidget(label);
    label->setFixedSize(80, 100);
    messageLayout->addWidget(new QLabel(QString("%1\n%2").arg("宽度").arg(QString::number(imglist.at(count*9 + index-1).getImg().width()))));
    messageLayout->addWidget(new QLabel(QString("%1:\n%2").arg("长度").arg(QString::number(imglist.at(count*9 + index-1).getImg().height()))));
    messageLayout->addWidget(new QLabel(QString("%1:\n%2kb").arg("大小").arg(QString::number(imglist.at(count*9 + index-1).getImg().byteCount()/1024))));
}

void ImgShowWin::showCalendarWidget()
{
    calendarWidget->show();
}

void ImgShowWin::changedata()
{
    calendarWidget->hide();
    QString timeselect = calendarWidget->selectedDate().toString("yyyyMMdd");
    updateImg(timeselect);

}

void ImgShowWin::updateImg(QString time)
{
    count = 0;
    isMagnify = false;
    magnifyid = 0;

    p1->clear();
    p2->clear();
    p3->clear();
    p4->clear();
    p5->clear();
    p6->clear();
    p7->clear();
    p8->clear();
    p9->clear();

    img1.fill(Qt::yellow);
    img2.fill(Qt::yellow);
    img3.fill(Qt::yellow);
    img4.fill(Qt::yellow);
    img5.fill(Qt::yellow);
    img6.fill(Qt::yellow);
    img7.fill(Qt::yellow);
    img8.fill(Qt::yellow);
    img9.fill(Qt::yellow);

    QLayoutItem* item;
    while ((item = messageLayout->takeAt(1)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QList<Img> imglistTemp = ImgController::getImgController()->getImgList(uid);
    imglist.clear();



    QMutableListIterator<Img> iter(imglistTemp);
    while (iter.hasNext()) {
        const Img& v = iter.next();
        QDateTime creatTime = QDateTime::fromString(v.getCreattime(), "yyyyMMddhhmmss");
        QString creatTimeStr = creatTime.toString("yyyyMMdd");

        if (creatTimeStr >= time)
        {
            imglist.append(v);
        }
    }




    int size  =imglist.size();
    qDebug() << size;
    if(size>0)
    {
        img1 = (imglist.at(0).getImg());
        QString str = imglist.at(0).getPath();
        int lastIndex = str.lastIndexOf("/");
        QString result = str.mid(lastIndex + 1);
        int sizestr = result.size();
        for(int i=10;i<sizestr;i+=10)
        {
            result.insert(i, "\n");
        }
        QLabel *label = new QLabel(result);
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);
        messageLayout->addWidget(label);
        label->setFixedSize(80, 100);
        messageLayout->addWidget(new QLabel(QString("%1\n%2").arg("宽度").arg(QString::number(imglist.at(0).getImg().width()))));
        messageLayout->addWidget(new QLabel(QString("%1:\n%2").arg("长度").arg(QString::number(imglist.at(0).getImg().height()))));
        messageLayout->addWidget(new QLabel(QString("%1:\n%2kb").arg("大小").arg(QString::number(imglist.at(0).getImg().byteCount()/1024/1024))));
    }
    if(size>1)
        img2 = (imglist.at(1).getImg());
    if(size>2)
        img3 = (imglist.at(2).getImg());
    if(size>3)
        img4 = (imglist.at(3).getImg());
    if(size>4)
        img5 = (imglist.at(4).getImg());
    if(size>5)
        img6 = (imglist.at(5).getImg());
    if(size>6)
        img7 = (imglist.at(6).getImg());
    if(size>7)
        img8 = (imglist.at(7).getImg());
    if(size>8)
        img9 = (imglist.at(8).getImg());

    update();


    int max = size/9;
    if(size%9 == 0&&max>0)
        max -= 1;
    roll->setMaximum(max);
}
