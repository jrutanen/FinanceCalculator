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
    if(openDB())
    {
        works = createTables();
    }

    closeDB();
}

std::deque<QStringList> DBManager::getBudgetedExpenses(int month)
{
    std::deque<QStringList> temp;
    temp = getData("expense_budget", month);

    return temp;
}

std::deque<QStringList> DBManager::getActualExpenses(int month)
{
    std::deque<QStringList> temp;
    temp = getData("expense_actual", month);

    return temp;
}

std::deque<QStringList>  DBManager::getIncome(int month)
{
    std::deque<QStringList> temp;
    temp = getData("income_budget", month);

    return temp;
}

std::deque<QStringList> DBManager::getLoan(int month)
{
    std::deque<QStringList> temp;
    temp = getData("loans", month);

    return temp;
}

std::deque<QStringList> DBManager::getSavings(int month)
{
    std::deque<QStringList> temp;
    temp = getData("savings", month);

    return temp;
}

bool DBManager::updateBudgetedExpense(QStringList *list)
{
    qDebug() << QString("updateBudgetedExpense");
    bool dbUpdated = false;
    dbUpdated =  updateData(QString("expense_budget"), list);

    return dbUpdated;
}

bool DBManager::addBudgetedExpense(QStringList *list, int month)
{
    qDebug() << QString("addBudgetedExpense");
    bool dbUpdated = false;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("expense_budget"), list, month);
    }
    else
    {
        dbUpdated =  updateData(QString("expense_budget"), list);
    }

    return dbUpdated;
}

bool DBManager::removeBudgetedExpense(QString id)
{
    return removeData(QString("expense_budget"), id);
}

bool DBManager::updateActualExpense(QStringList *list)
{
    qDebug() << QString("updateActualExpense");
    bool dbUpdated = false;
    dbUpdated =  updateData(QString("expense_actual"), list);

    return dbUpdated;
}

bool DBManager::addActualExpense(QStringList *list, int month)
{
    qDebug() << QString("addActualExpense");
    bool dbUpdated = false;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("expense_actual"), list, month);
    }
    else
    {
        dbUpdated =  updateData(QString("expense_actual"), list);
    }

    return dbUpdated;
}

bool DBManager::removeActualExpense(QString id)
{
    return removeData(QString("expense_actual"), id);
}

bool DBManager::updateIncome(QStringList *list)
{
    qDebug() << QString("updateIncome");
    bool dbUpdated = false;
    dbUpdated =  updateData(QString("income_budget"), list);

    return dbUpdated;
}

bool DBManager::addIncome(QStringList *list, int month)
{
    qDebug() << QString("addIncome");
    bool dbUpdated = false;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("income_budget"), list, month);
    }
    else
    {
        dbUpdated =  updateData(QString("income_budget"), list);
    }

    return dbUpdated;
}

bool DBManager::removeIncome(QString id)
{
    return removeData(QString("income_budget"), id);
}

bool DBManager::updateLoan(QStringList *list)
{
    qDebug() << QString("updateLoan");
    bool dbUpdated = false;
    dbUpdated =  updateData(QString("loans"), list);

    return dbUpdated;
}

bool DBManager::addLoan(QStringList *list, int month)
{
    qDebug() << QString("addLoan");
    bool dbUpdated = false;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("loans"), list, month);
    }
    else
    {
        dbUpdated =  updateData(QString("loans"), list);
    }

    return dbUpdated;
}

bool DBManager::removeLoan(QString id)
{
    return removeData(QString("loans"), id);
}

bool DBManager::updateSavings(QStringList *list)
{
    qDebug() << QString("updateSavings");
    bool dbUpdated = false;
    dbUpdated =  updateData(QString("savings"), list);

    return dbUpdated;
}

bool DBManager::addSavings(QStringList *list, int month)
{
    qDebug() << QString("addSavings");
    bool dbUpdated = false;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("savings"), list, month);
    }
    else
    {
        dbUpdated =  updateData(QString("savings"), list);
    }

    return dbUpdated;
}

bool DBManager::removeSavings(QString id)
{
    return removeData(QString("savings"), id);
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
    dbPath.append("financeCalulatorDB.sqlite");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        return false;
    }
    return true;
}

