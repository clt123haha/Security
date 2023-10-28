#include "setcontroller.h"

SetController * SetController::mySetController = nullptr;

SetController *SetController::getSetController()
{
   if(mySetController == nullptr)
       mySetController = new SetController;
   return mySetController;
}

QList<QString> SetController::cheakRow()
{
    QList<QString> result;
    char **qres;
    int row,col;
    int res = SetModel::getSetModel()->cheakRow(qres,row,col);
    if(res == 0 && row>0)
    {
        for (int i=1;i < row+1;i++) {
            result.append(qres[i*col]);
            result.append(qres[i*col+1]);
            result.append(qres[i*col+2]);
            result.append(qres[i*col+3]);
        }
    }
    return result;
}

int SetController::SetStatus(QString video_path, QString img_path, QString timeset, QString crame)
{
    QString sql1 = "SELECT * FROM 'set'";
    QString sql2 = QString("INSERT INTO 'set'(video_path,img_path,time_set,camera) VALUES('%1','%2','%3','%4')").arg(video_path).arg(img_path).arg(timeset).arg(crame);
    QString sql3 = QString("UPDATE 'set' SET video_path = '%1' ,img_path = '%2',time_set = '%3',camera = '%4'").arg(video_path).arg(img_path).arg(timeset).arg(crame);
    SetModel * mySetModel = SetModel::getSetModel();
    qDebug() << sql1.toUtf8();
    qDebug() << sql2.toUtf8();
    qDebug() << sql3.toUtf8();
    int res = mySetModel->SetStatus(sql1,sql2,sql3);
    if(res == 0)
        qDebug() << "success";
    return res;

}

SetController::SetController()
{

}
