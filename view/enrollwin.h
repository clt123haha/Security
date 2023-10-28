#ifndef ENROLLWIN_H
#define ENROLLWIN_H

#include <QLabel>
#include <QLineEdit>
#include <QIcon>
#include <QMessageBox>
#include <QPainter>
#include <QPushButton>
#include <QWidget>
#include "controller/usercontroller.h"
#include <QCryptographicHash>

class EnrollWin : public QWidget
{
    Q_OBJECT
public:
    explicit EnrollWin(QWidget *parent = nullptr);
    void initContorl();
    void paintEvent(QPaintEvent *event);
    void closeEvent (QCloseEvent * e);

private:
    QLabel *label1,*label2,*label3,*label4,*title;
    QLineEdit *edit1,*edit2,*edit3,*edit4;
    QPushButton *backtologinBun,*enrollBun,*eyebun1,*eyebun2;
    bool pwd_cansee,pwd2_cansee;
    UserController *userController;
signals:
    //返回登录界面
    void back();

public slots:
    //改变可见状态
    void changePwdStaus();
    void changePwd2Staus();
    //发送back（)
    void sendBack();
    //注册操作
    void doEroll();
};

#endif // ENROLLWIN_H
