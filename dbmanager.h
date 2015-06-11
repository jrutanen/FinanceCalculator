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
#include <QDateTime>

class DBManager
{
public:
    DBManager();
    std::vector<QStringList> getBudgetedExpenses(int month);
    std::vector<QStringList> getActualExpenses(int month);
    std::vector<QStringList> getIncome(int month);
    std::vector<QStringList> getLoan(int month);
    std::vector<QStringList> getSavings(int month);
    bool updateBudgetedExpense(QStringList *list);
    bool addBudgetedExpense(QStringList *list, int month);
    bool addActualExpense(QStringList *list, int month);
    bool addIncome(QStringList *list, int month);
    bool addLoan(QStringList *list, int month);
    bool addSavings(QStringList *list, int month);

private:
    QSqlDatabase db;
    bool openDB();
    bool createTables();
    QString dbPath;
    bool addData(QString tableName, QStringList *data, int month);
    bool updateData(QString tableName, QStringList *data);
    bool newData(QString tableName, QStringList *data, int month);
    std::vector<QStringList> getData(QString tableName, int month);
    QString intToDateMonth(int month);
};

#endif // DBMANAGER_H
