#ifndef SETMODEL_H
#define SETMODEL_H

#include <QString>
#include "sqlmodel.h"
#include <QDebug>

class SetModel
{
public:
    static SetModel *getSetModel();
    //设置表的增，改
    int SetStatus(QString sql1,QString sql2,QString sql3);
    //查询信息
    int cheakRow(char **&qres,int &row,int &col);
private:
    static SetModel * mySetModel;
    SetModel();
};

#endif // SETMODEL_H
