#include "setmodel.h"

SetModel * SetModel::mySetModel = nullptr;

SetModel *SetModel::getSetModel()
{
    if(mySetModel == nullptr)
        mySetModel = new SetModel;
    return mySetModel;
}

int SetModel::SetStatus(QString sql1, QString sql2 ,QString sql3)
{
    int result = -1;
    char errmessage;

    char **qres;
    int row,col;
    int res = SqlModel::getmySql()->search(sql1,qres,row,col,&errmessage);
    if(res == SQLITE_OK && row == 0)
    {
        res = SqlModel::getmySql()->other(sql2.toUtf8(),&errmessage);
        if(res == SQLITE_OK){
            result = 0;
        }
        else {
            qDebug() << "设置失败";

            result = 2;
        }
    }
    else
    {
        res = SqlModel::getmySql()->other(sql3.toUtf8(),&errmessage);
        if(res == SQLITE_OK){
            result = 0;
        }
        else {
            qDebug() << "设置失败";

            result = 2;
        }
    }
    return result;
}

int SetModel::cheakRow(char **&qres,int &row,int &col)
{
    int  result = -1;
    QString sql = "SELECT * FROM 'set'";
    char errmessage;
    int res = SqlModel::getmySql()->search(sql,qres,row,col,&errmessage);
    if(res == 0)
    {
        if(row > 0)
            result = 0;
        else {
            result = 2;
        }
    }
    else {

        result = 1;
    }
    return result;
}

SetModel::SetModel()
{

}
