#ifndef CHECKBOXCOMBOBOX_H
#define CHECKBOXCOMBOBOX_H

#include <QComboBox>

class CheckboxComboBox : public QComboBox
{
    Q_OBJECT
public:
    CheckboxComboBox(QWidget *parent = nullptr);

    void setItemChecked(int index, bool checked);
    bool isItemChecked(int index) const;
    QStringList getCheckedItems() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void hidePopup() override;

private slots:
    void updateText();

private:
    QMap<int, bool> m_checkedItems;
};

#endif // CHECKBOXCOMBOBOX_H
