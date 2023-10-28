#ifndef MULTISELECTCOMBOBOX_H
#define MULTISELECTCOMBOBOX_H

#include <QComboBox>
#include <QListWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QEvent>

class MultiSelectComboBox : public QComboBox
{
    Q_OBJECT

public:
    MultiSelectComboBox(QWidget *parent = Q_NULLPTR);
    ~MultiSelectComboBox();

    //隐藏下拉框
    virtual void hidePopup();

    //添加一条选项
    void addItem(const QString& _text, const QVariant& _variant = QVariant());

    //添加多条选项
    void addItems(const QStringList& _text_list);

    //返回当前选中选项
    QStringList currentText();

    //返回当前选项条数
    int count()const;

    //设置搜索框默认文字
    void SetSearchBarPlaceHolderText(const QString _text);

    //设置文本框默认文字
    void SetPlaceHolderText(const QString& _text);

    //下拉框状态恢复默认
    void ResetSelection();

    //清空所有内容
    void clear();

    //文本框内容清空
    void TextClear();

    //设置选中文本--单
    void setCurrentText(const QString& _text);

    //设置选中文本--多
    void setCurrentText(const QStringList& _text_list);

    //设置搜索框是否禁用
    void SetSearchBarHidden(bool _flag);

protected:

    //事件过滤器
    virtual bool eventFilter(QObject *watched,QEvent *event);

    //滚轮事件
    virtual void wheelEvent(QWheelEvent *event);

    //按键事件
    virtual void keyPressEvent(QKeyEvent *event);

private slots:

    //槽函数：文本框文本变化
    void stateChange(int _row);

    //槽函数：搜索框文本变化
    void onSearch(const QString& _text);

    //槽函数：点击下拉框选项
    void itemClicked(int _index);

signals:

    //信号：发送当前选中选项
    void selectionChange(const QString _data);

private:
    //下拉框
    QListWidget* list_widget_;
    //文本框，搜索框
    QLineEdit* line_edit_, *search_bar_;
    //搜索框显示标志
    bool hidden_flag_;
    //下拉框显示标志
    bool show_flag_;
};



#endif // MULTISELECTCOMBOBOX_H
