#ifndef REPORTOPTIMISATION_H
#define REPORTOPTIMISATION_H

#include <QtCore>
#include "core/treport.h"
#include "core/tmeasure.h"
#include "core/tparameterset.h"

class ReportOptimisation : public TReport
{
public:
    ReportOptimisation(QString name);

    void addMeasures(QList<TMeasure *> measures );
    void addIteration( int iteration , TParameterSet *paramSet, QMap<QString,double> parameters, double func_error );
    void addImage( QString name, QPixmap *pixmap );


private:
    QMap<QString,double> mPrevParameters;
    double mPrevFuncError;
};

#endif // REPORTOPTIMISATION_H
