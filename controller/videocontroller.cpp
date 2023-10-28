#include "videocontroller.h"


VideoController * VideoController::myVideoController = nullptr;

int VideoController::creatVideo(QString path, QString coverPath, QString camera,int fream_count)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeStr = currentDateTime.toString("yyyyMMddhhmmss");
    QString sql = QString("INSERT INTO 'video' ('path', 'cover_path', 'camera', 'creat_time','fream_count') VALUES ('%1','%2','%3',%4,%5)").arg(path).arg(coverPath).arg(camera).arg(currentDateTimeStr).arg(fream_count);
    int res = videoModel::getvideoModel()->creatVideo(sql.toUtf8());
    return res;
}

VideoController *VideoController::getVideoController()
{
    if(myVideoController == nullptr)
        myVideoController = new VideoController;
    return myVideoController;
}

QList<video> VideoController::getVideoList()
{
    QList<video> list;
    char **qres=nullptr;
    int row=0,col=0;
    QString sql = QString("SELECT path,cover_path,camera,creat_time,fream_count FROM 'video' ORDER BY creat_time DESC");

    int res = videoModel::getvideoModel()->getVideo(sql,qres,row,col);
    qDebug()<<res;
    qDebug()<<row;
    if(res == 0 && row > 0)
    {
        for (int i = 1;i<=row;i++)
        {
            int time = QString(qres[i*col+4]).toInt();
           video tempVideo(qres[i*col],qres[i*col+1],qres[i*col+2],qres[i*col+3],time);
           list.append(tempVideo);
        }
    }
    return list;
}

VideoController::VideoController()
{

}
