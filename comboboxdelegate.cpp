#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
{

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem("Food");
    editor->addItem("Utilities");
    editor->addItem("Housing");
    editor->addItem("Clothing");
    editor->addItem("Transportation");
    editor->addItem("Saving");
    editor->addItem("Personal");
//    editor->setMaximum(100);

    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();//.toInt();

    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(value); //setCurrentIndex(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
//    comboBox->interpretText();
    QString value = comboBox->currentText();

    model->setData(index, value, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

