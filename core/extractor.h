#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <QtCore>
#include "core/tdevice.h"
#include "core/tstrategy.h"
#include "core/tdataset.h"
#include "core/tparameterset.h"
#include "defines.h"


/*
 * Device, Model, Strategy
*/
class Extractor : public QObject
{
    Q_OBJECT

public:
    enum ERROR_TYPE{ ERROR_ABSOLUTE, ERROR_RELATIVE };
    Extractor(int id);
    virtual ~Extractor();
    void runMinimisation();
    virtual void minimisation() = 0;

    TDevice *device(){                  return device_; }
    TParameterSet *parameterSet(){      return setParameter_; }
    int maxIterations(){                return maxIterations_; }
    int iteration(){                    return iteration_; }
    QMap<QString,double> parameters(){  return lastParameters_; }
    double computeFunctionError();

public slots:
    void Stop();

private:
    TDevice*            device_;
    TStrategy*          strategy_;
    TParameterSet*      setParameter_;
    QList<TMeasure*>    measures_;
    ERROR_TYPE          typeError_;
    TDevice* createDevice(int device_id);

protected:
    bool                 stopped_;
    int                  maxIterations_;
    int                  iteration_;
    QMutex               mutexFunctionError_;
    QMap<QString,double> lastParameters_;

    TStrategy* strategy(){ return strategy_; }
    void setParameter(QString name,double value);
    double paramValue(QString name);
    bool nextIteration();
    void doneExtraction();
    void saveParameters();
    bool isStop(){ return stopped_; }

signals:
    void doneIteration(int iteration,double error);
    void doneMinimisation();
};

#endif // EXTRACTOR_H
