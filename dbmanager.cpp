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

std::deque<QStringList> DBManager::getBudgetedExpenses(QDate date)
{
    std::deque<QStringList> temp;
    temp = getData("expense_budget", date);

    return temp;
}

std::deque<QStringList> DBManager::getActualExpenses(QDate date)
{
    std::deque<QStringList> temp;
    temp = getData("expense_actual", date);

    return temp;
}

std::deque<QStringList>  DBManager::getIncome(QDate date)
{
    std::deque<QStringList> temp;
    temp = getData("income_budget", date);

    return temp;
}

std::deque<QStringList> DBManager::getLoan(QDate date)
{
    std::deque<QStringList> temp;
    temp = getData("loans", date);

    return temp;
}

std::deque<QStringList> DBManager::getSavings(QDate date)
{
    std::deque<QStringList> temp;
    temp = getData("savings", date);

    return temp;
}

bool DBManager::updateBudgetedExpense(QStringList *list)
{
    qDebug() << QString("updateBudgetedExpense");
    bool dbUpdated = false;
    dbUpdated =  updateData(QString("expense_budget"), list);

    return dbUpdated;
}

int DBManager::addBudgetedExpense(QStringList *list, QDate date)
{
    qDebug() << QString("addBudgetedExpense");
    int dbUpdated = -1;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("expense_budget"), list, date);
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

int DBManager::addActualExpense(QStringList *list, QDate date)
{
    qDebug() << QString("addActualExpense");
    int dbUpdated = -1;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("expense_actual"), list, date);
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

int DBManager::addIncome(QStringList *list, QDate date)
{
    qDebug() << QString("addIncome");
    int dbUpdated;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("income_budget"), list, date);
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

int DBManager::addLoan(QStringList *list, QDate date)
{
    qDebug() << QString("addLoan");
    int dbUpdated;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("loans"), list, date);
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

int DBManager::addSavings(QStringList *list, QDate date)
{
    qDebug() << QString("addSavings");
    int dbUpdated;
    if (list->at(0).isEmpty())
    {
        dbUpdated =  addData(QString("savings"), list, date);
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

double DBManager::getSumFor(QString dataType, QString category, QDate date)
{
    QString tableName;
    if(dataType.contains("actualExpenses"))
    {
        tableName = "expense_actual";
    }
    else
    {
        tableName = "expense_budget";
    }

    openDB();

    double queryResult;

    if (db.isOpen())
    {
        QString queryString = "";
        QSqlQuery query(db);
        if(!category.contains("Total"))
        {
            queryString.append(QString("SELECT SUM(amount) FROM %1 WHERE date='%2' AND category='%3'")
                               .arg(tableName)
                               .arg(date.toString("yyyy-MM-dd"))
                               .arg(category));
        }
        else
        {
            queryString.append(QString("SELECT SUM(amount) FROM %1 WHERE date='%2'")
                               .arg(tableName)
                               .arg(date.toString("yyyy-MM-dd")));
        }

        qDebug() << queryString;

        query.exec(queryString);

        while (query.next()) {
            queryResult = query.value(0).toInt();
        }
    }
    else
    {
        qDebug() << QString("DB is Closed!");
    }

    closeDB();

    return queryResult;
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

int DBManager::addData(QString tableName, QStringList *data, QDate date)
{
    bool queryOk = false;
    int rowId = -1;
    qDebug() << QString("addData");

    openDB();

    if (!db.isOpen())
    {
        qDebug() << QString("db closed");
    }
    if (db.isOpen())
    {
        //all dates are first day of the month (this is monthly bydget)
//        QString date = QString("%1")
//                       .arg(QDate::currentDateTime().toString(date));

        QString queryString = "";

        QSqlQuery query(db);

        if(!tableName.contains("expense"))
        {
            queryString.append(QString("INSERT INTO %1 (type, amount, date) "
                                   "VALUES ('%2', '%3', '%4')")
                                   .arg(tableName)
                                   .arg(data->at(1))
                                   .arg(data->at(2))
                                   .arg(date.toString("yyyy-MM-dd"))
                                   );
        }
        else
        {
            queryString.append(QString("INSERT INTO %1 (type, amount, date, category) "
                                   "VALUES ('%2', '%3', '%4', '%5')")
                                   .arg(tableName)
                                   .arg(data->at(1))
                                   .arg(data->at(2))
                                   .arg(date.toString("yyyy-MM-dd"))
                                   .arg(data->at(3))
                                   );

        }
        qDebug() << queryString;

        queryOk = query.exec(queryString);
        if (queryOk)
        {
            rowId = query.lastInsertId().toInt();
        }
    }

    closeDB();

    return rowId;
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

        if(!tableName.contains("expense"))
        {
            queryString.append(QString("UPDATE %1 "
                                       "SET type='%2', amount='%3' "
                                       "WHERE id='%4'")
                                       .arg(tableName)
                                       .arg(data->at(1))
                                       .arg(data->at(2))
                                       .arg(data->at(0))
                                       );
        }
        else
        {
            queryString.append(QString("UPDATE %1 "
                                       "SET type='%2', amount='%3', category='%4' "
                                       "WHERE id='%5'")
                                       .arg(tableName)
                                       .arg(data->at(1))
                                       .arg(data->at(2))
                                       .arg(data->at(3))
                                       .arg(data->at(0))
                                       );

        }

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

std::deque<QStringList> DBManager::getData(QString tableName, QDate date)
{
    openDB();

    std::deque<QStringList> queryResult;// = new std::deque<QStringList>;
    if (db.isOpen())
    {
//        QString date = QDate::currentDateTime().toString(date);
        qDebug() << date;
        QString queryString = "";
        QSqlQuery query(db);

        queryString.append(QString("SELECT * FROM %1 WHERE date='%2'")
                           .arg(tableName)
                           .arg(date.toString("yyyy-MM-dd")));

        qDebug() << queryString;

        query.exec(queryString);

        while (query.next()) {
            QStringList list;
            if (!tableName.contains("expense"))
            {
                list << query.value(0).toString()
                     << query.value(1).toString()
                     << query.value(2).toString()
                     << query.value(3).toString();

                qDebug() << QString("%1, %2, %3, %4")
                            .arg(query.value(0).toString())
                            .arg(query.value(1).toString())
                            .arg(query.value(2).toString())
                            .arg(query.value(3).toString());

            }
            else
            {
                list << query.value(0).toString()
                     << query.value(1).toString()
                     << query.value(2).toString()
                     << query.value(4).toString()
                     << query.value(3).toString();

                qDebug() << QString("%1, %2, %3, %4, %5")
                            .arg(query.value(0).toString())
                            .arg(query.value(1).toString())
                            .arg(query.value(2).toString())
                            .arg(query.value(4).toString())
                            .arg(query.value(3).toString());

            }
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
