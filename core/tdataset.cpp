#include "tdataset.h"
#include "core/tdblayer.h"

TDataset::TDataset()
{
    mID = -1;
}

TDataset::TDataset(int id){
    mID = id;
}

TDataset::~TDataset()
{
    foreach(TMeasure *measure,mMeasures){
        delete measure;
    }

    mMeasures.clear();
}

bool TDataset::Open(){

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT * FROM datasets WHERE id=:id")
            ->bindValue(":id",id())
            ->exec();

    if(dbLayer->isNext()){

        mID = dbLayer->value( "id" ).toInt();
        mDeviceID = dbLayer->value("device_id").toInt();
        mCreated = dbLayer->value("created").toDate();
        mName = dbLayer->value("name").toString();


        dbLayer->bindQuery("SELECT * FROM measures WHERE dataset_id=:id")
                ->bindValue(":id",id())
                ->exec();

        while(dbLayer->isNext()){
            // Load measures
            int measure_id = dbLayer->value( "id" ).toInt();

            TMeasure *measure = new TMeasure(measure_id);
            if(measure->Open()){
                mMeasures.append( measure );
            }
        }

        delete dbLayer;
        return true;
    }else{
        TSLog( dbLayer->getError() );
    }

    delete dbLayer;
    return false;
}

bool TDataset::Save()
{
    TDBLayer *dbLayer = TDBLayer::getInstance();
    QDate _changed = QDate::currentDate();
    if(mID > 0){
        bool res = dbLayer->bindQuery("UPDATE datasets SET device_id=:dev_id,changed=:changed,name=:name WHERE id=:id")
                ->bindValue(":dev_id",mDeviceID)
                ->bindValue(":changed",_changed)
                ->bindValue(":name",mName)
                ->bindValue(":id",mID)
                ->exec();

        if(!res){
            qDebug() << dbLayer->getError();
            delete dbLayer;
            return false;
        }

    }else{
        bool res = dbLayer->bindQuery("INSERT INTO datasets(device_id,created,changed,name) "
                                      "VALUES(:dev_id,:created,:changed,:name)")
                ->bindValue(":dev_id",mDeviceID)
                ->bindValue(":changed",_changed)
                ->bindValue(":created",_changed)
                ->bindValue(":name",mName)
                ->exec();

        if(!res){
            qDebug() << dbLayer->getError();
            delete dbLayer;
            return false;
        }


    }

    delete dbLayer;
    return true;
}

bool TDataset::Delete(){
    TDBLayer *dbLayer = TDBLayer::getInstance();
    bool res = false;

    if(id() != -1){

        res = dbLayer->bindQuery("DELETE FROM datasets WHERE id=:id")
                ->bindValue(":id",id())
                ->exec();

        if(res){
            // Remove all measures
            res = dbLayer->bindQuery("DELETE FROM measures WHERE dataset_id=:id")
                    ->bindValue(":id",id())
                    ->exec();
        }

    }

    delete dbLayer;
    return res;

}


QList<TMeasure *> TDataset::measures(QList<int> filter){
    QList<TMeasure *> _measures;
    foreach( TMeasure *_measure,mMeasures ){
        if( ! filter.contains(_measure->id()) ){
            _measures.append( _measure );
        }
    }

    return _measures;
}

QList<int> TDataset::listDatasetByDeviceId(int device_id){\
    QList<int> _list;
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT id FROM datasets WHERE device_id=:id")
            ->bindValue(":id",device_id)
            ->exec();
    while(dbLayer->isNext()){
        _list << dbLayer->value( "id" ).toInt();
    }

    delete dbLayer;
    return _list;
}


QString TDataset::name(int id){
    QString _name("");
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT name FROM parameter_sets WHERE id=:id")
            ->bindValue(":id",id)
            ->exec();

    if(dbLayer->isNext()){
        _name = dbLayer->value("name").toString();
    }

    return _name;
}
