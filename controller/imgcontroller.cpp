#include "imgcontroller.h"

ImgController * ImgController::myImgController = nullptr;

ImgController *ImgController::getImgController()
{
    if(myImgController == nullptr)
        myImgController = new ImgController;
    return myImgController;
}

int ImgController::creatImg(QString path, int uid)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeStr = currentDateTime.toString("yyyyMMddhhmmss");
    QString sql = QString("INSERT INTO 'img' ('u_id', "
                          "creat_time, 'path') VALUES (%1,%2,'%3')").arg(uid).arg(currentDateTimeStr).arg(path);
    ImgModel *myImgModel = ImgModel::getImgModel();
    int res = myImgModel->creatImgModel(sql.toUtf8());
    return res;
}

QList<Img> ImgController::getImgList(int uid)
{
   QList<Img> list;
   char **qres;
   int row,col;
   QString sql = QString("SELECT path,creat_time FROM 'img' WHERE u_id = %1").arg(uid);
   ImgModel *myImgModel = ImgModel::getImgModel();
   int res = myImgModel->getImgList(sql,qres,row,col);
   if(res == 0 & row > 0)
       for(int i=1;i<=row;i++)
       {
           QImage img(qres[i*col]);
           Img newImg(qres[i*col],img,qres[i*col+1]);
           list.push_back(newImg);
       }
   return list;
}

ImgController::ImgController()
{

}
