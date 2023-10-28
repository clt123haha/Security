#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QString>
#include "sqlmodel.h"
#include <QDebug>

class videoModel
{
public:
    static videoModel * getvideoModel();
    //新增数据
    int creatVideo(QString sql);
    //查询数据
    int getVideo(QString sql1,char **&qres,int &row,int &col);
private:
    static videoModel * myvideoModel;
    videoModel();
};

#endif // VIDEOMODEL_H
