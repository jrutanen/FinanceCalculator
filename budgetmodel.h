#ifndef BUDGETMODEL_H
#define BUDGETMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QDebug>
#include <QFont>
#include <QBrush>
#include <QSqlQuery>
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
    void setMonth(int month);
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const ;

private:
    DBManager *db;
    int rows;
    int cols;
    int month;
    double sum;
    std::vector<QStringList> expenses;
    void readData();
    void writeData();

private slots:
    void dataUpdated();
    void addRow();

signals:
    void updateView();
    void editCompleted(const QString &);
    void dataChanged();
};

#endif // BUDGETMODEL_H
