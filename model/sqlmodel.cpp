#include "sqlmodel.h"

SqlModel* SqlModel::mySqlModel = nullptr;
sqlite3 * SqlModel::dbconnect = nullptr;

SqlModel *SqlModel::getmySql()
{
    if(SqlModel::mySqlModel == nullptr)
    {
      SqlModel::mySqlModel = new SqlModel();

    }
    return SqlModel::mySqlModel;

}

int SqlModel::search(QString sql,char **&qres,int &row,int &col,char *errormessage)
{
    int result = -1;
    int res = sqlite3_get_table(SqlModel::mySqlModel->dbconnect,sql.toUtf8(),&qres,&row,&col,&errormessage);
    if(res == SQLITE_OK)
        return 0;
    else {
        qDebug() << sqlite3_errmsg(SqlModel::mySqlModel->dbconnect);
        qDebug() << sqlite3_errcode(SqlModel::mySqlModel->dbconnect);
        return 1;
    }
}

int SqlModel::other(QString sql, char *errormessage)
{
    int res = sqlite3_exec(SqlModel::mySqlModel->dbconnect,sql.toUtf8(),nullptr,nullptr,&errormessage);
    if(res == SQLITE_OK)
        return 0;
    else {
        qDebug() << sqlite3_errmsg(SqlModel::mySqlModel->dbconnect);
        qDebug() << sqlite3_errcode(SqlModel::mySqlModel->dbconnect);
        return 1;
    }
}

SqlModel::SqlModel()
{
    int res = sqlite3_open("./security.db", &this->dbconnect);
    if(res != SQLITE_OK){
        qDebug() << "打不开数据库";
    }
}

sqlite3 *SqlModel::getDbconnect() const
{
    return dbconnect;
}
