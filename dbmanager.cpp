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
    qDebug() << dbPath;
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        return false;
    }
/*
    QSqlQuery query(db);
    query.prepare("PRAGMA foreign_keys = ON");

    if (!query.exec()) {
        qDebug() << QString("%1").arg(query.lastError().text());
        return false;
    }
*/
    return true;
}
