#ifndef IMGMODEL_H
#define IMGMODEL_H

#include <QString>
#include "sqlmodel.h"
#include <QDebug>

class ImgModel
{
public:
    static ImgModel * getImgModel();
    //新增图片信息
    int creatImgModel(QString sql);
    //得到图片信息
    int getImgList(QString sql,char **&qres,int &row,int &col);

private:
    static ImgModel * myImgModel;
    ImgModel();
};

#endif // IMGMODEL_H
