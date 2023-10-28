#include "usercontroller.h"


UserController * UserController::myUserController = nullptr;

UserController *UserController::getUserController()
{
    if(myUserController == nullptr)
        myUserController = new UserController;
    return myUserController;
}

int UserController::enroll(QString account, QString name, QString pwd)
{
    int result = -1;
    QDateTime currentDateTime = QDateTime::currentDateTime();

    QString sql1 = QString("SELECT id FROM user WHERE account = '%1'").arg(account);
    QString sql2 = QString("INSERT INTO user(account,pwd,name) VALUES('%1','%2','%3')").arg(account).arg(pwd).arg(name);
    int res = UserModel::getUserModel()->enroll(sql1,sql2);
    if(res == 0)
        result = 0;
    return result;
}

QList<QString> UserController::login(QString account, QString pwd)
{
    QList<QString> list;
    int result = -1;
    char **qres;
    int row,col;

    QString sql1 = QString("SELECT id,name FROM user WHERE account = '%1' and pwd = '%2'").arg(account).arg(pwd);
    int res = UserModel::getUserModel()->login(sql1,qres,row,col);
    if(res == 0 && row >0)
        result = 0;
    if (result == 0)
    {
        list.append(qres[3]);
        list.append(qres[2]);
        return list;
    }
     return list;
}

UserController::UserController()
{

}
