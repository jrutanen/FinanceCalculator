#ifndef CHARTVIEW_H
#define CHARTVIEW_H
#include<QGraphicsView>
#include<QDebug>
#include<QResizeEvent>


class ChartView : public QGraphicsView
{
    Q_OBJECT

public:
    ChartView(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:

};

#endif // CHARTVIEW_H
