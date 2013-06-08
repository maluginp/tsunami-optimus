#ifndef TPARAMETERSET_H
#define TPARAMETERSET_H

#include "core/tparameter.h"


typedef struct _PARAMETER_SET_{
    int id;
    QString name;
    double initial;
    double minimum;
    double maximum;
    bool fixed;
    bool inc;
} PARAMETER_SET;

class TParameterSet
{
public:
    TParameterSet();
    TParameterSet(int id);
    TParameterSet(QString name, int device_id);
    TParameterSet(TParameterSet &parameterSet);
    ~TParameterSet();
    bool Open();


    bool Delete(int id);
    bool Delete();

    int id(){
        return mID;
    }

    QString name(){
        return mName;
    }
    void setName(QString name){
        mName = name;
    }

    QMap<QString,double> initials();

    int id(QString name){
        return mParameters[name].id;
    }

    int device_id(){
        return mDeviceID;
    }
    void setDeviceID(int dev_id){
        mDeviceID = dev_id;
    }

    double min(QString name){
        return mParameters[name].minimum;
    }

    double initial(QString name){
        return mParameters[name].initial;
    }

    double max(QString name){
        return mParameters[name].maximum;
    }

    bool fixed(QString name){
        return mParameters[name].fixed;
    }
    bool included(QString name){
        return mParameters[name].inc;
    }

    QStringList parameterNames(){

        return parameterNames( false );
    }

    QStringList parameterNames(bool all);




    void addRemove( int id ){
        if(id != -1){
            mRemove.append( id );
        }
    }

    void addParameter(QString name,double initial,double min,double max,bool fixed);
    void setParameter(QString name,double initial,double min,double max,bool fixed);

    void setParameter(QString name,PARAMETER_SET set);

    bool Save();

    void setValue(QMap<QString,double> values );

    QMap<QString,PARAMETER_SET> parameters(){
        return mParameters;
    }

    static bool exists(QString name);
    static QList<int> listParameterSetByDeviceId(int device_id);

private:
    int mID;
    int mDeviceID;
    QString mName;
    QDate mChanged;
    QDate mCreated;
    QList<int> mRemove;

    QMap<QString,PARAMETER_SET> mParameters;
};

#endif // TPARAMETERSET_H
