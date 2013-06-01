#ifndef TSTRATEGY_H
#define TSTRATEGY_H

#include <QtCore>
#include "core/tdataset.h"
#include "core/tmeasure.h"

typedef struct _GRAPH_WEIGHTS_{
    QMap<QString,double> constants;
    QMap< double, double  > weights;
} GRAPH_WEIGHTS;

//typedef struct _MEASURE_WEIGHT_{
//    double X;
//    double Y;
//    double weight;
//} MEASURE_WEIGHT;

typedef struct _DATASET_STRATEGY_{

    int id;
    QList<int> measures;

} DATASET_STRATEGY;


typedef struct _STRATEGY_DB_{
    int measure_id;
    QString type;
    MEASURE_DB db;
    QMap<double,double> weights;
    QMap<QString,QVariant> settings;

} STRATEGY_DB;

class TStrategy
{
public:
    TStrategy();
    TStrategy(int id);
    ~TStrategy();
    bool Open();
    bool Save();
    bool Delete();

    bool measureDisabled(int id){
        return mDataset.measures.contains(id);
    }

    int id(){
        return mID;
    }

    void setDatasetStrategy(DATASET_STRATEGY strategy){
        mDataset = strategy;
    }

    void setDatasetId(int dataset_id){
        mDatasetId = dataset_id;
    }
    void setIncludeMeasures( QList<int> inc ){
        mIncludeMeasure = inc;
    }

    TDataset *dataset();
    QList<TMeasure *> measures(bool only_enable);


//    QMap<double,double> weights(int measure_id, QMap<QString,double> constant);

    bool isIncludeWeight(){
        return mIncludeWeight;
    }
    void setIncludeWeight(bool inc){
        mIncludeWeight = inc;
    }

    int countDb();

    void beginDb();
    bool isNextDb();

    STRATEGY_DB nextDb();
    QString typeDb();
    MEASURE_DB measureDb();
    STRATEGY_DB strategyDb();

    double weight(double x);
    static GRAPH_WEIGHTS findWeightByConst(QVector<GRAPH_WEIGHTS> weights, QMap<QString,double> constants);

//    QMap<double,double> weights();
    static QVector<STRATEGY_DB> measures(int strategy_id, int measure_id );
//    double weight( double X, double Y );

    static int deviceIdByStrategyId( int strategy_id );

    QList<int> measures_id();
    bool saveWeights( QVector<STRATEGY_DB> strategy_dbs );

    static QList<int> listStrategyByDeviceId(int device_id);
private:

    int mID;
    QString mName;
    int mDeviceId,
        mDatasetId;
    bool mIncludeWeight;
    QVector< STRATEGY_DB > mMeasures;
    int mCurrentDb;
    QList<int> mIncludeMeasure;

    // Dataset
    DATASET_STRATEGY mDataset;

    QVector<GRAPH_WEIGHTS> openWeights(int measure_id );

//    void appendMeasure( STRATEGY_DB db );
//    void appendMeasures( int measure_id );
//    void appendMeasures( TMeasure *measure );
};

#endif // TSTRATEGY_H
