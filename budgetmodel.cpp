#include "budgetmodel.h"

BudgetModel::BudgetModel(QObject *parent) : QAbstractTableModel(parent)
{
    //    selectedCell = 0;
        db = new DBManager();
        month = 6;
        expenses = db->getBudgetedExpenses(month);
        rows = expenses.size();
        cols = 2;
}

int BudgetModel::rowCount(const QModelIndex &parent) const
{
    return expenses.size();
}

int BudgetModel::columnCount(const QModelIndex &parent) const
{
    return cols;
}

QVariant BudgetModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
        case Qt::DisplayRole:
            return expenses.at(row).at(col+1);
            break;
        case Qt::FontRole:
            if (row == 0 && col == 0) //change font only for cell(0,0)
            {
                QFont boldFont;
                boldFont.setBold(true);
                return boldFont;
            }
            break;
    }
    return QVariant();
}

QVariant BudgetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Expense");
            case 1:
                return QString("Amount");
            }
        }
    }
    return QVariant();
}

void BudgetModel::setMonth(int month)
{
    this->month = month;
}

bool BudgetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        int row = index.row();
        int col = index.column();
        QStringList newList;

        switch(col)
        {
            case 0:
                newList << value.toString() << "";
                break;
            case 1:
                newList << "" << value.toString();
                break;
        }

        //save value from editor to expenses
        if(row > expenses.size())
        {
            //New row
            expenses.push_back(newList);
            qDebug() << "push_back()";
        }
        else
        {
            expenses.at(row).replace(col + 1, value.toString());
            qDebug() << "replace";
        }
//        return expenses.at(row).at(col+1);
        qDebug() << value.toString();
    }
    return true;
}

Qt::ItemFlags BudgetModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

bool BudgetModel::insertRows(int row, int count, const QModelIndex &parent)
{

}

void BudgetModel::readData()
{
    expenses = db->getBudgetedExpenses(month);
}

void BudgetModel::writeData()
{

}

void BudgetModel::dataUpdated()
{

}

void BudgetModel::addRow()
{
    //notify that expenses is appended
   beginInsertRows(QModelIndex(), expenses.size()-1, expenses.size()-1);
       expenses.push_back(QStringList() << "New Item" << "0.0");
   //notify views that you're done with modifying the underlying data
   endInsertRows();
//    emit dataChanged();
    qDebug() << "signal received";
}
