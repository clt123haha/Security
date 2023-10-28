#ifndef VIDEO_H
#define VIDEO_H

#include <QString>

class video
{
public:
    video(QString path,QString coverpath,QString camera,QString creat_time,int time);
    QString getPath() const;
    QString getCoverpath() const;
    QString getCamera() const;
    QString getCreat_time() const;
    int getTime() const;

private:
    QString path,coverpath,camera,creat_time;
    int time;
};

#endif // VIDEO_H
