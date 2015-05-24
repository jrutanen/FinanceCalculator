#ifndef DATASET_H
#define DATASET_H

#include<QString>
#include<vector>

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
