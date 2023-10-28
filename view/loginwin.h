#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include "data/VerificationCodeLabel.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCryptographicHash>
#include "enrollwin.h"
#include "controller/usercontroller.h"

class LoginWin : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWin(QWidget *parent = nullptr);
    void initContorl();
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *e);

private:
    EnrollWin *enrollwin;
    VerificationCodeLabel *myVeritf;
    QLabel *label1,*label2,*label3,*title;
    QLineEdit *edit1,*edit2,*edit3;
    QPushButton *loginBun,*enrollBun,*eyebun;
    UserController *user;
    bool pwd_cansee;

signals:
    void getUid(int uid);
    void doLogin(QString name);
    void doLogin();
    void backtoMain();

public slots:
    void login();
    void openEnrollWin();
    void closeEnrollWin();
    void changePwdStaus();
};

#endif // LOGINWIN_H
