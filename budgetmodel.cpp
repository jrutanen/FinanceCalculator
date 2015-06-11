#include "budgetmodel.h"

BudgetModel::BudgetModel(QObject *parent) : QAbstractTableModel(parent)
{
    //    selectedCell = 0;
        db = new DBManager();
        month = 0;
        rows = 0;
        cols = 2;
}

int BudgetModel::rowCount(const QModelIndex &parent) const
{
    return dataSet.size();
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
            return dataSet.at(row).at(col+1);
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

void BudgetModel::setMonth(int cbMonth)
{
    this->month = cbMonth;
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
        if(row > dataSet.size())
        {
            //New row
            dataSet.push_back(newList);
        }
        else
        {
            QStringList values;
            dataSet.at(row).replace(col + 1, value.toString());
            values << dataSet.at(row).at(0) << dataSet.at(row).at(1) << dataSet.at(row).at(2);
            updateData(values);
        }
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

void BudgetModel::setDataType(QString name)
{
    dataType = name;
    readData();
}

void BudgetModel::updateData(QStringList values)
{
    db->updateBudgetedExpense(&values);
}

void BudgetModel::readData()
{
    //actualExpenses, budgetedExpenses, income
    if(dataType.contains("actualExpenses"))
    {
        dataSet = db->getActualExpenses(month);
    }
    else if (dataType.contains("budgetedExpenses"))
    {
        dataSet = db->getBudgetedExpenses(month);
        qDebug()<< "read dataset from ";
    }
    else if (dataType.contains("income"))
    {
        dataSet = db->getIncome(month);
    }
}

void BudgetModel::writeData()
{
    for (uint i = 0; i < dataSet.size() ; ++i)
    {
        //actualExpenses, budgetedExpenses, income
        if(dataType.contains("actualExpenses"))
        {
          //  dataSet = db->getActualExpenses(month);
        }
        else if (dataType.contains("budgetedExpenses"))
        {
            db->addBudgetedExpense(&dataSet.at(i), month);
            qDebug()<< "adding expense to db";
        }
        else if (dataType.contains("income"))
        {
            dataSet = db->getIncome(month);
        }
    }
}

void BudgetModel::dataUpdated()
{

}

void BudgetModel::addRow()
{
    //notify that expenses is appended
   beginInsertRows(QModelIndex(), dataSet.size()-1, dataSet.size()-1);
       //add new row to the dataset with empty ID
        dataSet.push_back(QStringList() << ""<< "New Item" << "0.0");
   //notify views that you're done with modifying the underlying data
   endInsertRows();
   writeData();
   readData();
//    emit dataChanged();
}
