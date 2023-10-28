#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QString>
#include <QList>
#include "sqlmodel.h"
#include <QDebug>

class logModel
{
public:
    static logModel * getlogModel();
    //得到日志信息
    int getLog(QString sql1, char **&qres, int &row, int &col);
    //新增日志信息
    int creatLog(QString sql);

private:
    logModel();
    static logModel * mylogModel;
};

#endif // LOGMODEL_H
