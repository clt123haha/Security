#ifndef SETWIN_H
#define SETWIN_H

#include <QWidget>
#include <QListView>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QCameraInfo>
#include <QComboBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QMessageBox>
#include "data/multiselectcombobox.h"
#include "controller/setcontroller.h"
#include  "data/ccheckcombox.h"

class SetWin : public QWidget
{
    Q_OBJECT
public:
    explicit SetWin(QWidget *parent = nullptr);
    void initContorl();

private:
    QMessageBox *msgBox;
    QLabel *label1,*label2,*label3,*label4,*title;
    QLineEdit *edit1,*edit2;
    QPushButton *bun1,*bun2,*PinBun,*CancelBun,*confirmButton,*cancelButton;
    QString videoPath,imgPath;
    QList<QCameraInfo> cameras;
    QComboBox *timeList;
    SetController *mySetController;
    QList<QCheckBox*> checkBoxList;
    QStandardItemModel* model;
    MultiSelectComboBox* comboBox;
    CCheckCombox *cameraNameList;

signals:
    //设置完成
    void down();
    //未完成设置
    void notDo();

public slots:
    //改变视频路径显示
    void changeVideoPath();
    //改变图片路径显示
    void changeImgPath();
    //更新数据库
    void updateSet();
    //返回主窗口
    void Cansel();
    //打开消息提示
    void openMsgBox();
    //关闭消息提示
    void closeMsgBox();
};

#endif // SETWIN_H
