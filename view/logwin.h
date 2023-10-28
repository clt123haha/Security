#ifndef LOGWIN_H
#define LOGWIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "controller/logcontroller.h"
#include <QScrollArea>

class logWin : public QWidget
{
    Q_OBJECT
public:
    explicit logWin(QWidget *parent = nullptr);
    void initContorl();
    void changeData();

private:
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    QVBoxLayout *mainLayout,*scrollLayout ;
    QLabel *labelIndex,*labelTime,*labelUserId,*labelContent;

signals:

public slots:
};

#endif // LOGWIN_H
