#-------------------------------------------------
#
# Project created by QtCreator 2023-09-12T22:12:22
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Security
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    view/startuanimation.cpp \
    data/myitem.cpp \
    view/loginwin.cpp \
    data/VerificationCodeLabel.cpp \
    view/setwin.cpp \
    view/enrollwin.cpp \
    controller/usercontroller.cpp \
    model/usermodel.cpp \
    model/sqlmodel.cpp \
    view/mainwin.cpp \
    model/setmodel.cpp \
    controller/setcontroller.cpp \
    view/monitorwin.cpp \
    view/playbackwin.cpp \
    data/clicklabel.cpp \
    data/decodingthread.cpp \
    model/videomodel.cpp \
    model/imgmodel.cpp \
    controller/imgcontroller.cpp \
    data/encodethreah.cpp \
    view/imgshowwin.cpp \
    data/img.cpp \
    controller/videocontroller.cpp \
    view/videoplaybackwin.cpp \
    data/video.cpp \
    data/playthreah.cpp \
    view/player.cpp \
    data/fcovertovideo.cpp \
    data/turn.cpp \
    data/multiselectcombobox.cpp \
    data/ccheckcombox.cpp \
    data/savepicthreadh.cpp \
    view/logwin.cpp \
    model/logmodel.cpp \
    controller/logcontroller.cpp

HEADERS += \
        widget.h \
    view/startuanimation.h \
    data/myitem.h \
    view/loginwin.h \
    data/VerificationCodeLabel.h \
    view/setwin.h \
    view/enrollwin.h \
    controller/usercontroller.h \
    model/usermodel.h \
    model/sqlmodel.h \
    view/mainwin.h \
    model/setmodel.h \
    controller/setcontroller.h \
    view/monitorwin.h \
    view/playbackwin.h \
    data/clicklabel.h \
    data/decodingthread.h \
    model/videomodel.h \
    model/imgmodel.h \
    controller/imgcontroller.h \
    data/encodethreah.h \
    view/imgshowwin.h \
    data/img.h \
    controller/videocontroller.h \
    view/videoplaybackwin.h \
    data/video.h \
    data/playthreah.h \
    view/player.h \
    data/fcovertovideo.h \
    data/turn.h \
    data/multiselectcombobox.h \
    data/ccheckcombox.h \
    data/savepicthreadh.h \
    view/logwin.h \
    model/logmodel.h \
    controller/logcontroller.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

QT       += core gui multimedia multimediawidgets \
            core

DESTDIR = bin

INCLUDEPATH += ./ffmpeglib/include

LIBS += $$PWD/lib/sqlite3.lib \
        $$PWD/ffmpeglib/lib/avcodec.lib  \
        $$PWD/ffmpeglib/lib/avdevice.lib  \
        $$PWD/ffmpeglib/lib/avfilter.lib  \
        $$PWD/ffmpeglib/lib/avformat.lib  \
        $$PWD/ffmpeglib/lib/avutil.lib  \
        $$PWD/ffmpeglib/lib/swresample.lib  \
        $$PWD/ffmpeglib/lib/swscale.lib
