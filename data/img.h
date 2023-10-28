#ifndef IMG_H
#define IMG_H

#include <QImage>
#include <QString>



class Img
{
public:
    Img(QString path,QImage img,QString creattime);
    QImage getImg() const;
    QString getPath() const;
    void setCreattime(const QString &value);
    QString getCreattime() const;
    bool operator==(const Img& other);



private:
    QImage img;
    QString path,creattime;
};

#endif // IMG_H