bool DBManager::closeDB()
{
    db.close();
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
                      "type VARCHAR(255) NOT NULL, "
                      "amount REAL, "
                      "date VARCHAR(10), "
                      "category VARCHAR(100)"
                      ")");

            //actual expenses
            queryOk = queryOk && query.exec("CREATE TABLE IF NOT EXISTS expense_actual("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "type VARCHAR(255) NOT NULL, "
                      "amount REAL, "
                      "date VARCHAR(10), "
                      "category VARCHAR(100)"
                      ")");

            //budgeted income
            queryOk = queryOk && query.exec("CREATE TABLE IF NOT EXISTS income_budget("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "type VARCHAR(255) NOT NULL, "
                      "amount REAL, "
                      "date VARCHAR(10)"
                      ")");

            //loans
            queryOk = queryOk && query.exec("CREATE TABLE IF NOT EXISTS loans("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "type VARCHAR(255) NOT NULL, "
                      "amount REAL, "
                      "interest REAL, "
                      "date VARCHAR(10)"
                      ")");

            //savings
            queryOk = queryOk && query.exec("CREATE TABLE IF NOT EXISTS savings("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "type VARCHAR(255) NOT NULL, "
                      "amount REAL, "
                      "date VARCHAR(10)"
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
    qDebug() << QString("addData");

    openDB();

    if (!db.isOpen())
    {
        qDebug() << QString("db closed");
    }
    if (db.isOpen())
    {
        //all dates are first day of the month (this is monthly bydget)
        QString date = QString("%1-%2-01")
                       .arg(QDateTime::currentDateTime().toString("yyyy"))
                       .arg(intToDateMonth(month));

        QString queryString = "";

        QSqlQuery query(db);

        queryString.append(QString("INSERT INTO %1 (type, amount, date) "
                                   "VALUES ('%2', '%3', '%4')")
                                   .arg(tableName)
                                   .arg(data->at(1))
                                   .arg(data->at(2))
                                   .arg(date)
                                   );

        qDebug() << queryString;

        queryOk = query.exec(queryString);
    }

    closeDB();

    return queryOk;
}

bool DBManager::updateData(QString tableName, QStringList *data)
{
    bool queryOk = false;
    qDebug() << QString("updateData");

    openDB();

    if (!db.isOpen())
    {
        qDebug() << QString("db closed");
    }
    if (db.isOpen())
    {
        QString queryString = "";

        QSqlQuery query(db);

        queryString.append(QString("UPDATE %1 "
                                   "SET type='%2', amount='%3' "
                                   "WHERE id='%4'")
                                   .arg(tableName)
                                   .arg(data->at(1))
                                   .arg(data->at(2))
                                   .arg(data->at(0))
                                   );

        qDebug() << queryString;

        queryOk = query.exec(queryString);
    }

    closeDB();

    return queryOk;
}

bool DBManager::removeData(QString tableName, QString id)
{
    openDB();

    if (db.isOpen())
    {
        QString queryString = "";
        QSqlQuery query(db);

        queryString.append(QString("DELETE FROM %1 WHERE id='%2'")
                           .arg(tableName)
                           .arg(id));

        qDebug() << queryString;

        if(!query.exec(queryString))
        {
            qDebug() << QString("Could not remove record from expense_budget");
            return false;
        }
    }
    else
    {
        qDebug() << QString("DB is Closed!");
    }

    closeDB();

    return true;

}

std::deque<QStringList> DBManager::getData(QString tableName, int month)
{
    openDB();

    std::deque<QStringList> queryResult;// = new std::deque<QStringList>;
    if (db.isOpen())
    {
        QString date = QDateTime::currentDateTime().toString("yyyy")
                        + "-" + intToDateMonth(month) + "-01";
        qDebug() << date;
        QString queryString = "";
        QSqlQuery query(db);

        queryString.append(QString("SELECT * FROM %1 WHERE date='%2'")
                           .arg(tableName)
                           .arg(date));

        qDebug() << queryString;

        query.exec(queryString);

        while (query.next()) {
            QStringList list;
            list << query.value(0).toString()
                 << query.value(1).toString()
                 << query.value(2).toString()
                 << query.value(3).toString();

            qDebug() << QString("%1, %2, %3, %4")
                        .arg(query.value(0).toString())
                        .arg(query.value(1).toString())
                        .arg(query.value(2).toString())
                        .arg(query.value(3).toString());
            queryResult.push_back(list);
        }
    }
    else
    {
        qDebug() << QString("DB is Closed!");
    }

    closeDB();

    return queryResult;
}

QString DBManager::intToDateMonth(int month)
{
    QString dateMonth = "";

    if (month < 10)
    {
        dateMonth.append(QString("0%1")
                         .arg(month));
    }
    else
    {
        dateMonth.append(QString::number(month));
    }
    return dateMonth;
}
