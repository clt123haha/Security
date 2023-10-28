#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QString>
#include "model/usermodel.h"
#include <QDateTime>


class UserController
{
public:
    static UserController * getUserController();
    int enroll(QString account,QString name,QString pwd);
    QList<QString> login(QString account,QString pwd);
private:
    static UserController * myUserController;
    UserController();
};

#endif // USERCONTROLLER_H
