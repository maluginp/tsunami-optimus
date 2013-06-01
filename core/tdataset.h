#ifndef TDATASET_H
#define TDATASET_H


#include <QtCore>
#include "core/tmeasure.h"
#include "core/tdblayer.h"
class TDataset
{
public:
    TDataset();
    TDataset(int id);
    ~TDataset();
    void setName(QString name){
        mName = name;
    }

    void setDeviceID(int device_id){
        mDeviceID = device_id;
    }

    int id(){
        return mID;
    }

    bool Open();
    bool Save();
    bool Delete();

    QList<TMeasure *> measures(){
        return mMeasures;
    }


    QMap<int,QString> measureList()
    {
        QMap<int,QString>  _items;
        foreach(TMeasure *measure,mMeasures){
            _items.insert(  measure->id(),  measure->name());
        }
        return _items;
    }

    QList<TMeasure *> measures(QList<int> filter);

    QString name(){
        return mName;
    }


    static QString name(int id);
    static QList<int> listDatasetByDeviceId(int device_id);
private:
    int mID;
    int mDeviceID;

    QString mName;

    QDate mCreated;
    QDate mChanged;


    QList<TMeasure *> mMeasures;

};

#endif // TDATASET_H
