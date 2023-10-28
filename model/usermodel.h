#ifndef USERMODEL_H
#define USERMODEL_H

#include <QString>
#include "sqlmodel.h"
#include <QDebug>


class UserModel
{
public:
    static UserModel *getUserModel();
    //新增用户
    int enroll(QString sql1,QString sql2);
    //查寻用户（登录）
    int login(QString sql1,char **&qres,int &row,int &col);
private:
    static UserModel * myUserModel;
    UserModel();
};

#endif // USERMODEL_H
