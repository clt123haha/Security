#include "img.h"

Img::Img(QString path,QImage img,QString creattime)
{
    this->path = path;
    this->img = img;
    this->creattime = creattime;
}

QImage Img::getImg() const
{
    return img;
}



QString Img::getPath() const
{
    return path;
}

void Img::setCreattime(const QString &value)
{
    creattime = value;
}

QString Img::getCreattime() const
{
    return creattime;
}

bool Img::operator==(const Img &other)
{
    return (this->getCreattime() == other.getCreattime() && this->path == other.path and this->img == other.img);
}

