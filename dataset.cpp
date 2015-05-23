#include "dataset.h"

DataSet::DataSet()
{

}

DataSet::DataSet(std::vector<double> d, QString n, QString u)
{
    data = d;
    name = n;
    unit = u;
}
std::vector<double> DataSet::getData()
{
    return data;
}

