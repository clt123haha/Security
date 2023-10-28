#include "multiselectcombobox.h"

MultiSelectComboBox::MultiSelectComboBox(QWidget *parent)
    : QComboBox(parent)
    , hidden_flag_(true)
    , show_flag_(false)
{
    list_widget_ = new QListWidget();
    line_edit_ = new QLineEdit();
    search_bar_ = new QLineEdit();

    /*设置搜索框*/
    QListWidgetItem* currentItem = new QListWidgetItem(list_widget_);
    //设置搜索框提示信息
    search_bar_->setPlaceholderText("Search.........");
    //显示清除按钮
    search_bar_->setClearButtonEnabled(true);
    list_widget_->addItem(currentItem);
    list_widget_->setItemWidget(currentItem, search_bar_);

    /*设置文本框*/
    //设为只读，因为该输入框只用来显示选中的选项，称为文本框更合适些
    line_edit_->setReadOnly(true);
    //把当前对象安装(或注册)为事件过滤器，当前也称为过滤器对象。事件过滤器通常在构造函数中进行注册。
    line_edit_->installEventFilter(this);
    //设置禁用样式，因为不受样式表控制，临时这样解决
    line_edit_->setStyleSheet("QLineEdit:disabled{background:rgb(233,233,233);}");

    this->setModel(list_widget_->model());
    this->setView(list_widget_);
    this->setLineEdit(line_edit_);
    connect(search_bar_, SIGNAL(textChanged(const QString&)), this, SLOT(onSearch(const QString&)));
    connect(this, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &MultiSelectComboBox::itemClicked);
}

MultiSelectComboBox::~MultiSelectComboBox()
{
}

void MultiSelectComboBox::hidePopup()
{
    show_flag_ = false;
    int width = this->width();
    int height = this->height();
    int x = QCursor::pos().x() - mapToGlobal(geometry().topLeft()).x() + geometry().x();
    int y = QCursor::pos().y() - mapToGlobal(geometry().topLeft()).y() + geometry().y();
    if (x >= 0 && x <= width && y >= this->height() && y <= height + this->height())
    {
    }
    else
    {
        QComboBox::hidePopup();
    }
}

void MultiSelectComboBox::addItem(const QString& _text, const QVariant& _variant /*= QVariant()*/)
{
    Q_UNUSED(_variant);
    QListWidgetItem* item = new QListWidgetItem(list_widget_);
    QCheckBox* checkbox = new QCheckBox(this);
    checkbox->setText(_text);
    list_widget_->addItem(item);
    list_widget_->setItemWidget(item, checkbox);
    connect(checkbox, &QCheckBox::stateChanged, this, &MultiSelectComboBox::stateChange);
}

void MultiSelectComboBox::addItems(const QStringList& _text_list)
{
    for (const auto& text_one : _text_list)
    {
        addItem(text_one);
    }
}

QStringList MultiSelectComboBox::currentText()
{
    QStringList text_list;
    if (!line_edit_->text().isEmpty())
    {
        //以;为分隔符分割字符串
        text_list = line_edit_->text().split(':');
    }
    return text_list;
}

int MultiSelectComboBox::count() const
{
    int count = list_widget_->count() - 1;
    if (count < 0)
    {
        count = 0;
    }
    return count;
}

void MultiSelectComboBox::SetSearchBarPlaceHolderText(const QString _text)
{
    search_bar_->setPlaceholderText(_text);
}

void MultiSelectComboBox::SetPlaceHolderText(const QString& _text)
{
    line_edit_->setPlaceholderText(_text);
}

void MultiSelectComboBox::ResetSelection()
{
    int count = list_widget_->count();
    for (int i = 1; i < count; i++)
    {
        //获取对应位置的QWidget对象
        QWidget *widget = list_widget_->itemWidget(list_widget_->item(i));
        //将QWidget对象转换成对应的类型
        QCheckBox *check_box = static_cast<QCheckBox*>(widget);
        check_box->setChecked(false);
    }
}

