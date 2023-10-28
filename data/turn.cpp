#include "turn.h"

turn::turn()
{
    video_index=-1;
    pkt = (AVPacket *)malloc((sizeof (AVPacket)));
    count=0;
}


void turn::turnVideo()
{
    while( av_read_frame(pFormatContext,pkt) == 0)
    {
        if(pkt->stream_index ==video_index)
        {
            count++;
            if(pkt->pts == AV_NOPTS_VALUE)
            {
               AVRational timebase1 =  pFormatContext->streams[video_index]->time_base;
                int64_t duration = (double)AV_TIME_BASE/av_q2d(pFormatContext->streams[video_index]->r_frame_rate);
                pkt->pts = (double)count*duration/(double)(av_q2d(timebase1)*AV_TIME_BASE);
                pkt->dts = pkt->pts;
                pkt->duration = duration/(double)(av_q2d(timebase1)*AV_TIME_BASE);
            }
            else if (pkt->pts<pkt->dts) {
                continue;
            }
            pkt->pts = av_rescale_q_rnd(pkt->pts,pFormatContext->streams[video_index]->time_base,newstream->time_base,(AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));
            pkt->dts = av_rescale_q_rnd(pkt->dts,pFormatContext->streams[video_index]->time_base,newstream->time_base,(AVRounding)(AV_ROUND_INF|AV_ROUND_PASS_MINMAX));
            pkt->duration = av_rescale_q(pkt->duration,pFormatContext->streams[video_index]->time_base,newstream->time_base);
            pkt->pos =  -1;
            pkt->flags |= AV_PKT_FLAG_KEY;
            pkt->stream_index = 0;
            av_interleaved_write_frame(opFormatContext,pkt);

        }
        av_packet_unref(pkt);
    }
    qDebug() << "down";
    av_write_trailer(opFormatContext);
    avcodec_close(opFormatContext->streams[video_index]->codec);
    av_freep(&opFormatContext->streams[video_index]->codec);

}

void turn::getReady()
{
    av_register_all();
    avdevice_register_all();
    pFormatContext = avformat_alloc_context();
    int res = avformat_open_input(&pFormatContext, this->filename.toUtf8(), nullptr, nullptr);
    if (res != 0) {
        qDebug() << "faile";
    }

    int result = -1;
    res = avformat_find_stream_info(pFormatContext, nullptr);
    if (res < 0) {
        qDebug() << "Failed to find stream information";
        avformat_close_input(&pFormatContext);
        result = 1;
    }
    else
    {
        for (unsigned int i = 0; i < pFormatContext->nb_streams; i++) {
            if (pFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                video_index = i;
                break;
            }
        }

        if (video_index == -1) {
            qDebug() << "No video stream found in the input file";
            avformat_close_input(&pFormatContext);
            result = 2;
        }
        else {
            result = 0;
        }
    }

    AVOutputFormat *outputFormat  = av_guess_format(nullptr, savepath.toUtf8().constData(), nullptr);
    if (!outputFormat) {
        qDebug() << "Failed to guess output format";
        return;
    }

    opFormatContext = avformat_alloc_context();
    if (!opFormatContext) {
        qDebug() << "Failed to allocate output format context";
        return;
    }

    opFormatContext->oformat = outputFormat;

    res = avio_open(&opFormatContext->pb, savepath.toUtf8().constData(), AVIO_FLAG_WRITE);
    if (res < 0) {
        qDebug() << "Failed to open output file";
        return;
    }

    newstream = avformat_new_stream(opFormatContext, nullptr);
    if (!newstream) {
        qDebug() << "Failed to create new stream";
        return;
    }

    avcodec_parameters_copy(newstream->codecpar,pFormatContext->streams[video_index]->codecpar);
    newstream->codecpar->codec_tag = 0;
    newstream->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;

    avformat_write_header(opFormatContext,nullptr);
    qDebug() << "success";
}

void turn::setFilename(const QString &value)
{
    filename = value;
}

void turn::setSavepath(const QString &value)
{
    savepath = value;
}
