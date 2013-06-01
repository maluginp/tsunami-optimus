#ifndef MANAGERSTRATEGY_H
#define MANAGERSTRATEGY_H

#include <QtCore>
#include "core/tdevice.h"
#include "core/tstrategy.h"

typedef struct _STRATEGY_MEASURE_{
    bool inc;
    int id;
    QString name;

} STRATEGY_MEASURE;

class ManagerStrategy
{
public:
    ManagerStrategy( TDevice *dev );

    bool Create(QString name);

    TDevice *device(){     return device_;   }
    TStrategy *strategy(){ return strategy_; }

    bool plotEnabled(QString name);

    void setId(int id){
        mId = id;
        strategy_ = new TStrategy(id);
        strategy_->Open();

    }
    int id(){ return mId; }

    int strategyId(QString name);
    QString datasetName();
    QList<STRATEGY_MEASURE> measures();
    QList<int> measureListId(bool only_enable);


    QStringList list(int device_id);
private:
    TDevice*   device_;
    TStrategy* strategy_;
    int        mId;
};

#endif // MANAGERSTRATEGY_H
