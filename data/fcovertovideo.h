#ifndef FCOVERTOVIDEO_H
#define FCOVERTOVIDEO_H


extern "C"{
    #include "libavcodec/avcodec.h"
    #include "libavdevice/avdevice.h"
    #include "libavfilter/avfilter.h"
    #include "libavformat/avformat.h"
    #include "libavutil/avutil.h"
    #include "libswresample/swresample.h"
    #include "libswscale/swscale.h"

}

#include <QString>
class fcoverTovideo
{
public:
    fcoverTovideo();
    //打开 H264 的压缩码流数据
    void openH264File(QString file);
    //转码得到相应的封装格式
    void covertToDest(QString file);
private:
    AVFormatContext *formatContent,*outformatContent;
    int video_index;
    AVOutputFormat *outformat;
    AVPacket *pkt;
};

#endif // FCOVERTOVIDEO_H
