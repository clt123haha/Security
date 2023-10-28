#include "CheckboxComboBox.h"
#include <QMouseEvent>
#include <QAbstractItemView>

CheckboxComboBox::CheckboxComboBox(QWidget *parent)
    : QComboBox(parent)
{
    connect(view(), &QAbstractItemView::clicked, this, &CheckboxComboBox::updateText);
}

void CheckboxComboBox::setItemChecked(int index, bool checked)
{
    m_checkedItems[index] = checked;
    updateText();
}

bool CheckboxComboBox::isItemChecked(int index) const
{
    return m_checkedItems.value(index, false);
}

QStringList CheckboxComboBox::getCheckedItems() const
{
    QStringList checkedItems;
    for (auto it = m_checkedItems.constBegin(); it != m_checkedItems.constEnd(); ++it) {
        if (it.value()) {
            checkedItems << itemText(it.key());
        }
    }
    return checkedItems;
}

void CheckboxComboBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        showPopup();
    }
}

void CheckboxComboBox::hidePopup()
{
    // Do nothing to prevent the popup from closing when the user clicks outside
}

void CheckboxComboBox::updateText()
{
    QStringList checkedItems = getCheckedItems();
    if (!checkedItems.isEmpty()) {
        setEditText(checkedItems.join("; "));
    } else {
        setEditText("");
    }
}
