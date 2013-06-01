#ifndef FORMWEIGHTCONST_H
#define FORMWEIGHTCONST_H
#include <qcustomplot.h>
#include <QDialog>
#include <QtCore>

#include "core/tstrategy.h"

namespace Ui {
class FormWeightConst;
}



class FormWeightConst : public QDialog
{
    Q_OBJECT
    
public:
    explicit FormWeightConst(int strategy_id, int measure_id, QWidget *parent = 0);
    ~FormWeightConst();
    
private:
    Ui::FormWeightConst *ui;
//    QCPItemText *textLabel;
    QVector<STRATEGY_DB> mMeasures;
    int mLastClickGraph,
        mSelectedGraph,
        mColumnWeightIndex,
        mStrategyId,
        mMeasureId;


private slots:
//    void plottableDoubleClick(QCPAbstractPlottable* plot,QMouseEvent* mouse);
    void plottableClick(QCPAbstractPlottable* plot,QMouseEvent* mouse);
    void itemClick(QCPAbstractItem* item,QMouseEvent* event);
    void weightsTableClick(QModelIndex index);

    void SaveGraph();

    void weightsTableContextMenu(QPoint point);

    void weightsTableSetValueAction();
};

#endif // FORMWEIGHTCONST_H
