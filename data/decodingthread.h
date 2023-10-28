#ifndef DECODINGTHREAD_H
#define DECODINGTHREAD_H

#include <QThread>
#include <QDebug>
#include <QImage>
#include "controller/setcontroller.h"
#include "controller/imgcontroller.h"
#include "encodethreah.h"
#include <QDir>
#include <QFile>
#include <QTime>
#include <QUrl>

extern "C"{
    #include "libavcodec/avcodec.h"
    #include "libavdevice/avdevice.h"
    #include "libavfilter/avfilter.h"
    #include "libavformat/avformat.h"
    #include "libavutil/avutil.h"
    #include "libswresample/swresample.h"
    #include "libswscale/swscale.h"

}

class DecodingThread : public QThread
{
    Q_OBJECT
public:
    DecodingThread();
    void run();
    int getReady();
    int openVideo();
    int findStream();
    int openDcodec();
    bool getPuase() const;
    void setPuase(bool value);
    void setEnd(bool value);
    void setName(const QString &value);
    void saveImg();
    void setUid(int value);
    void setImgPath(const QString &value);
    //关闭界面时进行视频存储
    void saveVideo();

private:
    EncodeThreah *encodeThreah;
    int uid,time;
    QString filepath,imgPath;
    bool end = false;
    AVInputFormat *fmt;
    bool puase = false;
    int waitTime = 40;
    QString name;
    AVFormatContext *pFormatContext;
    int videoStreamIndex;
    AVCodec * decode;
    AVPacket *avpacket;
    AVCodecContext *CodecContext;
    AVFrame *picture,*pictureRGB,*pictureYUV;
    QImage img_my;

signals:
    void change(QImage img);

public slots:
    void saveCoverImg(QString path);

};

#endif // DECODINGTHREAD_H
