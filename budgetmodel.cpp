#include "budgetmodel.h"

BudgetModel::BudgetModel(QObject *parent) : QAbstractTableModel(parent)
{
    //    selectedCell = 0;
        db = new DBManager();
}

int BudgetModel::rowCount(const QModelIndex &parent) const
{
    return 2;
}

int BudgetModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant BudgetModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
        case Qt::DisplayRole:
            if (row == 0 && col == 0)
            {
                return "Hello World!";
            }
            break;
        case Qt::FontRole:
            if (row == 0 && col == 0) //change font only for cell(0,0)
            {
                QFont boldFont;
                boldFont.setBold(true);
                return boldFont;
            }
            break;
        case Qt::BackgroundRole:

            if (row == 1 && col == 2)  //change background only for cell(1,2)
            {
                QBrush redBackground(Qt::red);
                return redBackground;
            }
            break;
        case Qt::TextAlignmentRole:

            if (row == 1 && col == 1) //change text alignment only for cell(1,1)
            {
                return Qt::AlignRight + Qt::AlignVCenter;
            }
            break;
        case Qt::CheckStateRole:

            if (row == 1 && col == 0) //add a checkbox to cell(1,0)
            {
                return Qt::Checked;
            }
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
                return QString("first");
            case 1:
                return QString("second");
            case 2:
                return QString("third");
            }
        }
    }
    return QVariant();
}

void BudgetModel::dataUpdated()
{

}
