#include "fcovertovideo.h"

#include <QDebug>

fcoverTovideo::fcoverTovideo()
{
//注册组件
av_register_all();
//视频信息结构体初始化
formatContent=avformat_alloc_context();
//目标视频信息结构体初始化
outformatContent=avformat_alloc_context();
//是否为视频流
video_index=-1;
//保存压缩码流数据
pkt=(AVPacket*)malloc(sizeof(AVPacket));
}

void fcoverTovideo::openH264File(QString file)
{
    int res=avformat_open_input(&formatContent,file.toStdString().c_str(), nullptr,nullptr);
    //判断打开成功与否
    if(res<0)
    {
    qDebug()<<"打开失败";
    return ;
    }

    res=avformat_find_stream_info(formatContent,nullptr);
    //判断是否有流媒体
    if(res<0)
    {
    qDebug()<<"没有流媒体";
    return ;
    }
    //查找视频流
    for(int i=0;i<formatContent->nb_streams;i++)
    {
    //视频流
    if(formatContent->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
    {
    video_index=i;
    break;
    }
    }
    //需要判断是不是视频流
    if(video_index<0)
    {
    qDebug()<<"查找视频流失败";
    return ;
    }
    qDebug()<<"输入的准备已经完成";
}

void fcoverTovideo::covertToDest(QString file)
{
    outformat=av_guess_format(nullptr,file.toStdString().c_str(),nullptr);
    if(outformat==nullptr)
    {
    qDebug()<<"没找到对应格式的相关信息";
    return ;
    }
    int res=avio_open(&outformatContent->pb,file.toStdString().c_str(), AVIO_FLAG_WRITE);
    if(res<0)
    {
    qDebug()<<"打开输出文件失败";
    return ;
    }
    qDebug() << "准备完成";
    AVStream *OutnewStream=avformat_new_stream(outformatContent,nullptr);
    if(OutnewStream==nullptr)
    {
    qDebug()<<"新建流失败";
    return ;
    }
    res=avcodec_parameters_copy(OutnewStream->codecpar, formatContent->streams[video_index]->codecpar);
    if(res<0)
    {
    qDebug()<<"参数设置失败";
    return ;
    }
    OutnewStream->codecpar->codec_tag=0;
    res=avformat_write_header(outformatContent,nullptr);
    if(res<0)
    {
    qDebug()<<"头部信息写入失败";
    return ;
    }
    int size=OutnewStream->codecpar->width*OutnewStream->codecpar->height;
    av_new_packet(pkt,size);
    //循环去读一帧一帧的数据
    int frameCount=0;
    while(av_read_frame(formatContent,pkt)==0)
    {
    //判断是不是视频流
    if(pkt->stream_index==video_index)
    {
    //转码
    frameCount++;
    qDebug()<<"第"<<frameCount<<"帧";
    //判断有没有设置显示时间基：没有设置的情况下
    if(pkt->pts==AV_NOPTS_VALUE)
    {
    //时间基的转换
    AVRational time_base1=formatContent->streams[video_index]->time_base;
    //计算两帧之前的长度:转换
    int64_t duration=(double)AV_TIME_BASE/
    av_q2d(formatContent->streams[video_index]->r_frame_rate);
    //计算显示时间基：（当前帧数*两帧之间的长度）/（输入时间基*AV_TIME_BASE）
    pkt->pts=(double)(frameCount*duration)/
    (double)(av_q2d(time_base1)*AV_TIME_BASE);
    //解码时间基=显示时间基：
    pkt->dts=pkt->pts;
    //
    pkt->duration=duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);
    }
    //有设置的情况下：显示时间基大于解码时间基不做处理
    else if(pkt->pts<pkt->dts)
    {
    continue;
    }
    //时间基的转换：参数 1：要换算的值；参数 2：原来的时间基，参数 3：现在的时间基
    //参数 4：换算的规则
    //显示时间基的转化
    pkt->pts=av_rescale_q_rnd(pkt->pts, formatContent->streams[video_index]->time_base, OutnewStream->time_base, (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));
    //解码时间基的转换
    pkt->dts=av_rescale_q_rnd(pkt->dts, formatContent->streams[video_index]->time_base, OutnewStream->time_base, (AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX)
    );
    pkt->duration=av_rescale_q(pkt->duration, formatContent->streams[video_index]->time_base, OutnewStream->time_base);
    pkt->pos=-1;
    pkt->flags|=AV_PKT_FLAG_KEY;
    pkt->stream_index=0;
    //写入数据到输出视频信息结构体汇总
    av_interleaved_write_frame(outformatContent,pkt);
    }
    av_packet_unref(pkt);
    }
    //写入尾巴帧
    av_write_trailer(outformatContent);
    //关闭编码器
    avcodec_close(outformatContent->streams[video_index]->codec);
    av_freep(&outformatContent->streams[video_index]->codec);
    //关闭输出流
    avio_close(outformatContent->pb);
    //释放输出信息的结构体
    av_free(outformatContent);
    //关闭输入流
    avformat_close_input(&formatContent);
    //释放输入视频信息结构体
    av_free(formatContent);
    //释放包
    av_packet_free(&pkt);
}
