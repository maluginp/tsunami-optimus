#ifndef MANAGERMEASURES_H
#define MANAGERMEASURES_H

#include "core/tmeasure.h"
#include "core/tdevice.h"



class ManagerMeasures
{
public:
    ManagerMeasures(TDevice *device);
    ~ManagerMeasures( );
    bool CreateSet(QString name);

    void setDevice(TDevice *device);
    void setDatasetID(int dataset_id);
    void setDataset(QString name);

    TDevice *device(){
        return mDevice;
    }

    int dataset_id(){
        return mDatasetID;
    }

    int measure_id(){
        return mMeasureID;
    }

    bool CreateMeasure(TMeasure *measure);

    bool saveMeasure(QMap<QString, QVariant> info, QList< MEASURE_DB > databases);
    TMeasure *openMeasure(QString name);
    TMeasure *openMeasure(int measure_id);

    QStringList getColumnsName(QStringList exclude);
    QStringList getColumnsName();


    int getMeasureID(QString dataset,QString measure);
private:
    TDevice *mDevice;
    int mDatasetID;
    int mMeasureID;
};

#endif // MANAGERMEASURES_H
