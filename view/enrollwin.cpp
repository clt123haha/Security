#include "enrollwin.h"


EnrollWin::EnrollWin(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("注册界面");
    this->setWindowIcon(QIcon(":/img/fly.png"));
    this->resize(700,500);
    this->initContorl();
    userController = UserController::getUserController();
    pwd_cansee = pwd2_cansee = false;
}

void EnrollWin::initContorl()
{

    QFont ft;
    ft.setPointSize(14);
    title = new QLabel("注册",this);
    title->setGeometry(350,50,100,30);
    title->setFont(ft);


    this->label1 = new QLabel("账号:",this);
    this->label1->setGeometry(175,100,100,30);

    this->edit1 = new QLineEdit(this);
    this->edit1->setMaxLength(8);
    this->edit1->setGeometry(375,100,200,30);

    label2 = new QLabel("昵称",this);
    label2->setGeometry(175,175,100,30);
    edit2 = new QLineEdit(this);
    edit2->setGeometry(375,175,200,30);


    label3 = new QLabel("密码",this);
    label3->setGeometry(175,250,100,30);
    edit3 = new QLineEdit(this);
    this->edit3->setMaxLength(8);
    edit3->setGeometry(375,250,200,30);
    edit3->setEchoMode(QLineEdit::Password);
    eyebun1 = new QPushButton(this);
    eyebun1->setAutoRepeat(true);
    eyebun1->setAutoRepeatDelay(400);
    eyebun1->setAutoRepeatInterval(50);
    eyebun1->setIcon(QPixmap(":/img/eye.png"));
    eyebun1->setGeometry(575,250,30,30);

    label4 = new QLabel("重复密码",this);
    label4->setGeometry(175,325,100,30);
    edit4 = new QLineEdit(this);
    this->edit4->setMaxLength(8);
    edit4->setEchoMode(QLineEdit::Password);
    edit4->setGeometry(375,325,200,30);
    eyebun2 = new QPushButton(this);
    eyebun2->setIcon(QPixmap(":/img/eye.png"));
    eyebun2->setGeometry(575,325,30,30);

    enrollBun = new QPushButton("确定",this);
    enrollBun->setGeometry(175,400,100,30);
    backtologinBun = new QPushButton("取消",this);
    backtologinBun->setGeometry(375,400,100,30);

    connect(eyebun1,SIGNAL(clicked()),this,SLOT(changePwdStaus()));
    connect(eyebun2,SIGNAL(clicked()),this,SLOT(changePwd2Staus()));
    connect(backtologinBun,SIGNAL(clicked()),this,SLOT(sendBack()));
    connect(enrollBun,SIGNAL(clicked()),this,SLOT(doEroll()));
    connect(edit1,SIGNAL(returnPressed()),this,SLOT(doEroll()));
    connect(edit2,SIGNAL(returnPressed()),this,SLOT(doEroll()));
    connect(edit3,SIGNAL(returnPressed()),this,SLOT(doEroll()));
    connect(edit4,SIGNAL(returnPressed()),this,SLOT(doEroll()));
}

void EnrollWin::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/img/background.jpg"));
}

void EnrollWin::closeEvent(QCloseEvent *e)
{
    emit back();
}

void EnrollWin::changePwdStaus()
{
    if(pwd_cansee)
        edit3->setEchoMode(QLineEdit::Password);
    else
        edit3->setEchoMode(QLineEdit::Normal);
    pwd_cansee = !pwd_cansee;
}

void EnrollWin::changePwd2Staus()
{
    if(pwd2_cansee)
        edit4->setEchoMode(QLineEdit::Password);
    else
        edit4->setEchoMode(QLineEdit::Normal);
    pwd2_cansee = !pwd2_cansee;
}

void EnrollWin::sendBack()
{
    emit back();
}

void EnrollWin::doEroll()
{
    if(edit1->text() == "" || edit2->text() == "" || edit3->text() == "" || edit4->text() == "")
    {
        QMessageBox::information(this,"提示","信息不可为空");
        return;
    }
    if(edit3->text() != edit4->text())
    {
        QMessageBox::information(this,"提示","两次密码不相同");
        return;
    }
    QRegExp regex("^[A-Za-z0-9]{6,10}$");

    if (!regex.exactMatch(edit3->text()))
    {
        QMessageBox::information(this,"提示","密码只能包含数字和字母且长度在六到十位");
        return;
    }
    int res = userController->enroll(edit1->text(),edit2->text(),QCryptographicHash::hash(edit3->text().toLatin1(),QCryptographicHash::Md5).toHex());
    if(res == 0)
    {
        QMessageBox::information(this,"提示","注册成功");
        emit back();
    }
    else {
        QMessageBox::information(this,"提示","注册失败，请尝试更换账号");
    }

}
