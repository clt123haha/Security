#ifndef IMGCONTROLLER_H
#define IMGCONTROLLER_H

#include "model/imgmodel.h"
#include "data/img.h"
#include <QDateTime>

class ImgController
{
public:
    static ImgController * getImgController();
    int creatImg(QString path,int uid);
    QList<Img> getImgList(int uid);

private:
    static ImgController * myImgController;
    ImgController();
};

#endif // IMGCONTROLLER_H
