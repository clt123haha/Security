#include "widget.h"
#include <QApplication>
#include "view/videoplaybackwin.h"
#include "view/startuanimation.h"
#include "view/logwin.h"
#include "view/setwin.h"
#include "data/playthreah.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    startuanimation w;
    w.show();
    return a.exec();
}
