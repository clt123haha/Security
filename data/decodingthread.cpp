#include "decodingthread.h"


DecodingThread::DecodingThread()
{
    encodeThreah = new EncodeThreah;
}

void DecodingThread::run()
{
    avpacket = (AVPacket *)malloc((sizeof (AVPacket)));
    this->picture = av_frame_alloc();
    this->picture->width = this->CodecContext->width;
    this->picture->height = this->CodecContext->height;
    this->picture->format = this->CodecContext->pix_fmt;
    this->pictureRGB = av_frame_alloc();
    this->pictureRGB->width = this->CodecContext->width;
    this->pictureRGB->height = this->CodecContext->height;
    this->pictureRGB->format = this->CodecContext->pix_fmt;
    this->pictureYUV = av_frame_alloc();
    this->pictureYUV->width = this->CodecContext->width;
    this->pictureYUV->height = this->CodecContext->height;
    this->pictureYUV->format = this->CodecContext->pix_fmt;
    int picture_size = avpicture_get_size(AV_PIX_FMT_RGB32,CodecContext->width,CodecContext->height);
    uint8_t *buffter = (uint8_t *)malloc(picture_size*sizeof (uint8_t));

    avpicture_fill((AVPicture *)pictureRGB, buffter, AV_PIX_FMT_RGB32, this->CodecContext->width, this->CodecContext->height);

    SwsContext *swsContext =  sws_getContext(CodecContext->width,CodecContext->height,CodecContext->pix_fmt,
                   CodecContext->width,CodecContext->height,AV_PIX_FMT_RGB32,
                   SWS_BICUBIC,nullptr,nullptr,nullptr);

    int pictureYUV_size = avpicture_get_size(AV_PIX_FMT_YUV420P,CodecContext->width,CodecContext->height);
    uint8_t *buffterYUV = (uint8_t *)malloc(pictureYUV_size*sizeof (uint8_t));

    avpicture_fill((AVPicture *)pictureYUV, buffterYUV, AV_PIX_FMT_YUV420P, this->CodecContext->width, this->CodecContext->height);

    SwsContext *swsYUVContext =  sws_getContext(CodecContext->width,CodecContext->height,CodecContext->pix_fmt,
                   CodecContext->width,CodecContext->height,AV_PIX_FMT_YUV420P,
                   SWS_BICUBIC,nullptr,nullptr,nullptr);

    encodeThreah->setWidth(pictureYUV->width);
    encodeThreah->setHeight(pictureYUV->height);
    connect(encodeThreah,SIGNAL(saveImg(QString)),this,SLOT(saveCoverImg(QString)));
   encodeThreah->start();

    int num = 0;
    char img_path[255];
    img_path[0] = '\0';
    while( av_read_frame(pFormatContext,avpacket) == 0)
    {
        if(end)
            break;

        if(avpacket->stream_index == videoStreamIndex)
        {
            int got_num = -1;
            avcodec_decode_video2(CodecContext,picture,&got_num,this->avpacket);
            if(got_num != 0){
                sws_scale(swsContext,picture->data,picture->linesize,0,picture->height,pictureRGB->data,pictureRGB->linesize);
                QImage img((uchar *)buffter, pictureRGB->width, pictureRGB->height, QImage::Format_RGB32);
                emit change(img);
                img_my = img.copy();
                sws_scale(swsYUVContext,picture->data,picture->linesize,0,picture->height,pictureYUV->data,pictureYUV->linesize);
                encodeThreah->addAVFrame(pictureYUV);
                num++;
            }

        }
        av_packet_unref(this->avpacket);
    }
}

int DecodingThread::getReady()
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
    SetController *mySetController = SetController::getSetController();
    QList<QString> list = mySetController->cheakRow();
    filepath = list.at(1);
    encodeThreah->setPath(list.at(0));
    encodeThreah->setTime(list.at(2).toInt());
    encodeThreah->setCamera(name);

    return res;
}

int DecodingThread::openVideo()
{
    av_register_all();
    avdevice_register_all();
    pFormatContext = avformat_alloc_context();
    fmt=av_find_input_format("dshow");
    QString cameraName = QString("video=%1").arg(name);
    int res=avformat_open_input(&pFormatContext,cameraName.toUtf8(),fmt,nullptr);
    if(res!=0)
    {
        qDebug()<<"摄像头打开失败";

        return -1;
    }
    return 0;
}

int DecodingThread::findStream()
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
        videoStreamIndex = -1;
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
        }
    }
    return result;
}

int DecodingThread::openDcodec()
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

void DecodingThread::setName(const QString &value)
{
    name = value;
}

void DecodingThread::saveImg()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyyMMddhhmmss");
    QString path = QString("%3/%1/%2.png").arg(name).arg(formattedDateTime).arg(imgPath);
    QDir directory;

    if (!directory.exists(filepath)) {
        if (!directory.mkpath(filepath))
        {
            qDebug() << "Failed to create directory.";
            return;
        }
    }
    ImgController *myImgController = ImgController::getImgController();
    myImgController->creatImg(path,uid);
    img_my.save(path);
    qDebug() << path;
}


void DecodingThread::setUid(int value)
{
    uid = value;
    encodeThreah->setUid(value);
}

void DecodingThread::setImgPath(const QString &value)
{
    imgPath = value;
}

void DecodingThread::saveVideo()
{
    encodeThreah->saveVideo();
}

void DecodingThread::saveCoverImg(QString path)
{
    img_my.save(path);
}

