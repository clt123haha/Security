#include "loginwin.h"

LoginWin::LoginWin(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("登录界面");
    this->setWindowIcon(QIcon(":/img/fly.png"));
    this->resize(700,500);
    enrollwin = new EnrollWin;
    pwd_cansee = false;
    user = UserController::getUserController();
    this->initContorl();
}

void LoginWin::initContorl()
{

    QFont ft;
    ft.setPointSize(14);
    title = new QLabel("登录",this);
    title->setGeometry(350,50,100,30);
    title->setFont(ft);

    this->myVeritf = new VerificationCodeLabel(this);


    this->label1 = new QLabel("账号:",this);
    this->label1->setGeometry(175,100,100,30);

    this->edit1 = new QLineEdit(this);
    this->edit1->setMaxLength(8);
    this->edit1->setGeometry(425,100,100,30);

    label2 = new QLabel("密码",this);
    label2->setGeometry(175,200,100,30);
    edit2 = new QLineEdit(this);
    this->edit2->setEchoMode(QLineEdit::Password);
    this->edit2->setMaxLength(8);
    edit2->setGeometry(425,200,100,30);
    eyebun = new QPushButton(this);
    eyebun->setAutoRepeat(true);
    eyebun->setAutoRepeatDelay(400);
    eyebun->setAutoRepeatInterval(50);
    eyebun->setIcon(QPixmap(":/img/eye.png"));
    eyebun->setGeometry(525,200,30,30);


    label3 = new QLabel("验证码",this);
    label3->setGeometry(175,300,100,30);
    edit3 = new QLineEdit(this);
    this->edit3->setMaxLength(8);
    edit3->setGeometry(250,300,100,30);
    myVeritf->setGeometry(400,300,200,50);

    loginBun = new QPushButton("登录",this);
    loginBun->setGeometry(175,400,100,30);
    enrollBun = new QPushButton("注册",this);
    enrollBun->setGeometry(425,400,100,30);

    connect(loginBun,SIGNAL(clicked()),this,SLOT(login()));
    connect(enrollBun,SIGNAL(clicked()),this,SLOT(openEnrollWin()));
    connect(enrollwin,SIGNAL(back()),this,SLOT(closeEnrollWin()));
    connect(eyebun,SIGNAL(clicked()),this,SLOT(changePwdStaus()));
    connect(edit1,SIGNAL(returnPressed()),this,SLOT(login()));
    connect(edit2,SIGNAL(returnPressed()),this,SLOT(login()));
    connect(edit3,SIGNAL(returnPressed()),this,SLOT(login()));
}

void LoginWin::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/img/background.jpg"));
}

void LoginWin::closeEvent(QCloseEvent *e)
{
    emit backtoMain();
}

void LoginWin::login()
{
    if(edit1->text() == "" || edit2->text() == "" || edit3->text() == "")
    {
        QMessageBox::information(this,"提示","信息不可为空");
        return;
    }
    if(edit3->text().toLower() != myVeritf->getVerificationCode().toLower())
    {
        QMessageBox::information(this,"提示","验证码错误");
        return;
    }
    QList<QString> res = user->login(edit1->text(),QCryptographicHash::hash(edit2->text().toLatin1(),QCryptographicHash::Md5).toHex());
    if(res.size()==0)
    {
        QMessageBox::information(this,"提示","账号或密码不正确”");
    }
    else {
        emit getUid(res.at(1).toInt());
        emit doLogin(res.at(0));
    }
}

void LoginWin::openEnrollWin()
{
    enrollwin->show();
    this->hide();
}

void LoginWin::closeEnrollWin()
{
    enrollwin->hide();
    this->show();
}

void LoginWin::changePwdStaus()
{
    if(pwd_cansee)
        edit2->setEchoMode(QLineEdit::Password);
    else
        edit2->setEchoMode(QLineEdit::Normal);
    pwd_cansee = !pwd_cansee;
}

