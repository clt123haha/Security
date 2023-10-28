#include "logcontroller.h"

logController * logController::mylogController = nullptr;

logController *logController::getlogController()
{
    if(mylogController == nullptr)
        mylogController = new logController;
    return mylogController;
}

int logController::creatLog(int uid, QString content)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeStr = currentDateTime.toString("yyyyMMdd");
    QString sql = QString("INSERT INTO 'loging'(time,uid,content) VALUES('%1',%2,'%3')").arg(currentDateTimeStr).arg(uid).arg(content);
    int res = logModel::getlogModel()->creatLog(sql);
    return res;
}

QList<QString> logController::getLog()
{
    QList<QString> result;
    char **qres;
    int row,col;
    QString sql = "SELECT * FROM 'loging'";
    int res = logModel::getlogModel()->getLog(sql.toUtf8(),qres,row,col);
    if(res == 0 && row>0)
    {
        for (int i=1;i < row+1;i++) {
            result.append(qres[i*col]);
            result.append(qres[i*col+1]);
            result.append(qres[i*col+2]);
            result.append(qres[i*col+3]);
        }
    }
    return result;
}

logController::logController()
{

}
