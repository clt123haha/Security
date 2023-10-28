#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H

#include <QList>
#include <QString>
#include "model/logmodel.h"
#include <QDateTime>

class logController
{
public:
    static logController * getlogController();
    int creatLog(int uid,QString content);
    QList<QString> getLog();

private:
    logController();
    static logController * mylogController;
};

#endif // LOGCONTROLLER_H
