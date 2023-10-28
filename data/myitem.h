#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QStyleOptionGraphicsItem>

class MyItem : public QObject , public QGraphicsItem
{
    Q_OBJECT
public:
    MyItem(QString path,int status,int direction);
    QRectF boundingRect() const;
    void advance(int);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void setImagePath(QString newPath);

private:
    QPixmap img;
    int   status;
    int direction;

signals:
    void boom();

};

#endif // MYITEM_H
