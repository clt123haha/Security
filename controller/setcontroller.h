#ifndef SETCONTROLLER_H
#define SETCONTROLLER_H

#include <QString>
#include "model/setmodel.h"


class SetController
{
public:
    static SetController * getSetController();
    int SetStatus(QString video_path,QString img_path,QString timeset,QString crame);
    QList<QString> cheakRow();
private:
    static SetController* mySetController;
    SetController();
};

#endif // SETCONTROLLER_H
