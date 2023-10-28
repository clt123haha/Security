#include "ComboBoxTest.h"

#include <QCheckBox>

ComboBoxTest::ComboBoxTest(QWidget *parent) : QWidget(parent)

{
    ui->setupUi(this);
    // 设置窗口标题
    this->setWindowTitle("ComboBox带复选框");

    // 创建QListWidget对象空间
    m_listWidget = new QListWidget;

    // 要先设置model，然后在设置view，我测试时反过来设置会崩掉哦
    //! 将comboBox的model对象设置为QListWidget对象的model
    //! 因为QListWidget继承QListView所以其存在model对象
    comboBox->setModel(m_listWidget->model());

    //! 将comboBox的view对象设置为QListWidget对象
    //! 因为QListWidget继承QListView所以相当于View
    comboBox->setView(m_listWidget);

    //! 此处添加一个空item用于当默认值
    // 创建QListWidgetItem对象并指定父对象
    QListWidgetItem *item = new QListWidgetItem(m_listWidget);
    // 将item添加到QListWidget对象中
    m_listWidget->addItem(item);
}

ComboBoxTest::~ComboBoxTest()
{
    //释放QListWidget、ui的存储空间
    delete m_listWidget;
    delete ui;
}

void ComboBoxTest::on_addBtn_clicked()
{
    // 获取要添加item上显示的文本
    QString text = ui->lineEdit->text();

    // 当文本为空时直接返回，不添加
    if(text.isEmpty())
    {
        return;
    }

    //! 创建复选框对象空间
    //! 创建时指定复选框的父对象，其父对象在释放时会将其中的子对象指针先释放
    QCheckBox *checkBox = new QCheckBox(m_listWidget);

    // 创建QListWidgetItem对象并传入文本和指定父对象
    QListWidgetItem *item = new QListWidgetItem(text, m_listWidget);
    //设置item文本居中
    item->setTextAlignment(Qt::AlignCenter);

    //将item添加到QListWidget对象中
    m_listWidget->addItem(item);
    //将复选框设置到item中
    m_listWidget->setItemWidget(item, checkBox);
}

void ComboBoxTest::on_comboBox_currentIndexChanged(int index)
{
    //获取当前索引位置的item
    QListWidgetItem *item = m_listWidget->item(index);
    //当获取的item为空时返回
    if(nullptr == item)
    {
        return;
    }

    //获取当前选项的文本
    QString itemStr = item->text();

    //获取当前选项所在复选框的widget对象
    QWidget *widget = m_listWidget->itemWidget(item);
    //将widget对象转换为checkBox对象
    QCheckBox *checkBox = dynamic_cast<QCheckBox *>(widget);
    //当获取的checkBox为空时返回
    if(nullptr == checkBox)
    {
        ui->textBrowser->append("空");
        return;
    }

    //根据checkBox的勾选状态获取文本
    QString checkBoxStr = checkBox->isChecked()? "已勾选": "未勾选";

    //组合text
    QString text = QString("索引位置：%1  文本：%2  选中状态：%3")
            .arg(index).arg(itemStr).arg(checkBoxStr);

    //将文本追加到文本栏中
    ui->textBrowser->append(text);
}

