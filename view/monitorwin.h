#ifndef MONITORWIN_H
#define MONITORWIN_H

#include <QWidget>
#include <QDebug>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QTimer>
#include <QDir>
#include <QMessageBox>
#include <QGridLayout>
#include <QCameraInfo>
#include "data/clicklabel.h"
#include "data/decodingthread.h"
#include "controller/setcontroller.h"
#include <QSignalMapper>
#include "controller/logcontroller.h"

class MonitorWin : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorWin();
    void initContorl();
    //开启摄像头
    void openCamera();
    //改变布局
    int cheakGrid();
    //设置登录状态
    void setIsLogin(bool value);
    //设置uid
    void setUid(int value);
    void paintEvent(QPaintEvent *event);
    //关闭界面时进行视频存储
    void saveVideo();

private:
    int uid,number;
    ClickLabel *camera1,*camera2,*camera3,*camera4;
    QPushButton *onebun,*fourbun,*teakPictureBun;
    QWidget *leftWin,*rightWin,*gridWin,*bunWin;
    QVBoxLayout *leftLayout,*rightLayout;
    QHBoxLayout *bunLayout,*totalLayout;
    QList<QCameraInfo> cameras;
    QGridLayout *gridLayout;
    DecodingThread *th1,*th2,*th3,*th4;
    QImage img1,img2,img3,img4;
    QStringList namelist;
    QString imgpath,videopath;
    bool isLogin;
    QSignalMapper *signalMapper ;
signals:

public slots:
    //改变布局
    void ChangeGrid(int id);
    //改变布局
    void ChangeGridBun(int id);
    //改变布局
    void ChangeGrid();
    //改变布局
    void SeeAllGrid();
    //拍照
    void takingPicture();
    //改变图片信息
    void getImg1(QImage img);
    void getImg2(QImage img);
    void getImg3(QImage img);
    void getImg4(QImage img);

};

#endif // MONITORWIN_H
