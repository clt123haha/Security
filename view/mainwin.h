#ifndef MAINWIN_H
#define MAINWIN_H

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
#include <QStackedWidget>
#include "monitorwin.h"
#include "playbackwin.h"
#include "setwin.h"
#include "controller/setcontroller.h"
#include "loginwin.h"
#include <QCamera>
#include "view/logwin.h"
#include <QMessageBox>

class MainWin : public QWidget
{
    Q_OBJECT
public:
    explicit MainWin(QWidget *parent = nullptr);
    void initContorl();
    //检查设置是否完全
    void cheakSetWin();
    //设置uid
    void setUid(int value);
    //打开摄像头
    void openCamera();
    void closeEvent (QCloseEvent * e);

private:
    bool isLogin;
    int uid;
    QLabel *logo,*title,*timeNow;
    QPushButton *bun1,*bun2,*bun3,*bun4,*helloUser;
    QWidget *upwin,*downwin;
    QVBoxLayout *totalLayout;
    QHBoxLayout *upLayout,*downLayout;
    QTimer *timer;
    QGridLayout *gridLayout;
    QStackedWidget *stack;
    MonitorWin *page1;
    PlaybackWin *page2;
    logWin *page3;
    SetWin *setwin;
    LoginWin *loginwin;

signals:

public slots:
    //关闭登录窗口
    void closeLoginWin();
    //改变时间显示
    void slotCountMessage();
    //改变页面
    void changePage1();
    void changePage2();
    void changePage3();
    void changePage4();
    //登录操作
    void doLogin();
    //改变用户名显示
    void userLogin(QString name);
    //关闭设置界面
    void closeSetWin();
    //改变uid
    void changeUid(int uid);
};

#endif // MAINWIN_H
