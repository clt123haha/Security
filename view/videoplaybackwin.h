#ifndef VIDEOPLAYBACKWIN_H
#define VIDEOPLAYBACKWIN_H

#include <QObject>
#include <QWidget>
#include "data/clicklabel.h"
#include "data/video.h"
#include <QHBoxLayout>
#include <QPushButton>
#include "controller/videocontroller.h"
#include <QCalendarWidget>
#include "player.h"
#include <QFileInfo>
#include <QIcon>
#include <QMessageBox>

class VideoPlaybackWin : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlaybackWin(QWidget *parent = nullptr);
    //初始化控件
    void initContorl();
    //加载视频相关信息，并且加载到窗口上
    void initVideoMes();
    //依据时间更新数据
    void updateVideoMes(QString time);
    //设置uid
    void setUid(int value);

private:

    ClickLabel *img1,*img2,*img3,*img4;
    QLabel *mes1,*mes2,*mes3;
    QList<video> videoList;
    int index,uid,count,indexnow;
    QVBoxLayout *mesLayout;
    QHBoxLayout *totalLayout,*rowLayout1,*rowLayout2,*rowLayout3,*rowLayout4;
    QPushButton *search,*one,*two,*three;
    QWidget *mesWin;
    QCalendarWidget * calendarWidget;
    Player *player;

signals:

public slots:
    //关闭播放窗口
    void closePlayer();
    //翻页
    void back();
    //翻页
    void forward();
    //翻页
    void forward2();
    //获得选择的时间，刷新数据
    void changedata();
    //切换左侧图片
    void changeIndex(int i);
    void palyVideo();
    //显示日历
    void showCalendarWidget();
    //上一个视频
    void videoUpOne();
    //下一个视频
    void videoDownOne();
};

#endif // VIDEOPLAYBACKWIN_H
