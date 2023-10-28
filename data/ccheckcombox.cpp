#include "ccheckcombox.h"


CCheckCombox::CCheckCombox(QWidget *parent) : QComboBox(parent),
m_ItemRoot(nullptr),
m_bAutoUnchecked(true)
{
    if (QStandardItemModel *m = qobject_cast<QStandardItemModel*>(this->model()))
    {
        m_ItemRoot = m->invisibleRootItem();
    }
    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setReadOnly(true);

    this->setLineEdit(m_pLineEdit);
    connect(this, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index){
        combineCurrentText();
    });
}

void CCheckCombox::addCheckableItem(const QString &text, const QVariant &userData /*= QVariant()*/)
{
    QComboBox::addItem(text, userData);

    if (m_ItemRoot)
    {
        m_ItemRoot->child(this->count()-1, 0)->setCheckable(true);
    }
}

void CCheckCombox::updateIndexStatus(int index)
{
    Qt::CheckState state = (Qt::CheckState)itemData(index, Qt::CheckStateRole).toInt();

    switch (state)
    {
    case Qt::Unchecked:
        setItemData(index, Qt::Checked, Qt::CheckStateRole);
        break;
    case Qt::PartiallyChecked:
    case Qt::Checked:
        setItemData(index, Qt::Unchecked, Qt::CheckStateRole);
        break;
    default:
        break;
    }

}

void CCheckCombox::mousePressEvent(QMouseEvent *e)
{
    int x = e->pos().x();
    int iconWidth = iconSize().width();
    if (x <= iconWidth)
    {
        int index = currentIndex();
        updateIndexStatus(index);
    }
    else
    {
        QComboBox::mousePressEvent(e);
    }
}

void CCheckCombox::hidePopup()
{
    int iconWidth = iconSize().width();
    int x = QCursor::pos().x() - mapToGlobal(geometry().topLeft()).x() + geometry().x();
    int index = view()->selectionModel()->currentIndex().row();
    if (x >= 0 && x <= iconWidth)
    {
        updateIndexStatus(index);
    }
    else
    {
        QComboBox::hidePopup();
    }
}

void CCheckCombox::setAutoUnchecked(bool bAuto)
{
    m_bAutoUnchecked = bAuto;
}

void CCheckCombox::combineCurrentText()
{
    bool canUncheck = false;
    if (m_ItemRoot)
    {
        if (!m_ItemRoot->child(currentIndex(), 0)->isCheckable())
        {
            canUncheck = m_bAutoUnchecked;
        }
    }

    QString showText = "";
    for (int i = 0; i < count(); ++i)
    {
        Qt::CheckState state = (Qt::CheckState)itemData(i, Qt::CheckStateRole).toInt();

        if (state == Qt::Checked)
        {
            if (canUncheck)
            {
                setItemData(i, Qt::Unchecked, Qt::CheckStateRole);
            }
            else
            {
                showText.append(this->itemText(i)).append(";");
            }
        }
    }

    if (showText.isEmpty())
        showText = currentText();
    //显示调整
    QFontMetrics fm(this->font());
    m_pLineEdit->setText(showText);
}

QVector<int> CCheckCombox::getCheckedIndexs()
{
    QVector<int> checkedIndexs;
    for (int i = 0; i < count(); ++i)
    {
        Qt::CheckState state = (Qt::CheckState)itemData(i, Qt::CheckStateRole).toInt();

        if (state == Qt::Checked)
        {
            checkedIndexs.push_back(i);
        }
    }
    return checkedIndexs;
}

QVariant CCheckCombox::getUserData(int index)
{
    return itemData(index, Qt::UserRole);
}


