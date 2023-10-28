#ifndef ENCODETHREAH_H
#define ENCODETHREAH_H

extern "C"{
    #include "libavcodec/avcodec.h"
    #include "libavdevice/avdevice.h"
    #include "libavfilter/avfilter.h"
    #include "libavformat/avformat.h"
    #include "libavutil/avutil.h"
    #include "libswresample/swresample.h"
    #include "libswscale/swscale.h"

}

#include "controller/logcontroller.h"
#include <QDebug>
#include <QString>
#include <QQueue>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include "controller/videocontroller.h"
#include <QDateTime>
#include <QDir>

class EncodeThreah : public QThread
{
    Q_OBJECT
public:
    EncodeThreah();
    void ready();
    void addAVFrame(AVFrame *avFrame);
    void end();
    void setPath(const QString &value);
    void setWidth(int value);
    void setHeight(int value);
    void run();
    void setTime(int value);
    void savVideo();
    void encodeFrame(AVFrame *pictureYUV);
    void setCamera(const QString &value);
    void setUid(int value);
    //关闭界面时进行视频存储
    void saveVideo();

private:
    AVOutputFormat *outformat;
    int num,width,height,time,pkt_index,uid;
    AVFormatContext * opFormatContext;
    AVCodecContext * pCodecContext;
    AVCodec *encoder;
    AVPacket *pkt;
    QString path,filePath,camera,coverPath;
    QQueue<AVFrame*> AVFramelist;
    QTimer* timer;
//    QMutex mutex;

public slots:

signals:
    void saveImg(QString path);
};

#endif // ENCODETHREAH_H
