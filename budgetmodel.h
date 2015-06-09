#ifndef BUDGETMODEL_H
#define BUDGETMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QDebug>
#include <QFont>
#include <QBrush>
#include "dbmanager.h"

class BudgetModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    BudgetModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    DBManager *db;

private slots:
    void dataUpdated();

signals:
    void updateView();

//    dataUpdated();
};

#endif // BUDGETMODEL_H
