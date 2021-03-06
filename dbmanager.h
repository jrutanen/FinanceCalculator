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

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql/QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardPaths>
#include <QDate>
#include <deque>

//!  DBManager class.
/*!
  This class is the creates database for the budget data if needed and handles all
  transactions with the created database.
*/
class DBManager
{
public:
    //! A constructor.
    /*!
      Constructor for DBManager class.
    */
    DBManager();

    //! A method to read budgeted expenses from the database for a given month.
    /*!
      \param month a int number of the month (1 to 12).
      \return deque<QStringList> with data rows for the month from the database
      \sa DBManager()
    */
    std::deque<QStringList> getBudgetedExpenses(QDate date);

    //! A method to read actual expenses from the database for a given month.
    /*!
      \param month a int number of the month (1 to 12).
      \return deque<QStringList> with data rows for the month from the database
      \sa DBManager()
    */
    std::deque<QStringList> getActualExpenses(QDate date);

    //! A method to read budgeted income from the database for a given month.
    /*!
      \param month a int number of the month (1 to 12).
      \return deque<QStringList> with data rows for the month from the database
      \sa DBManager()
    */
    std::deque<QStringList> getIncome(QDate date);

    //! A method to read loan balances from the database for a given month.
    /*!
      \param month a int number of the month (1 to 12).
      \return deque<QStringList> with data rows for the month from the database
      \sa DBManager()
    */
    std::deque<QStringList> getLoan(QDate date);

    //! A method to read savings balance from the database for a given month.
    /*!
      \param month a int number of the month (1 to 12).
      \return deque<QStringList> with data rows for the month from the database
      \sa DBManager()
    */
    std::deque<QStringList> getSavings(QDate date);

    //! A method to update budgeted expense row in the database.
    /*!
      \param *list a pointer to a QStringList containing the row to be updated.
      \return true if update was succesful, false if not.
      \sa DBManager()
    */
    bool updateBudgetedExpense(QStringList *list);

    //! A method to add new expense to the budgeted expenses in the database for a given month.
    /*!
      \param *list a pointer to the QStringList containing the row to be added.
      \param month a int number of the month (1 to 12).
      \return id of the inserted row as integer, -1 if insert was not successful.
      \sa DBManager()
    */
    int addBudgetedExpense(QStringList *list, QDate date);

    //! A method to remove expense from the budgeted expenses in the database.
    /*!
      \param id for the datarecord in the database
      \return true if removal was succesful, false if not.
      \sa DBManager()
    */
    bool removeBudgetedExpense(QString id);

    //! A method to update actual expense row in the database.
    /*!
      \param *list a pointer to a QStringList containing the row to be updated.
      \return true if update was succesful, false if not.
      \sa DBManager()
    */
    bool updateActualExpense(QStringList *list);

    //! A method to add new expense to the actual expenses in the database for a given month.
    /*!
      \param *list a pointer to the QStringList containing the row to be added.
      \param month a int number of the month (1 to 12).
      \return id of the inserted row as int
      \sa DBManager()
    */
    int addActualExpense(QStringList *list, QDate date);

    //! A method to remove actual expense from the budgeted expenses in the database.
    /*!
      \param id for the datarecord in the database
      \return true if removal was succesful, false if not.
      \sa DBManager()
    */
    bool removeActualExpense(QString id);

    //! A method to update budgeted income row in the database.
    /*!
      \param *list a pointer to a QStringList containing the row to be updated.
      \return true if update was succesful, false if not.
      \sa DBManager()
    */
    bool updateIncome(QStringList *list);

    //! A method to add new income row to the database for a given month.
    /*!
      \param *list a pointer to the QStringList containing the row to be added.
      \param month a int number of the month (1 to 12).
      \return id of the inserted row as int
      \sa DBManager()
    */
    int addIncome(QStringList *list, QDate date);

    //! A method to remove income row from the database.
    /*!
      \param id for the datarecord in the database
      \return true if removal was succesful, false if not.
      \sa DBManager()
    */
    bool removeIncome(QString id);

