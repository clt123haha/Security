#include "savepicthreadh.h"

#include <QImageWriter>

savePicThreadh::savePicThreadh() : QThread ()
{

}

void savePicThreadh::setImg(const QImage &value)
{
    img = value;
}

void savePicThreadh::setPath(const QString &value)
{
    path = value;
}

void savePicThreadh::run()
{
    QImageWriter writer(path);
    writer.write(img);
}

void savePicThreadh::setUid(int value)
{
    uid = value;
}
