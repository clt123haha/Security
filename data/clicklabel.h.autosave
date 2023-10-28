#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "controller/imgcontroller.h"
#include <QApplication>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(int labelId, QWidget *parent = nullptr);
    void setW(int value);
    void setH(int value);

signals:
    void labelClicked(int labelId);
    void labelClickedTwice(int labelId);

public slots:
    void changeImg(QImage img);
    void saveImg(QString path,int uid);

protected:
    void mousePressEvent(QMouseEvent *event); // 鼠标按压事件
    void mouseDoubleClickEvent(QMouseEvent *event); // 鼠标双击事件

private:
    int m_labelId,w,h;
    QImage img;
};

#endif
