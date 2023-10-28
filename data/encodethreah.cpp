#include "encodethreah.h"


EncodeThreah::EncodeThreah()
{
    num = 0;
    pkt_index = 0;
    time = 0;
}

void EncodeThreah::setPath(const QString &value)
{
    path = value;
}

void EncodeThreah::setWidth(int value)
{
    width = value;
}

void EncodeThreah::setHeight(int value)
{
    height = value;
}



void EncodeThreah::encodeFrame(AVFrame *pictureYUV)
{
    //把AVFrame发送给pCodecContext
    int res = avcodec_send_frame(this->pCodecContext, pictureYUV);
    if(res<0)
    {
        qDebug()<<"avcodec_send_frame error";
        return;
    }
    //一帧YUV420P压缩可能压缩成2个AVPacket
    while (res >= 0) {
        pictureYUV->pts = pkt_index++;
        //把一帧AVFrame压缩成AVPacket
        res = avcodec_receive_packet(this->pCodecContext, this->pkt);
        if(res == AVERROR_EOF || res == AVERROR(EAGAIN))
        {
            break;
        }
        //AVPacket写入h264文件
        av_interleaved_write_frame(this->opFormatContext, this->pkt);
        num++;
        //编码帧数+1
    }
}



void EncodeThreah::setCamera(const QString &value)
{
    camera = value;
}

void EncodeThreah::setUid(int value)
{
    uid = value;
}

void EncodeThreah::saveVideo()
{
    this->savVideo();                           //写尾帧，写入数据库
    num = 0;
}

void EncodeThreah::addAVFrame(AVFrame* avFrame)
{
    AVFramelist.enqueue(avFrame);
}


void EncodeThreah::run()
{
    while (true)
    {
        if (!AVFramelist.isEmpty())
        {
            if(num == 0)
            {
                this->ready();                              //编码准备
                this->encodeFrame(AVFramelist.dequeue());   //编码
                if(num==0) num++;
                QDateTime currentDateTime = QDateTime::currentDateTime();
                QString formattedDateTime = currentDateTime.toString("yyyyMMddhhmmss");
                coverPath = QString("%1/%3/%2.png").arg(path).arg(formattedDateTime).arg(camera);
                emit saveImg(coverPath);
            }
            else if(num<1500 * time)
                this->encodeFrame(AVFramelist.dequeue());   //编码
            else if(num>=1500 * time)
            {
                this->savVideo();                           //写尾帧，写入数据库
                num = 0;
            }
        }
    }
}

void EncodeThreah::setTime(int value)
{
    time = value;
}

void EncodeThreah::savVideo()
{
    av_write_trailer(opFormatContext);
    avio_close(opFormatContext->pb);
    avformat_free_context(opFormatContext);
    VideoController::getVideoController()->creatVideo(filePath,coverPath,camera,num);
    logController::getlogController()->creatLog(uid,"视频存储");
}


void EncodeThreah::ready()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyyMMddhhmmss");

    filePath = QString("%1/%3/%2.h264").arg(path).arg(formattedDateTime).arg(camera);

    QString path_ = QString("%1/%2").arg(path).arg(camera);

    QDir dir(path_);
    if (!dir.exists()) {
        if (dir.mkpath(".")) {
        }
    }

    av_register_all();
    opFormatContext=avformat_alloc_context();
    outformat=av_guess_format(nullptr,filePath.toUtf8(),nullptr);
    if(outformat==nullptr)
    {
    qDebug()<<"猜测格式失败";
    return;
    }

    opFormatContext->oformat=outformat;
    /*打开文件流：
    参数 1:AVIOContext--输入输出的上下文对象（视频流信息结构体中的一个成员 pb）；
    参数 2:文件名；
    参数 3：文件以什么形式打开,编码是以写的方式打开；
    返回值：成功与否，<0 为失败
    */
    int res=avio_open(&opFormatContext->pb,filePath.toUtf8(),AVIO_FLAG_WRITE);
    if(res<0)
    {
    qDebug()<<"打开视频文件失败";
    return;
    }

    AVStream *newStream=avformat_new_stream(opFormatContext,nullptr);
    if(newStream==nullptr)
    {
    qDebug()<<"新建视频流失败";
    return;
    }

    pCodecContext=newStream->codec;
    /*除了可以得到视频编解码的相关信息，编码的话还需要设置很多的参数
    首先是它的宽度和高度*/
    pCodecContext->width=width;
    pCodecContext->height=height;
    //设置码率，每一秒存的比特,这个值的设置也不要随意；码率太大，视频也会变大；
    pCodecContext->bit_rate=400000;
    //设置帧率-每一秒多少张图片--25 张
    pCodecContext->time_base={1,25};
    //设置显示的率，也叫码率
    pCodecContext->framerate={25,1};
    /*设置每一组的图片数量，IPB 帧，I 帧存一帧的所有数据，P 帧根据 I 解码，B 帧根据
    前后的两帧解码；10 帧为一组；
    后面的 10 帧解码不会与前 10 帧有关联。*/
    pCodecContext->gop_size=10;//官方建议 10 帧为一个单位
    //还有两个量化值需要设置:会影响视频的清晰度，越小越清晰，建议默认就可以了
    pCodecContext->qmax=51;
    pCodecContext->qmin=10;
    //设置一下 b 帧为 0，这样的话就只有 I 帧和 P 帧
    pCodecContext->max_b_frames=0;
    //设置编码格式--YUV420P 像素数据
    pCodecContext->pix_fmt=AV_PIX_FMT_YUV420P;
    //设置流的格式：视频流还是音频流--视频流
    pCodecContext->codec_type=AVMEDIA_TYPE_VIDEO;
    //设置编码器的 id,根据匹配到的 AVOutputFormat 对应信息来设置
    pCodecContext->codec_id=outformat->video_codec;

    AVCodec *codec=avcodec_find_encoder(pCodecContext->codec_id);
    if(codec==nullptr)
    {
    qDebug()<<"没找到对应的编码器";
    return;
    }

    res=avcodec_open2(pCodecContext,codec,nullptr);
    if(res<0)
    {
        qDebug()<<"打开编码器失败";
        return;
    }

    res=avformat_write_header(opFormatContext,nullptr);
    if(res<0)
    {
    qDebug()<<"写入头部信息失败";
    return;
    }
    this->num=0;
    pkt=av_packet_alloc();
    qDebug()<<"初始化工作完成";
}

void EncodeThreah::end()
{
    av_write_trailer(opFormatContext);
    avio_close(opFormatContext->pb);
    avformat_free_context(opFormatContext);
}
