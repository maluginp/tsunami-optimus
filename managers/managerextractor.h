#ifndef MANAGEREXTRACTOR_H
#define MANAGEREXTRACTOR_H

#include "core/tdevice.h"
#include "core/tstrategy.h"
#include "core/tparameterset.h"
#include "core/extractor.h"
#include "defines.h"

typedef struct _EXTRACTOR_PLOT_{
    QString constant;
    QVector<double> model_x;
    QVector<double> model_y;
    QVector<double> measure_x;
    QVector<double> measure_y;
} EXTRACTOR_PLOT;


class ManagerExtractor
{
public:
    ManagerExtractor();
    ~ManagerExtractor();
    bool openDevice(int device_id);

    void setCurrentDevice(TDevice *device){
        mDevice = device;
    }

    QList<EXTRACTOR_PLOT> plot(QString plot_type, QMap<TDevice::Axis,PLOT_AXIS_RANGE> &_ranges);

    QStringList plotNames();


    TDevice *device(){
        return mDevice;
    }

    TStrategy *strategy(){
        return mStrategy;
    }

    TParameterSet *parameterSet(){
        return mParameterSet;
    }


    Extractor *extractor(){
        return mExtractor;
    }

    void setMinimisator();




private:
    TDevice *mDevice;
    Extractor *mExtractor;
    TStrategy *mStrategy;
    TParameterSet *mParameterSet;
    QMutex mutex;
};

#endif // MANAGEREXTRACTOR_H
