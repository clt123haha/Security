#include "logmodel.h"

logModel * logModel::mylogModel = nullptr;

logModel *logModel::getlogModel()
{
    if(mylogModel == nullptr)
        mylogModel = new logModel;
    return mylogModel;
}

int logModel::getLog(QString sql1, char **&qres, int &row, int &col)
{
    int result = -1;
    char errmessage;
    int res = SqlModel::getmySql()->search(sql1.toUtf8(),qres,row,col,&errmessage);
    if(res == SQLITE_OK)
    {
        if(row == 0)
            result = 2;
        else {
            result = 0;
        }
    }
    else {
        result = 1;
    }
    return result;
}

int logModel::creatLog(QString sql)
{
    int result = -1;
    char errmessage;
    int res = SqlModel::getmySql()->other(sql.toUtf8(),&errmessage);
    if(res == SQLITE_OK)
       result = 0;
    else {
            result = 2;
        }

    return result;
}

logModel::logModel()
{

}
