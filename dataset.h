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

#ifndef DATASET_H
#define DATASET_H

#include<QString>
#include<vector>

//!  DataSet class.
/*!
  This class is not used currently. To be deleted.
*/
class DataSet
{
public:
    DataSet();
    DataSet( std::vector <double>, QString, QString );
    std::vector<double> getData();
    QString getName();
private:
    std::vector<double> data;
    QString name;
    QString unit;
};

#endif // DATASET_H
