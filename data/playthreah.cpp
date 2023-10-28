#include "playthreah.h"

PlayThread::PlayThread()
{
    videoStreamIndex = -1;
    puase = false;
    end = false;
    waitTime = 40;
    target = -1;
}

void PlayThread::run()
{
    avpacket = (AVPacket *)malloc((sizeof (AVPacket)));
    int size = this->CodecContext->width*this->CodecContext->height;
    av_new_packet(avpacket,size);
    this->picture = av_frame_alloc();
    this->picture->width = this->CodecContext->width;
    this->picture->height = this->CodecContext->height;
    this->picture->format= this->CodecContext->pix_fmt;
    this->pictureRGB = av_frame_alloc();
    this->pictureRGB->width = this->CodecContext->width;
    this->pictureRGB->height = this->CodecContext->height;
    this->pictureRGB->format= this->CodecContext->pix_fmt;

    int picture_size = avpicture_get_size(AV_PIX_FMT_RGB32,CodecContext->width,CodecContext->height);
    uint8_t *buffter = (uint8_t *)malloc(picture_size*sizeof (uint8_t));

    avpicture_fill((AVPicture *)pictureRGB, buffter, AV_PIX_FMT_RGB32,
                   this->CodecContext->width, this->CodecContext->height);



    SwsContext *swsContext =  sws_getContext(CodecContext->width,CodecContext->height,CodecContext->pix_fmt,
                   CodecContext->width,CodecContext->height,AV_PIX_FMT_RGB32,
                   SWS_BICUBIC,nullptr,nullptr,nullptr);


    int num = 0;

    while( av_read_frame(pFormatContext,avpacket) == 0)
    {
        while(puase)
        {
            if(end)
                break;
        }

        if(end)
            break;

        if(avpacket->stream_index == videoStreamIndex)
        {
            int got_num = -1;
            avcodec_decode_video2(CodecContext,picture,&got_num,this->avpacket);
            if(got_num != 0){
                if(num < target)
                {
                    num++;
                }
                else {
                    sws_scale(swsContext,picture->data,picture->linesize,0,picture->height,pictureRGB->data,pictureRGB->linesize);

                    QImage img((uchar *)buffter, pictureRGB->width, pictureRGB->height, QImage::Format_RGB32);

                    emit change(img);
                    msleep(waitTime);
                    num++;
                    emit addNum(num);
                }
            }
        }

        av_packet_unref(this->avpacket);
    }
}


int PlayThread::getReady()
{
    int res = openVideo();
    if(res == 0)
    {
        res = findStream();
        if(res == 0)
        {
            res = openDcodec();
        }
    }
    return res;
}

QString PlayThread::getPath() const
{
    return path;
}

void PlayThread::setPath(const QString &value)
{
    path = value;
}

int PlayThread::openVideo()
{
    int result = -1;
    av_register_all();
    pFormatContext = avformat_alloc_context();
    int res=avformat_open_input(&pFormatContext,path.toUtf8(),nullptr,nullptr);
    if(res!=0)
    {
        qDebug()<<"_open_input_fail";

        return -1;
    }
    if (res != 0) {
        result = 1;
    }
    else
        result = 0;
    return result;
}

int PlayThread::findStream()
{
    int result = -1;
    int res = avformat_find_stream_info(pFormatContext, nullptr);
    if (res < 0) {
        qDebug() << "Failed to find stream information";
        avformat_close_input(&pFormatContext);
        result = 1;
    }
    else
    {

        for (unsigned int i = 0; i < pFormatContext->nb_streams; i++) {
            if (pFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoStreamIndex = i;
                break;
            }
        }

        if (videoStreamIndex == -1) {
            qDebug() << "No video stream found in the input file";
            avformat_close_input(&pFormatContext);
            result = 2;
        }
        else {
            result = 0;
            qDebug() << "video stream found in the input file"<<videoStreamIndex;
        }
    }


    return result;
}

int PlayThread::openDcodec()
{
    int result = -1;
    CodecContext = pFormatContext->streams[videoStreamIndex]->codec;
    AVCodec * decode = avcodec_find_decoder(CodecContext->codec_id);
    if(decode == nullptr){
        qDebug() << "can't find decode file";
        result = 1;
    }
    else {
        int res = avcodec_open2(CodecContext, decode, nullptr);
        if (res < 0) {
            qDebug() << "Failed to open codec";
            result = 2;
            }
        else {
            result = 0;
        }
    }
    return result;
}

bool PlayThread::getPuase() const
{
    return puase;
}

void PlayThread::setPuase(bool value)
{
    puase = value;
}

int PlayThread::getWaitTime() const
{
    return waitTime;
}

void PlayThread::setWaitTime(int value)
{
    waitTime = value;
}

void PlayThread::setEnd(bool value)
{
    end = value;
}

int PlayThread::getNum()
{
    avpacket = (AVPacket *)malloc((sizeof (AVPacket)));
    int size = this->CodecContext->width*this->CodecContext->height;
    av_new_packet(avpacket,size);

    this->picture = av_frame_alloc();
    this->picture->width = this->CodecContext->width;
    this->picture->height = this->CodecContext->height;
    this->picture->format= this->CodecContext->pix_fmt;


    int num = 0;

    while( av_read_frame(pFormatContext,avpacket) == 0)
    {

        if(avpacket->stream_index == videoStreamIndex)
        {
            int got_num = -1;
            avcodec_decode_video2(CodecContext,picture,&got_num,this->avpacket);
            if(got_num != 0){
                num++;
            }
        }

        av_packet_unref(this->avpacket);
    }
    return num;
}

void PlayThread::setTarget(int value)
{
    target = value;
}
