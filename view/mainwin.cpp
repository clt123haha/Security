#include "mainwin.h"

MainWin::MainWin(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("主界面");
    this->setWindowIcon(QIcon(":/img/fly.png"));
    this->resize(700,500);
    this->initContorl();
    isLogin = false;
}

void MainWin::initContorl()
{

    setwin = new SetWin;
    loginwin = new LoginWin;
    upwin = new QWidget;
    upwin->setStyleSheet("background-color:yellow");
    downwin = new QWidget;
    downwin->setStyleSheet("background-color:grey");
    downLayout = new QHBoxLayout;
    downwin->setLayout(downLayout);
    totalLayout = new QVBoxLayout;
    this->setLayout(totalLayout);
    totalLayout->addWidget(upwin,1);
    totalLayout->addWidget(downwin,8);

    upLayout = new QHBoxLayout;
    upwin->setLayout(upLayout);
    logo = new QLabel;
    logo->setPixmap(QPixmap(":/img/logo.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    upLayout->addWidget(logo);
    title = new QLabel("超级安保系统");
    upLayout->addWidget(title);
    bun1 = new QPushButton("监控模式");
    bun2 = new QPushButton("回放模式");
    bun3 = new QPushButton("日志查询");
    bun4 = new QPushButton("系统设置");
    upLayout->addWidget(bun1);
    upLayout->addWidget(bun2);
    upLayout->addWidget(bun3);
    upLayout->addWidget(bun4);
    helloUser = new QPushButton("未登录");
    upLayout->addWidget(helloUser);
    timeNow = new QLabel;
    upLayout->addWidget(timeNow);
    timer = new QTimer(this);
    timer->start(1000);

    stack = new QStackedWidget;
    downLayout->addWidget(stack);

    page1 = new MonitorWin;
    stack->addWidget(page1);
    page2 = new PlaybackWin;
    stack->addWidget(page2);
    page3 = new logWin;
    stack->addWidget(page3);


    connect(timer, SIGNAL(timeout()), this, SLOT(slotCountMessage()));
    connect(bun1, SIGNAL(clicked()), this, SLOT(changePage1()));
    connect(bun2, SIGNAL(clicked()), this, SLOT(changePage2()));
    connect(bun3, SIGNAL(clicked()), this, SLOT(changePage3()));
    connect(bun4, SIGNAL(clicked()), this, SLOT(changePage4()));
    connect(helloUser, SIGNAL(clicked()), this, SLOT(doLogin()));
    connect(loginwin, SIGNAL(doLogin(QString)), this, SLOT(userLogin(QString)));
    connect(setwin, SIGNAL(down()), this, SLOT(closeSetWin()));
    connect(setwin, SIGNAL(notDo()), this, SLOT(closeSetWin()));
    connect(loginwin, SIGNAL(getUid(int)), this, SLOT(changeUid(int)));
    connect(loginwin, SIGNAL(backtoMain()), this, SLOT(closeLoginWin()));
}

void MainWin::cheakSetWin()
{
    QList<QString> list = SetController::getSetController()->cheakRow();
    int res = 1;
    bool allDevicesAvailable = true;
    if(list.size()>0)
    {
        QDir dir1(list.at(0));
        if (!dir1.exists())
            res = 0;
        QDir dir2(list.at(1));
        if (!dir2.exists())
            res = 0;
        if(list.at(2) == "")
            res = 0;

        QStringList strList = list.at(3).split(";", QString::SkipEmptyParts);

        QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

        for (const QString& deviceName : strList) {
            bool deviceAvailable = false;

            for (const QCameraInfo& camera : cameras) {
                if (camera.description() == deviceName) {
                    deviceAvailable = true;
                    break;
                }
            }

            if (!deviceAvailable) {
                allDevicesAvailable = false;
                qDebug() << "Camera device" << deviceName << "is not available.";
                break;
            }
        }
    }


    if(list.size() == 0 || res == 0 || !allDevicesAvailable)
    {
        this->hide();
        setwin->show();
    }
    else {
        this->show();
        this->openCamera();
    }
}

void MainWin::setUid(int value)
{
    uid = value;
}

void MainWin::openCamera()
{
    page1->openCamera();
}

void MainWin::closeEvent(QCloseEvent *e)
{
    page1->saveVideo();
}


void MainWin::closeLoginWin()
{
    this->show();
    loginwin->hide();
}


void MainWin::slotCountMessage()
{
    this->timeNow->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
}

void MainWin::changePage1()
{
    stack->setCurrentIndex(0);
}

void MainWin::changePage2()
{
    if(isLogin)
        stack->setCurrentIndex(1);
    else {
        QMessageBox::information(this,"提示","未登录");
        doLogin();
    }
}

void MainWin::changePage3()
{
    if(isLogin)
    {
        page3->changeData();
        stack->setCurrentIndex(2);
    }
    else {
        QMessageBox::information(this,"提示","未登录");
        doLogin();
    }
}

void MainWin::changePage4()
{
    setwin->show();
}

void MainWin::doLogin()
{
    if(!isLogin)
    {
        loginwin->show();
        this->hide();
    }
    else
    {
        helloUser->setText("请登录");
        isLogin = false;
    }


}

void MainWin::userLogin(QString name)
{
    helloUser->setText(name);
    loginwin->hide();
    this->show();
    page1->setIsLogin(true);
    isLogin = true;
}

void MainWin::closeSetWin()
{
    if(!isLogin)
    {
        this->setwin->hide();
        this->show();
        this->openCamera();
    }
    else {
        this->setwin->hide();
    }
}

void MainWin::changeUid(int uid)
{
    this->uid = uid;
    page1->setUid(uid);
    page2->setUid(uid);
}
