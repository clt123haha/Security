#ifndef PLAYER_H
#define PLAYER_H

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "data/playthreah.h"
#include <QImage>
#include "data/turn.h"
#include <QComboBox>
#include <QPushButton>
#include "data/savepicthreadh.h"
#include "controller/imgcontroller.h"
#include <QScrollBar>
#include "controller/setcontroller.h"
#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>
#include "controller/logcontroller.h"
#include "controller/setcontroller.h"
class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = nullptr);
    void initContorl();
    //播放视频
    void play();
    void paintEvent(QPaintEvent *event);
    ~Player();
    //设置存储路径
    void setPath(const QString &value);
    //设置标题
    void setTitle(const QString &value);
    //设置uid
    void setUid(int value);
    //点击x号触发事件
    void closeEvent (QCloseEvent * e);
    //设置视频是否结束
    void setEnd(bool value);
    void setTime(int value);

private:
    QString path,title,imgsavePath;
    bool ifpuase = false;
    QLabel *label,*label1,*label3,*label4,*label5,*label6,*label7,*label8,*label9,*label10,*label11,*label12,*label13;
    QPushButton *bun1,*backbun,*getVideoBun,*takePicBun,*upBun,*downBun;
    QComboBox *combobox1,*combobox2;
    QImage img;
    PlayThread *th;
    QVBoxLayout *totalLayout;
    QHBoxLayout *down,*up,*mid;
    QWidget *w1,*w2,*w3;
    turn *turnTh;
    int uid;
    QScrollBar *scrollBar;
    savePicThreadh *saveTh;
    int num,time;

public slots:
    //更新图片
    void changeImage(QImage img);
    //暂停/开始
    void puase();
    //改变播放速度
    void changeSpead(int index);
    //关闭视频播放窗口
    void backto();
    //转码
    void turnVideo();
    //截图
    void takePic();
    //得到正在播放的帧数
    void getNum(int i);
    //改变需要播放到的帧数
    void changeNum(int i);
    //上一个视频
    void sendupone();
    //下一个视频
    void senddownone();


signals:
    void upone();
    void downone();
    void back();
};

#endif // PLAYER_H
