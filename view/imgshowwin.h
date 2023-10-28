#ifndef IMGSHOWWIN_H
#define IMGSHOWWIN_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "data/img.h"
#include <QPixmap>
#include <QScrollBar>
#include <QCalendarWidget>
#include "data/clicklabel.h"
#include <QPushButton>
#include "controller/imgcontroller.h"
#include <QIcon>


class ImgShowWin : public QWidget
{
    Q_OBJECT
public:
    explicit ImgShowWin(QWidget *parent = nullptr);
    void initContorl();
    void setUid(int value);
    //刷新图片信息，加载到窗口
    void showPicture();
    void paintEvent(QPaintEvent *event);

private:
    QWidget *picWin,*mesWin;
    QGridLayout *pictureLayout;
    QVBoxLayout *messageLayout;
    QHBoxLayout *totalLayout;
    QCalendarWidget *calendarWidget;
    QList<Img> imglist;
    int uid,count,magnifyid;
    QPushButton *calendarBun;
    ClickLabel *p1,*p2,*p3,*p4,*p5,*p6,*p7,*p8,*p9;
    QImage img1,img2,img3,img4,img5,img6,img7,img8,img9;
    QScrollBar *roll;
    bool isMagnify;

signals:

public slots:
    //改变页数
    void changePage(int index);
    //放大/缩小
    void magnify(int index);
    //改变信息显示
    void changeMes(int index);
    //日历显示
    void showCalendarWidget();
    //改变时间，隐藏日历
    void changedata();
    //改变信息（依据选择的时间）
    void updateImg(QString time);
};

#endif // IMGSHOWWIN_H
