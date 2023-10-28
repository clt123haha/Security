#ifndef SAVEPICTHREADH_H
#define SAVEPICTHREADH_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QImage>
#include <QDateTime>
#include <QDir>
#include "controller/imgcontroller.h"

class savePicThreadh : public QThread
{
    Q_OBJECT
public:
    savePicThreadh();
    //保存图片
    void setImg(const QImage &value);
    //设置图片路径
    void setPath(const QString &value);
    void run();
    void setUid(int value);

private:
    QImage img;
    QString path;
    int uid;
};

#endif // SAVEPICTHREADH_H
