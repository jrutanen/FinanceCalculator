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
    //safety check for index
    if(!index.isValid())
    {
        return QVariant();
    }

    int row = index.row();
    int col = index.column();

    switch(role)
    {
        case Qt::DisplayRole:
            return dataSet.at(row).at(col+1);
            break;
        case Qt::FontRole:
            if (row == 0) //change font only for cell(0,0)
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
    //safety check for index
    if(!index.isValid())
    {
        return false;
    }

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
    readData();
}

QStringList BudgetModel::calculateTotal(std::deque<QStringList> data)
{
    double totalAmount = 0.0;
    for (int i = 0; i < data.size(); ++i)
    {
        totalAmount += data.at(i).at(2).toDouble();
    }
    QStringList row;
    row <<"" << "Total" << QString::number(totalAmount);
    return row;
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
//        dataSet = db->getBudgetedExpenses(month);
        dataSet = db->getBudgetedExpenses(month);
        dataSet.push_front(calculateTotal(dataSet));
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
//            dataSet = db->getIncome(month);
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
       //actualExpenses, budgetedExpenses, income
       if(dataType.contains("actualExpenses"))
       {
           QStringList row;
           row << ""<< "New Item" << "0.0";
           readData();
       }
       else if (dataType.contains("budgetedExpenses"))
       {
           QStringList row;
           row << ""<< "New Item" << "0.0";
           db->addBudgetedExpense(&row , month);
           readData();
           qDebug()<< "updated dataset and row";
       }
       else if (dataType.contains("income"))
       {
           //dataSet = db->getIncome(month);
       }       //add new row to the dataset with empty ID
   //notify views that you're done with modifying the underlying data
   endInsertRows();
}

void BudgetModel::removeRow(int row)
{
    /*A removeRows() implementation must call beginRemoveRows() before the
    * rows are removed from the data structure, and it must call endRemoveRows()
    * immediately afterwards.*/

    beginRemoveRows(QModelIndex(), row, row-1);
        if (row > 0)
        {
            //remove record from the database
            db->removeBudgetedExpense(dataSet.at(row).at(0));
            readData();
        }
    endRemoveRows();
}

void BudgetModel::changeMonth(int cbMonth)
{
    month = cbMonth;
    readData();
}
