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
    return rows;
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
