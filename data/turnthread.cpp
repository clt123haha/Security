#include "turnthread.h"

void turnThread::getReady()
{

}

void turnThread::run()
{

}

turnThread::turnThread()
{
    video_index=-1;
    filename = "../fileout/video/sintel.h264";
    savepath = "../fileout/video/sintel.mp4";
    pkt = (AVPacket *)malloc((sizeof (AVPacket)));
    count=0;

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
