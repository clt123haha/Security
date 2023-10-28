#include "video.h"

video::video(QString path,QString coverpath,QString camera,QString creat_time,int time)
{
    this->path = path;
    this->coverpath = coverpath;
    this->camera = camera;
    this->creat_time = creat_time;
    this->time = time;
}

QString video::getPath() const
{
    return path;
}

QString video::getCoverpath() const
{
    return coverpath;
}

QString video::getCamera() const
{
    return camera;
}

QString video::getCreat_time() const
{
    return creat_time;
}

int video::getTime() const
{
    return time;
}
