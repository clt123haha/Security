#ifndef COMBOBOXTEST_H
#define COMBOBOXTEST_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class ComboBoxTest;
}

class ComboBoxTest : public QWidget
{
    Q_OBJECT

public:
    explicit ComboBoxTest(QWidget *parent = nullptr);
    ~ComboBoxTest();

private slots:

    void on_addBtn_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    QListWidget         *m_listWidget;  // 下拉列表框的
};

#endif // COMBOBOXTEST_H

