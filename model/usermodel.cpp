#include "usermodel.h"

UserModel * UserModel::myUserModel = nullptr;

UserModel *UserModel::getUserModel()
{
    if(myUserModel == nullptr)
        myUserModel = new UserModel;
    return myUserModel;
}

int UserModel::enroll(QString sql1,QString sql2)
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
            qDebug() << "新增失败";

            result = 2;
        }
    }
    else {
        qDebug() << "用户名重复";

        result = 1;
    }
    return result;
}

int UserModel::login(QString sql1,char **&qres, int &row, int &col)
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

UserModel::UserModel()
{

}
