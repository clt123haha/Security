#ifndef _CHECK_COMBOX_H
#define _CHECK_COMBOX_H

#include <QComboBox>
#include <QStandardItem>
#include <QMouseEvent>
#include <qdebug.h>
#include <qabstractitemview.h>
#include <QStandardItemModel>
#include <QLineEdit>

class QLineEdit;

class CCheckCombox : public QComboBox
{
    Q_OBJECT
public:
    CCheckCombox(QWidget *parent = NULL);

    void addCheckableItem(const QString &text, const QVariant &userData = QVariant());

    virtual void hidePopup();

    void setAutoUnchecked(bool bAuto);

    QVector<int> getCheckedIndexs();

    QVariant getUserData(int index);

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    void updateIndexStatus(int index);

    void combineCurrentText();
private:
    QStandardItem *m_ItemRoot;
    QLineEdit* m_pLineEdit;
    bool m_bAutoUnchecked;
};
#endif

