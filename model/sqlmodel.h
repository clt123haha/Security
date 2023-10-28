#ifndef SQLMODEL_H
#define SQLMODEL_H

#include "sqlite3.h"
#include <QDebug>
#include <QString>


class SqlModel
{
public:
    char *errormessage = nullptr;
    static SqlModel* getmySql();
    //查
    static int search(QString sql,char **&qres,int &row,int &col,char *errormessage);
    //增删改
    static int other(QString sql,char *errormessage);
    sqlite3 *getDbconnect() const;

private:
    SqlModel();
    static sqlite3 *dbconnect;
    static SqlModel *mySqlModel;
};

#endif // SQLMODEL_H
