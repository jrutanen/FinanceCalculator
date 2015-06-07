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

#include "dbmanager.h"

DBManager::DBManager()
{
    bool works = false;
    works = openDB();
    if (works)
    {
        qDebug() << QString("Works? %1").arg(works);
    }
}

QStringList DBManager::getBudgetedExpenses(int month)
{
    QStringList *temp = new QStringList();
    return *temp;
}

QStringList DBManager::getActualExpenses(int month)
{
    QStringList *temp = new QStringList();
    return *temp;
}

QStringList DBManager::getIncome(int month)
{
    QStringList *temp = new QStringList();
    return *temp;
}

QStringList DBManager::getLoan(int month)
{
    QStringList *temp = new QStringList();
    return *temp;
}

QStringList DBManager::getSavings(int month)
{
    QStringList *temp = new QStringList();
    return *temp;
}

bool DBManager::addBudgetedExpense(QStringList *list, int month)
{
    return addData(QString("expense_budget"), list, month);
}

bool DBManager::addActualExpense(QStringList *list, int month)
{
    return addData(QString("expense_actual"), list, month);
}

bool DBManager::addIncome(QStringList *list, int month)
{
    return addData(QString("income_budget"), list, month);
}

bool DBManager::addLoan(QStringList *list, int month)
{
    return addData(QString("loans"), list, month);
}

bool DBManager::addSavings(QStringList *list, int month)
{
    return addData(QString("savings"), list, month);
}

/**
 * @brief Opens the database
 * @return bool db.open()
 */
bool DBManager::openDB()
{

    if (QSqlDatabase::contains("financeCalculatorDB"))
    {
        db = QSqlDatabase::database("financeCalculatorDB");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE", "financeCalculatorDB");
    }

    dbPath = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory);
    dbPath.append("FinanceCalculator/financeCalulatorDB.sqlite");
//    qDebug() << dbPath;
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        return false;
    }

    return true;
}

/**
 * @brief Creates all the tables
 * @return bool
 */
bool DBManager::createTables()
{
    bool queryOk = false;

    if (db.isOpen())
    {
        QSqlQuery query(db);

        if(!db.tables().contains("expense_budget"))
        {
            //database tables need to be created

            //budgeted expenses
            queryOk = query.exec("CREATE TABLE IF NOT EXISTS expense_budget("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "cost_type VARCHAR(255) NOT NULL, "
                      "cost_amount REAL, "
                      "cost_budget_date VARCHAR(10)"
                      ")");

            //actual expenses
            queryOk = queryOk && query.exec("CREATE TABLE IF NOT EXISTS expense_actual("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "actual_cost_type VARCHAR(255) NOT NULL, "
                      "actual_cost_amount REAL, "
                      "actual_cost_date VARCHAR(10)"
                      ")");

            //budgeted income
            queryOk = queryOk && query.exec("CREATE TABLE IF NOT EXISTS income_budget("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "income_type VARCHAR(255) NOT NULL, "
                      "income_amount REAL, "
                      "income_budget_date VARCHAR(10)"
                      ")");

            //loans
            queryOk = queryOk && query.exec("CREATE TABLE IF NOT EXISTS loans("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "creditor VARCHAR(255) NOT NULL, "
                      "loan_amount REAL, "
                      "loan_yearly_interest REAL, "
                      "loan_budget_date VARCHAR(10)"
                      ")");

            //savings
            queryOk = queryOk && query.exec("CREATE TABLE IF NOT EXISTS savings("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "savings_type VARCHAR(255) NOT NULL, "
                      "savings_amount REAL, "
                      "savings_date VARCHAR(10)"
                      ")");


            // Config table (for update purposes)
            queryOk = queryOk && query.exec("CREATE TABLE IF NOT EXISTS config("
                                            "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                                            "parameter VARCHAR(255) NOT NULL, "
                                            "value VARCHAR(255) NOT NULL"
                                            ")");

        }
    }
    return queryOk;
}

bool DBManager::addData(QString tableName, QStringList *data, int month)
{
    bool queryOk = false;
    if (db.isOpen())
    {
//        QString dateOne = QDateTime::currentDateTime();
        QString date = QDateTime::currentDateTime().toString("YYYY") + "-" + month + "-01";
        QString queryString = "";
        QSqlQuery query(db);

        queryString.append("INSERT INTO %1 VALUES").arg(tableName);

        qDebug() << queryString;

        for (int i = 0; i < data->size(); i++)
        {
            queryString.append(data->at(i));
            if (i < data->size() - 1) queryString.append(",");
        }

        qDebug() << queryString;
        /*
        queryOk = query.exec("INSERT INTO "
                             + tableName
                             + "VALUES "
                             + data->at(0) + ","
                             + data->at(1) + ","
                             + month + ","
                            ")");
        */
    }

    return queryOk;
}
