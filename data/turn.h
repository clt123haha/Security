#ifndef TURN_H
#define TURN_H

extern "C"{
    #include "libavcodec/avcodec.h"
    #include "libavdevice/avdevice.h"
    #include "libavfilter/avfilter.h"
    #include "libavformat/avformat.h"
    #include "libavutil/avutil.h"
    #include "libswresample/swresample.h"
    #include "libswscale/swscale.h"

}

#include <QDebug>

class turn
{
public:
    turn();
    //转码
    void turnVideo();
    //转码工作
    void getReady();
    //设置文件路径
    void setFilename(const QString &value);
    //设置保存路径
    void setSavepath(const QString &value);

private:
    AVFormatContext *pFormatContext,*opFormatContext;
    AVPacket *pkt;
    AVStream* newstream;
    QString filename,savepath;
    int video_index,count;
};

#endif // TURN_H
