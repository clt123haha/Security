#include "setwin.h"

SetWin::SetWin(QWidget *parent) : QWidget(parent)
{
    videoPath = "";
    imgPath = "";
    cameras = QCameraInfo::availableCameras();
    this->setWindowTitle("设置界面");
    this->setWindowIcon(QIcon(":/img/fly.png"));
    this->resize(500,500);
    mySetController = SetController::getSetController();
    this->initContorl();
}

void SetWin::initContorl()
{
    msgBox = new QMessageBox;
    msgBox->setText("确定设置信息吗");

    confirmButton = msgBox->addButton("确认",QMessageBox::RejectRole);
    confirmButton->setObjectName("confirmButton");

    cancelButton = msgBox->addButton("取消", QMessageBox::RejectRole);
    cancelButton->setObjectName("cancelButton");


    QFont ft;
    ft.setPointSize(14);
    title = new QLabel("设置界面",this);
    title->setFont(ft);
    title->setGeometry(200,30,100,50);

    bun1 = new QPushButton("...",this);
    bun1->setGeometry(400,100,50,30);

    edit1 = new QLineEdit(this);
    edit1->setReadOnly(true);
    edit1->setGeometry(150,100,200,30);

    label1 = new QLabel("视频存储位置",this);
    label1->setGeometry(40,100,100,30);

    bun2 = new QPushButton("...",this);
    bun2->setGeometry(400,175,50,30);

    edit2 = new QLineEdit(this);
    edit2->setReadOnly(true);
    edit2->setGeometry(150,175,200,30);

    label2 = new QLabel("图片存储位置",this);
    label2->setGeometry(40,175,100,30);


    label3 = new QLabel("时间间隔",this);
    label3->setGeometry(40,250,200,30);
    timeList = new QComboBox(this);
    char temp[255];
    for(int i=1;i<11;i++)
    {
        sprintf(temp,"%d分钟",i);
        timeList->addItem(temp);
    }
    timeList->setGeometry(150,250,200,30);


    label4 = new QLabel("摄像头配置",this);
    label4->setGeometry(40,325,200,30);

     cameraNameList = new CCheckCombox(this);

    foreach (const QCameraInfo &cameraInfo, cameras) {
        cameraNameList->addCheckableItem(cameraInfo.description(),false);
    }

    cameraNameList->setGeometry(150,325,200,30);

    PinBun = new QPushButton("确定",this);
    PinBun->setGeometry(100,400,50,30);
    CancelBun = new QPushButton("取消",this);
    CancelBun->setGeometry(300,400,50,30);


    connect(bun1,SIGNAL(clicked()),this,SLOT(changeVideoPath()));
    connect(bun2,SIGNAL(clicked()),this,SLOT(changeImgPath()));
    connect(PinBun,SIGNAL(clicked()),this,SLOT(openMsgBox()));
    connect(confirmButton,SIGNAL(clicked()),this,SLOT(updateSet()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(closeMsgBox()));
    connect(CancelBun,SIGNAL(clicked()),this,SLOT(Cansel()));
}

void SetWin::changeVideoPath()
{
    videoPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), "../");
    edit1->setText(videoPath);
}

void SetWin::changeImgPath()
{
    imgPath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), "../");
    edit2->setText(imgPath);
}

void SetWin::updateSet()
{
    if(edit1->text() == "" || edit2->text() == "")
    {
        QMessageBox::information(this,"提示","信息不可为空");
        return;
    }
   QStringList strList = cameraNameList->currentText().split(";", QString::SkipEmptyParts);
   if(strList.size() > 4)
   {
       QMessageBox::information(this,"提示","摄像头数量不能大于4");
       return;
   }
    int res = mySetController->SetStatus(edit1->text(),edit2->text(),QString::number(timeList->currentIndex()+1),cameraNameList->currentText());
    if(res == 0)
    {
        QMessageBox::information(this,"提示","设置成功，若已在运行，重新启动后生效");
        emit down();
    }
    else
        QMessageBox::information(this,"提示","设置失败");
}

void SetWin::Cansel()
{
    QList<QString> list = SetController::getSetController()->cheakRow();
    if(list.size() > 0)
        emit notDo();
    else {
        QMessageBox::information(this,"提示","请进行设置");
    }
}

void SetWin::openMsgBox()
{
    msgBox->show();
}

void SetWin::closeMsgBox()
{
    msgBox->hide();
}

