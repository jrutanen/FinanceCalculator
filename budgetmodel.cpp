/* Copyright (C) 2015 Finance Calculator
 * (Jani Rutanen)
 *
 * This file is part of Financial Calculator.
 *
 * Financial Calculator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Financial Calculator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Financial Calculator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "budgetmodel.h"

BudgetModel::BudgetModel(QObject *parent) : QAbstractTableModel(parent)
{
    //    selectedCell = 0;
        db = new DBManager();
        month = 0;
        rows = 0;
        cols = 2;
        year = 2015;
        month = 1;
        day = 1;
        date.setDate(year, month, day);
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
            return dataSet.at(row).at(col + 1);
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
            case 2:
                return QString("Category");
            }
        }
    }

    return QVariant();
}

void BudgetModel::setMonth(int cbMonth)
{
    this->month = cbMonth;
}

void BudgetModel::setCols(int columns)
{
    cols = columns;
}

std::vector<double> BudgetModel::getCategorySummary()
{
    std::vector<double> values;
    //Food, Housing, Utilities, Transportation, Clothing, Personal, Saving, Total
    values.push_back(db->getSumFor(dataType , "Food", date));
    values.push_back(db->getSumFor(dataType , "Housing", date));
    values.push_back(db->getSumFor(dataType , "Utilities", date));
    values.push_back(db->getSumFor(dataType , "Transportation", date));
    values.push_back(db->getSumFor(dataType , "Clothing", date));
    values.push_back(db->getSumFor(dataType , "Personal", date));
    values.push_back(db->getSumFor(dataType , "Saving", date));
    values.push_back(db->getSumFor(dataType , "Total", date));

    return values;
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
        uint row = index.row();
        uint col = index.column();
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
        QStringList values;
        //update model data
        dataSet.at(row).replace(col + 1, value.toString());
        //update database
        if (dataSet.at(row).size() < 4)
        {
            values << dataSet.at(row).at(0) << dataSet.at(row).at(1) << dataSet.at(row).at(2);
        }
        else
        {
            values << dataSet.at(row).at(0) << dataSet.at(row).at(1) << dataSet.at(row).at(2) << dataSet.at(row).at(3);
        }
        updateData(values);

        //recalculate total
        dataSet.pop_front();
        dataSet.push_front(calculateTotal(dataSet));// at(0).replace(3, value.toString());

        //inform view that the cell has changed.
        emit dataChanged(index, index);
    } //if (role == Qt::EditRole)

    return true;
}

Qt::ItemFlags BudgetModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

void BudgetModel::setDataType(QString name)
{
    dataType = name;
    readData();
}

void BudgetModel::updateData(QStringList values)
{
    //actualExpenses, budgetedExpenses, income, loan, savings
    if(dataType.contains("actualExpenses"))
    {
        db->updateActualExpense(&values);
        emit modelDataUpdated();
    }
    else if (dataType.contains("budgetedExpenses"))
    {
        db->updateBudgetedExpense(&values);
        emit modelDataUpdated();
    }
    else if (dataType.contains("income"))
    {
        db->updateIncome(&values);
    }
    else if (dataType.contains("loan"))
    {
        db->updateLoan(&values);
    }
    else if (dataType.contains("savings"))
    {
        db->updateSavings(&values);
    }
}

QStringList BudgetModel::calculateTotal(std::deque<QStringList> data)
{
    double totalAmount = 0.0;
    for (uint i = 0; i < data.size(); ++i)
    {
        totalAmount += data.at(i).at(2).toDouble();
    }
    QStringList row;
    row <<"" << "Total" << QString::number(totalAmount) << "";
    return row;
}

void BudgetModel::addNewRow(QStringList newRow)
{
    int id = -1;
    //notify that expenses is appended
    beginInsertRows(QModelIndex(), dataSet.size()-1, dataSet.size()-1);
       //add new row to the dataset and get the id of the new row
       //actualExpenses, budgetedExpenses, income, loan, savings
       if(dataType.contains("actualExpenses"))
       {
           id = db->addActualExpense(&newRow , date);
           emit modelDataUpdated();
       }
       else if (dataType.contains("budgetedExpenses"))
       {
           id = db->addBudgetedExpense(&newRow , date);
           emit modelDataUpdated();
       }
       else if (dataType.contains("income"))
       {
           id = db->addIncome(&newRow , date);
       }
       else if (dataType.contains("loan"))
       {
           id = db->addLoan(&newRow , date);
       }
       else if (dataType.contains("savings"))
       {
           id = db->addSavings(&newRow , date);
       }
       if (id > -1)
       {
           newRow.replace(0, QString::number(id));
           dataSet.push_back(newRow);
       }
       else
       {
           readData();
       }
   //notify views that you're done with modifying the underlying data
   endInsertRows();
}

void BudgetModel::readData()
{
    beginResetModel();
        //actualExpenses, budgetedExpenses, income
        if(dataType.contains("actualExpenses"))
        {
            dataSet = db->getActualExpenses(date);
            dataSet.push_front(calculateTotal(dataSet));
        }
        else if (dataType.contains("budgetedExpenses"))
        {
            dataSet = db->getBudgetedExpenses(date);
            dataSet.push_front(calculateTotal(dataSet));
        }
        else if (dataType.contains("income"))
        {
            dataSet = db->getIncome(date);
            dataSet.push_front(calculateTotal(dataSet));
        }
        else if (dataType.contains("loan"))
        {
            dataSet = db->getLoan(date);
            dataSet.push_front(calculateTotal(dataSet));
        }
        else if (dataType.contains("savings"))
        {
            dataSet = db->getSavings(date);
            dataSet.push_front(calculateTotal(dataSet));
        }
    endResetModel();
}

void BudgetModel::addRow()
{
    int id = -1;
    QStringList row;
    row << ""<< "New Item" << "0.0" << "";
    //notify that expenses is appended
    beginInsertRows(QModelIndex(), dataSet.size()-1, dataSet.size()-1);
       //add new row to the dataset and get the id of the new row
       //actualExpenses, budgetedExpenses, income, loan, savings
       if(dataType.contains("actualExpenses"))
       {
           id = db->addActualExpense(&row , date);
           emit modelDataUpdated();
       }
       else if (dataType.contains("budgetedExpenses"))
       {
           id = db->addBudgetedExpense(&row , date);
           emit modelDataUpdated();
       }
       else if (dataType.contains("income"))
       {
           id = db->addIncome(&row , date);
       }
       else if (dataType.contains("loan"))
       {
           id = db->addLoan(&row , date);
       }
       else if (dataType.contains("savings"))
       {
           id = db->addSavings(&row , date);
       }
       if (id > -1)
       {
           row.replace(0, QString::number(id));
           dataSet.push_back(row);
       }
       else
       {
           readData();
       }
   //notify views that you're done with modifying the underlying data
   endInsertRows();
}

void BudgetModel::removeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row-1);
        if (row > 0)
        {
            //remove record from the database
            //actualExpenses, budgetedExpenses, income
            if(dataType.contains("actualExpenses"))
            {
                db->removeActualExpense(dataSet.at(row).at(0));
                emit modelDataUpdated();
            }
            else if (dataType.contains("budgetedExpenses"))
            {
                db->removeBudgetedExpense(dataSet.at(row).at(0));
                emit modelDataUpdated();
            }
            else if (dataType.contains("income"))
            {
                db->removeIncome(dataSet.at(row).at(0));
            }
            else if (dataType.contains("loan"))
            {
                db->removeLoan(dataSet.at(row).at(0));
            }
            else if (dataType.contains("savings"))
            {
                db->removeSavings(dataSet.at(row).at(0));
            }
        }
    endRemoveRows();

    readData();
}

void BudgetModel::changeMonth(int cbMonth)
{
    month = cbMonth;
    date.setDate(year, month, day);
    readData();
}

void BudgetModel::changeYear(QString cbYear)
{
    year = cbYear.toInt();
    date.setDate(year, month, day);
    readData();
}

void BudgetModel::copyFromPreviousMonth(QDate toDate)
{
    std::deque<QStringList> dataSetPreviousMonth;
    QDate fromDate = toDate.addMonths(-1);

    //actualExpenses, budgetedExpenses, income, loan, savings
    if(dataType.contains("actualExpenses"))
    {
        dataSetPreviousMonth = db->getActualExpenses(fromDate);
//        dataSet.push_front(calculateTotal(dataSet));
    }
    else if (dataType.contains("budgetedExpenses"))
    {
        dataSetPreviousMonth = db->getBudgetedExpenses(fromDate);
//        dataSet.push_front(calculateTotal(dataSet));
    }
    else if (dataType.contains("income"))
    {
        dataSetPreviousMonth = db->getIncome(fromDate);
//        dataSet.push_front(calculateTotal(dataSet));
    }
    else if (dataType.contains("loan"))
    {
        dataSetPreviousMonth = db->getLoan(fromDate);
//        dataSet.push_front(calculateTotal(dataSet));
    }
    else if (dataType.contains("savings"))
    {
        dataSetPreviousMonth = db->getSavings(fromDate);
//        dataSet.push_front(calculateTotal(dataSet));
    }
    for (uint i = 0; i < dataSetPreviousMonth.size(); ++i)
    {
        //row << ""<< "New Item" << "0.0" << "";
        QStringList row;
        if(!dataType.contains("Expenses"))
        {
            row << "" << dataSetPreviousMonth.at(i).at(1)
                      << dataSetPreviousMonth.at(i).at(2) << "";
        }
        else
        {
            row << "" << dataSetPreviousMonth.at(i).at(1)
                      << dataSetPreviousMonth.at(i).at(2)
                      << dataSetPreviousMonth.at(i).at(3)
                      << "";
        }
        addNewRow(row);
    }
    readData();
}
