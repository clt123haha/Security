#ifndef PlayThread_H
#define PlayThread_H

#include <QThread>


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
#include <QImage>



class PlayThread : public QThread
{
    Q_OBJECT
public:
    PlayThread();
    void run();
    //准备工作
    int getReady();
    QString getPath() const;
    void setPath(const QString &value);
    int openVideo();
    int findStream();
    int openDcodec();

    bool getPuase() const;
    void setPuase(bool value);

    int getWaitTime() const;
    void setWaitTime(int value);

    void setEnd(bool value);
    int getNum();
    void setTarget(int value);

private:

    bool end;
    bool puase;
    int waitTime,target;
    QString path;
    AVFormatContext *pFormatContext;
    int videoStreamIndex;
    AVCodec * decode;
    AVPacket *avpacket;
    AVCodecContext *CodecContext;
    AVFrame *picture,*pictureRGB;

signals:
    void change(QImage img);
    void addNum(int i);
};

#endif // PlayThread_H