void MultiSelectComboBox::clear()
{
    line_edit_->clear();
    list_widget_->clear();
    QListWidgetItem* currentItem = new QListWidgetItem(list_widget_);
    search_bar_->setPlaceholderText("Search.........");
    search_bar_->setClearButtonEnabled(true);
    list_widget_->addItem(currentItem);
    list_widget_->setItemWidget(currentItem, search_bar_);
    SetSearchBarHidden(hidden_flag_);
    connect(search_bar_, SIGNAL(textChanged(const QString&)), this, SLOT(onSearch(const QString&)));
}

void MultiSelectComboBox::TextClear()
{
    line_edit_->clear();
    ResetSelection();
}

void MultiSelectComboBox::setCurrentText(const QString& _text)
{
    int count = list_widget_->count();
    for (int i = 1; i < count; i++)
    {
        //获取对应位置的QWidget对象
        QWidget *widget = list_widget_->itemWidget(list_widget_->item(i));
        //将QWidget对象转换成对应的类型
        QCheckBox *check_box = static_cast<QCheckBox*>(widget);
        if (_text.compare(check_box->text()))
            check_box->setChecked(true);
    }
}

void MultiSelectComboBox::setCurrentText(const QStringList& _text_list)
{
    int count = list_widget_->count();
    for (int i = 1; i < count; i++)
    {
        //获取对应位置的QWidget对象
        QWidget *widget = list_widget_->itemWidget(list_widget_->item(i));
        //将QWidget对象转换成对应的类型
        QCheckBox *check_box = static_cast<QCheckBox*>(widget);
        if (_text_list.contains(check_box->text()))
            check_box->setChecked(true);
    }
}

void MultiSelectComboBox::SetSearchBarHidden(bool _flag)
{
    hidden_flag_ = _flag;
    list_widget_->item(0)->setHidden(hidden_flag_);
}

bool MultiSelectComboBox::eventFilter(QObject *watched, QEvent *event)
{
    //设置点击输入框也可以弹出下拉框
    if (watched == line_edit_ && event->type() == QEvent::MouseButtonRelease && this->isEnabled())
    {
        showPopup();
        return true;
    }
    return false;
}

void MultiSelectComboBox::wheelEvent(QWheelEvent *event)
{
    //禁用QComboBox默认的滚轮事件
    Q_UNUSED(event);
}

void MultiSelectComboBox::keyPressEvent(QKeyEvent *event)
{
    QComboBox::keyPressEvent(event);
}

void MultiSelectComboBox::stateChange(int _row)
{
    Q_UNUSED(_row);
    QString selected_data("");
    int count = list_widget_->count();
    for (int i = 1; i < count; i++)
    {
        QWidget *widget = list_widget_->itemWidget(list_widget_->item(i));
        QCheckBox *check_box = static_cast<QCheckBox*>(widget);
        if (check_box->isChecked())
        {
            selected_data.append(check_box->text()).append(";");
        }
    }
    selected_data.chop(1);
    if (!selected_data.isEmpty())
    {
        line_edit_->setText(selected_data);
    }
    else
    {
        line_edit_->clear();
    }
    line_edit_->setToolTip(selected_data);
    emit selectionChange(selected_data);
}

void MultiSelectComboBox::onSearch(const QString& _text)
{
    for (int i = 1; i < list_widget_->count(); i++)
    {
        QCheckBox *check_box = static_cast<QCheckBox*>(list_widget_->itemWidget(list_widget_->item(i)));
        //文本匹配则显示，反之隐藏
        //Qt::CaseInsensitive模糊查询
        if (check_box->text().contains(_text, Qt::CaseInsensitive))
            list_widget_->item(i)->setHidden(false);
        else
            list_widget_->item(i)->setHidden(true);
    }
}

void MultiSelectComboBox::itemClicked(int _index)
{
    if (_index != 0)
    {
        QCheckBox *check_box = static_cast<QCheckBox*>(list_widget_->itemWidget(list_widget_->item(_index)));
        check_box->setChecked(!check_box->isChecked());
    }
}