    //! A method to update loan row in the database.
    /*!
      \param *list a pointer to a QStringList containing the row to be updated.
      \return true if update was succesful, false if not.
      \sa DBManager()
    */
    bool updateLoan(QStringList *list);

    //! A method to add new loan row to the database for a given month.
    /*!
      \param *list a pointer to the QStringList containing the row to be added.
      \param month a int number of the month (1 to 12).
      \return id of the inserted row as integer, -1 if insert was not successful.
      \sa DBManager()
    */
    int addLoan(QStringList *list, QDate date);

    //! A method to remove loan row from the database.
    /*!
      \param id for the datarecord in the database
      \return true if removal was succesful, false if not.
      \sa DBManager()
    */
    bool removeLoan(QString id);

    //! A method to update savings row in the database.
    /*!
      \param *list a pointer to a QStringList containing the row to be updated.
      \return true if update was succesful, false if not.
      \sa DBManager()
    */
    bool updateSavings(QStringList *list);

    //! A method to add new savings row to the database for a given month.
    /*!
      \param *list a pointer to the QStringList containing the row to be added.
      \param month a int number of the month (1 to 12).
      \return id of the inserted row as int -1 if insert was not successful.
      \sa DBManager()
    */
    int addSavings(QStringList *list, QDate date);

    //! A method to remove savings row from the database.
    /*!
      \param id for the datarecord in the database
      \return true if removal was succesful, false if not.
      \sa DBManager()
    */
    bool removeSavings(QString id);

    //! A method to get sum for categories in the table.
    /*!
      \param category QString for the category in the database
      \return sum of all values in that category.
      \sa DBManager()
    */
    double getSumFor(QString dataType, QString category, QDate date);

private:
    //! Variable to store the database info.
    /*!
      Database handler.
    */
    QSqlDatabase db;

    //! A method to open database connection.
    /*!
      \sa DBManager()
    */
    bool openDB();

    //! A method to close database connection.
    /*!
      \sa DBManager()
    */
    bool closeDB();

    //! A method to create database tables if not already existing.
    /*!
      \sa DBManager()
    */
    bool createTables();

    //! Variable to store the path to the sqlite database file.
    /*!
      File path to the sqlite database. Stored in the shared application files folder
      specific to each operating system.
    */
    QString dbPath;

    //! A method to add datarow to the database.
    /*!
      \param tableName QString with name for the table where data is added
      \param *data pointer to the QStringList containing the data for the row to be added
      \param month int containing the number of the month (1-12). Month value is used to calculate
             date value for the data row. All items are stored to the first day of the given month.
      \return id for the inserted row as integer, -1 if the insert was not succesful.
      \sa DBManager()
    */
    int addData(QString tableName, QStringList *data, QDate date);

    //! A method to update datarow in the database.
    /*!
      \param tableName QString with name for the table where data is updated
      \param *data pointer to the QStringList containing the data for the row to be updated
      \return true if update was succesful, false if not.
      \sa DBManager()
    */
    bool updateData(QString tableName, QStringList *data);

    //! A method to remove datarow from the database.
    /*!
      \param tableName QString with name for the table where data is updated
      \param id QString containing the id for the data record to be removed.
      \return true if update was succesful, false if not.
      \sa DBManager()
    */
    bool removeData(QString tableName, QString id);

    //! A method to fetch data records from the database.
    /*!
      \param tableName QString with name for the table where data is updated
      \param month a int for the month (1 to 12) from which records are wanted.
      \return deque<QStringList> containing the fetched records.
      \sa DBManager()
    */
    std::deque<QStringList> getData(QString tableName, QDate date);

    //! A method to convert month number integer (1 to 12) to string (01 to 12) that can be used in date.
    /*!
      \param month a int for the month (1 to 12).
      \return QString containing the month number if format 01, 02 ... 12
      \sa DBManager()
    */
    QString intToDateMonth(int month);
};

#endif // DBMANAGER_H
