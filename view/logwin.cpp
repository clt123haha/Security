#include "logwin.h"

logWin::logWin(QWidget *parent) : QWidget(parent)
{
    this->resize(640,480);
    this->initContorl();
}

void logWin::initContorl()
{
    scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);

    mainLayout = new QVBoxLayout;
    QHBoxLayout *rowLayout = new QHBoxLayout();
    setLayout(mainLayout);
    scrollWidget = new QWidget;
    scrollLayout = new QVBoxLayout(scrollWidget);

    scrollArea->setWidget(scrollWidget);

    labelIndex = new QLabel("序号");
    labelTime = new QLabel("时间");
    labelUserId = new QLabel("用户ID");
    labelContent = new QLabel("内容");

    rowLayout->addWidget(labelIndex);
    rowLayout->addWidget(labelTime);
    rowLayout->addWidget(labelUserId);
    rowLayout->addWidget(labelContent);

    mainLayout->addLayout(rowLayout);
    mainLayout->addWidget(scrollArea);
}

void logWin::changeData()
{
    scrollWidget = new QWidget;
    scrollLayout = new QVBoxLayout(scrollWidget);

    scrollArea->setWidget(scrollWidget);

    QHBoxLayout *rowLayout = new QHBoxLayout();
    QList<QString> loglist = logController::getlogController()->getLog();
    for (int i = 0; i < loglist.size(); i++) {
        QLabel* labelLog = new QLabel(loglist[i]);

        // 每四个 QLabel 添加一个新的行布局
        if (i % 4 == 0) {
            rowLayout = new QHBoxLayout();
            scrollLayout->addLayout(rowLayout);
        }

        rowLayout->addWidget(labelLog);
    }
}
