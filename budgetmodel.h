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

#ifndef BUDGETMODEL_H
#define BUDGETMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QDebug>
#include <QFont>
#include <QBrush>
#include <deque>
#include <QDate>
#include "dbmanager.h"

//!  BudgetModel class.
/*!
  This class is the model for the budget shown in the tableview for budgeted
  expenses and income. Same model is also used for actual expenses. BudgetModel
  class inherits QAbstactTableModel class.
*/

class BudgetModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    //! A constructor.
    /*!
      Constructor for BudgetModel class.
    */
    BudgetModel(QObject *parent);

    //! A overriden virtual method taking one argument and returning an integer value.
    /*!
      \param &parent a QModelIndex.
      \return Number of rows in the data
      \sa BudgetModel()
    */
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;

    //! A overriden virtual method taking one argument and returning an integer value.
    /*!
      \param &parent a QModelIndex.
      \return Number of columns in the data
      \sa BudgetModel()
    */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    //! A overriden virtual method taking two arguments and returning QVariant value.
    /*!
      \param &index a QModelIndex containing row, column and parent for the requested data.
      \param role Qt::displayRole.
      \return Requested data rows from the model
      \sa BudgetModel(), Qt::FontRole, Qt::DisplayRole
    */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    //! A overriden virtual method taking tree arguments and returning QVariant value.
    /*!
      This method returns headers for the tableview
      \param section a QModelIndex containing row, column and parent for the requested data.
      \param orientation a Qt::Orientation to mark if header for row or column is returned.
      \param role interger value for Qt::DisplayRole.
      \return Requested data rows from the model
      \sa BudgetModel(), Qt::Orientation, Qt::DisplayRole
    */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /*! A overriden virtual method taking tree arguments and returning bool value.
      This method handles edited values in the model and updates database with the values.
      \param section a QModelIndex containing row, column and parent for the edited data.
      \param value a QVariant containing the new value for the index.
      \param role interger value for Qt::EditRole.
      \return true if update was successful, otherwise returns false.
      \sa BudgetModel(), Qt::EditRole
    */
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex & index) const;

    /*! A method to set the type of data object contains (budgeted expense, actual expense, income, savings or investment).
      \param name a QString containing datatype.
      \sa BudgetModel()
    */
    void setDataType(QString name);

    /*! A method to change the Month that the data will be displayed for.
      \param cbMonth a int containing month number (1 to 12).
      \sa BudgetModel()
    */
    void setMonth(int cbMonth);

    /*! A method to change the number of columns in the model.
      \param cols a int containing month number columns.
      \sa BudgetModel()
    */
    void setCols(int columns);

private:
    //! Pointer to the database.
    /*!
      This variable is pointer to the database for budget information.
    */
    DBManager *db;

    //! Stores type of the data in the object
    /*!
      This variable stores information regaring the type of the data the object contains.
      Data type is used to use the correct infomation in the database. Possible values are
      budgetedExpenses, actualExpenses, income, savings and loans.
    */
    QString dataType; //actualExpenses, budgetedExpenses, income, savings, loans

    //! Stores number of rows in the data table
    int rows;

    //! Stores number of columns in the data table (default is 2)
    int cols;

    //! Stores the number of the month for the data (1 to 12)
    int month;

    //! Stores the year for the data
    int year;

    //! Stores the year for the data
    int day;

    //! Stores the year for the data
    QDate date;

    //! Stores the total sum of values for the datatype
    double sum;

    //! This variable contains the list of datarows in the model
    /*!
      This variable stores the data rows as QStringList. Each row has four QString variables,
      id (record id in the database), title, amount and category of the budget item. First row of
      the dataSet contain summary row with empty id and empty category. Title for the first row is
      Total and the amount is the total amount from all the items from 1 to size()-1.
    */
    std::deque<QStringList> dataSet;

    /*! Method to read all data from the database for the current datatype and month.
      First this method replaces content of the dataSet variable with the data from database.
      Secondly this method adds the summary row to the top of the dataset.
      \sa BudgetModel()
    */
    void readData();

    /*! Method to writes values to the database.
      This method updates database with new values.
      \param values a QStringList containing values for one row.
      \sa BudgetModel()
    */
    void updateData(QStringList values);

    /*! Method calculates sum of all amount fiels in budget items.
      This method iterates through the dataSet and calculates total
      sum for the amount field.
      \param data a deque<QStringList> containing values for the model.
      \return QStringList with four QStrings [""]["total"][sum of amounts][""]
      \sa BudgetModel()
    */
    QStringList calculateTotal(std::deque<QStringList> data);

    /*! Method adds new row to the database and notifies view of the change.
     *  \param newRow an QStringList.
        \sa BudgetModel()
     */
    void addNewRow(QStringList newRow);

private slots:
    /*! \fn void addRow()
     *  \brief slot to add new row to the model. Function adds row with content "New Item", "0.0", ""
     *  \param row an integer.
     */
    void addRow();

    /*! \fn removeRow(int row)
     *  \brief Removes row from the model and updates database.
     *  \param row an integer.
     */
    void removeRow(int row);

    /*! \fn void changeMonth(int cbMonth)
     *  \brief Changes month in the model
     *  \param cbMonth an integer.
     */
    void changeMonth(int cbMonth);

    /*! \fn void changeYear(QString year)
     *  \brief Changes year in the model
     *  \param year as QString.
     */
    void changeYear(QString cbYear);

    /*! \fn void copyFromPreviousMonth(QDate toDate)
     *  \brief Copies entries from previous month to the model
     *  \param toDate as QDate.
     */
    void copyFromPreviousMonth(QDate toDate);

signals:

};

#endif // BUDGETMODEL_H
