#ifndef VERIFICATIONCODELABEL_H
#define VERIFICATIONCODELABEL_H

#include <QLabel>
#include <QTimer>
#include <QPaintEvent>
#include <QPainter>
#include <QTime>

class VerificationCodeLabel : public QLabel
{
    Q_OBJECT

public:
    VerificationCodeLabel(QWidget *parent=0);
    ~VerificationCodeLabel();
    //返回一个字符串（字母一律都按照小写返回）
    QString getVerificationCode() const;
    //重写时间处理的回调函数mousePressEvent
    void mousePressEvent(QMouseEvent *ev);
public slots:
    //公共槽函数
    //刷新验证码，在用户不确定的时候进行相应刷新
    void slt_reflushVerification();
    //实时更新颜色
//    void TimeoutSlot();
protected:
    //重写绘制事件,以此来生成验证码
    void paintEvent(QPaintEvent *event);
private:

    int noice_point_number ;//噪点的数量
    QTimer *m_timer;
    enum {
        NUMBER_FLAG,
        UPLETTER_FLAG,
        LOWLETTER_FLAG
    };
    //这是一个用来的生成验证码函数
    void produceVerificationCode() const;
    //产生一个随机的字符
    QChar produceRandomLetter() const;
    //产生随机的颜色
    void produceRandomColor() const;

    QChar *verificationCode;
    QColor *colorArray;


};

#endif // VERIFICATIONCODELABEL_H
