#include "myitem.h"

MyItem::MyItem(QString path, int status,int direction)
{
    this->img.load(path);
    this->status = status;
    this->direction = direction;
}

QRectF MyItem::boundingRect() const
{
    return  QRectF(-this->img.width()/2,-this->img.height()/2,this->img.width(),this->img.height());
}

void MyItem::advance(int)
{
    if(this->status == 1){
        if(collidingItems().size()>0){
            this->status = 0;
            qDebug() << "boom";
            emit boom();
            return;
        }
        this->setPos(mapToScene(5*this->direction,0));
    }
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-this->img.width()/2,-this->img.height()/2,this->img.width(),this->img.height(),this->img);
}

void MyItem::setImagePath(QString newPath)
{
    img = QPixmap(newPath);
    update();
}
