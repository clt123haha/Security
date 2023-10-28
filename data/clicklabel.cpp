#include "clicklabel.h"


ClickLabel::ClickLabel(int labelId, QWidget *parent): QLabel(parent), m_labelId(labelId)
{
    this->m_labelId = labelId;
}




void ClickLabel::changeImg(QImage img)
{
    this->img = img;
    setFixedSize(this->w, this->h);
    this->update();
}

void ClickLabel::saveImg(QString path,int uid)
{

    img.save(path.toUtf8());
    ImgController::getImgController()->creatImg(path,uid);
}

void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    emit labelClicked(m_labelId);
}

void ClickLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit labelClickedTwice(m_labelId);
}

void ClickLabel::setH(int value)
{
    h = value;
}

void ClickLabel::setW(int value)
{
    w = value;
}
