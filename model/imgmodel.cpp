#include "imgmodel.h"

ImgModel * ImgModel::myImgModel = nullptr;

ImgModel *ImgModel::getImgModel()
{
    if(myImgModel == nullptr)
        myImgModel = new ImgModel;
    return myImgModel;
}

int ImgModel::creatImgModel(QString sql)
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

int ImgModel::getImgList(QString sql,char **&qres,int &row,int &col)
{
    int result = -1;
    char errmessage;
    int res = SqlModel::getmySql()->search(sql.toUtf8(),qres,row,col,&errmessage);
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

ImgModel::ImgModel()
{

}
