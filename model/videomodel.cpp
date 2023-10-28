#include "videomodel.h"

videoModel * videoModel::myvideoModel = nullptr;

videoModel *videoModel::getvideoModel()
{
    if(myvideoModel == nullptr)
        myvideoModel = new videoModel;
    return myvideoModel;
}

int videoModel::creatVideo(QString sql)
{
    int result = -1;
    char errmessage;


    int res = SqlModel::getmySql()->other(sql.toUtf8(),&errmessage);
    if(res == SQLITE_OK)
       result = 0;
    else {
            qDebug() << "新增失败";

            result = 2;
        }

    return result;
}

int videoModel::getVideo(QString sql1, char **&qres, int &row, int &col)
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

videoModel::videoModel()
{

}
