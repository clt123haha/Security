#include "verificationcodelabel.h"

const int letter_number = 4;//产生字符的数量

VerificationCodeLabel::VerificationCodeLabel(QWidget *parent)
    : QLabel(parent)
{
    //生成随机种子
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    colorArray = new QColor[letter_number];
    verificationCode = new QChar[letter_number];
    noice_point_number = this->width();


}
//重写绘制事件,以此来生成验证码
void VerificationCodeLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPoint p;
    //背景设为白色
    //    painter.fillRect(this->rect(), Qt::white);
    painter.fillRect(0, 0, 150, 52, Qt::white);
    painter.setFont(QFont("Comic Sans MS"));
    //产生4个不同的字符
    produceVerificationCode();
    //产生4个不同的颜色
    produceRandomColor();
    //绘制验证码
    for (int i = 0; i < letter_number; ++i)
    {
         painter.save();  // 保存当前绘制状态
         painter.scale(1.5, 1.5);  // 放大绘制的比例，可以根据需要调整放大倍数
         painter.drawText(0 + 20 * i, 0, 45, 45, Qt::AlignCenter, QString(verificationCode[i]));
         painter.restore();
    }
    //绘制噪点
    for (int j = 0; j < noice_point_number; ++j)
    {

        painter.setPen(colorArray[j % 4]);
                painter.drawPoint(0 + (qrand() % 150), 0 + (qrand() % 52));
    }
    return;
}
//这是一个用来生成验证码的函数
void VerificationCodeLabel::produceVerificationCode() const
{
    for (int i = 0; i < letter_number; ++i)
        verificationCode[i] = produceRandomLetter();
    return;
}
//产生一个随机的字符
QChar VerificationCodeLabel::produceRandomLetter() const
{
    QChar c;
    int flag = qrand() % letter_number;
    switch (flag)
    {
    case NUMBER_FLAG:c='0' + qrand() % 10; break;
    case UPLETTER_FLAG:c='A' + qrand() % 26; break;
    case LOWLETTER_FLAG:c='a' + qrand() % 26; break;
    default:c=qrand() % 2 ? 'W' : 'D';
    }
    return c;


}
//产生随机的颜色
void VerificationCodeLabel::produceRandomColor() const
{
    for (int i = 0; i < letter_number; ++i)
        colorArray[i] = static_cast<Qt::GlobalColor>((qrand() % 16) + 2);
    return;
}
//返回一个字符串（字母一律都按照小写返回）
QString VerificationCodeLabel::getVerificationCode() const
{
    QString s;
    QChar cTemp;
    for (int i = 0; i < letter_number; ++i)
    {
        cTemp = verificationCode[i];
        s += cTemp>97?cTemp.toLower():cTemp;
    }
    return s;
}
//重写单击事件处理回调函数，实现点击刷新验证码
void VerificationCodeLabel::mousePressEvent(QMouseEvent *ev)
{
    repaint();
}
//刷新验证码，在用户不确定的时候进行相应刷新
void VerificationCodeLabel::slt_reflushVerification()
{
    repaint();
}
VerificationCodeLabel::~VerificationCodeLabel()
{

}

