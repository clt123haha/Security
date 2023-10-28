#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include "model/videomodel.h"
#include <QString>
#include "data/video.h"
#include <QDateTime>

class VideoController
{
public:
    int creatVideo(QString path,QString coverPath,QString camera,int fream_count);
    static VideoController * getVideoController();
    QList<video> getVideoList();
private:
    static VideoController * myVideoController;
    VideoController();
};

#endif
// VIDEOCONTROLLER_H
