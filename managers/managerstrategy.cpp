#include "managerstrategy.h"

#include "core/tdblayer.h"

ManagerStrategy::ManagerStrategy(TDevice *dev)
{
    device_ = dev;
}

bool ManagerStrategy::Create(QString name)
{
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery( "INSERT INTO strategies(name,device_id,dataset_id) VALUES(:name,:device_id,:dataset_id) " )
            ->bindValue(":name",name)
            ->bindValue(":device_id",device()->id())
            ->bindValue(":dataset_id",device()->strategyId())
            ->exec();

    if(!dbLayer->isRequested()){
        qDebug() << "MStrategy::Create : " << dbLayer->getError();
        delete dbLayer;
        return false;
    }
    delete dbLayer;

    return true;

}

bool ManagerStrategy::plotEnabled(QString name)
{
//    return mStrategy->plotEnabled(name);
    return true;
}

int ManagerStrategy::strategyId(QString name)
{
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT id FROM strategies WHERE name=:name")
            ->bindValue(":name",name)
            ->exec();

    int id =-1;
    if(dbLayer->isNext()){
        bool ok;
        id = dbLayer->value("id").toInt(&ok);
        if(!ok){
            id = -1;
        }
    }

    delete dbLayer;
    return id;
}

QString ManagerStrategy::datasetName()
{
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT name FROM datasets WHERE id=:id")
            ->bindValue(":id",device()->datasetId())
            ->exec();

    QString _dataset("");

    if(!dbLayer->isNext()){
        if(!dbLayer->isRequested()){
            qDebug() << dbLayer->getError();
        }
        delete dbLayer;
        return QString("");
    }


    _dataset =  dbLayer->value("name").toString();
    delete dbLayer;
    return _dataset;
}

 QList<STRATEGY_MEASURE> ManagerStrategy::measures(){


    QList<STRATEGY_MEASURE> _measures;
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT name,id FROM measures WHERE dataset_id=:dataset")
            ->bindValue(":dataset",device()->datasetId())
            ->exec();

    while(dbLayer->isNext()){
        STRATEGY_MEASURE _measure;
        _measure.id   = dbLayer->value("id").toInt();
        _measure.name = dbLayer->value("name").toString();
        _measure.inc  = ! strategy()->measureDisabled( _measure.id );

        _measures.append( _measure );
    }

    delete dbLayer;
    return _measures;

}

QList<int> ManagerStrategy::measureListId(bool only_enable)
{
    QList<int> _measures;
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT id FROM measures WHERE dataset_id=:dataset")
            ->bindValue(":dataset",device()->datasetId())
            ->exec();

    while(dbLayer->isNext()){
        int _id = dbLayer->value("id").toInt();
        _measures.append( _id );

    }

    delete dbLayer;
    return _measures;
}



//QStringList ManagerStrategy::datasets(){
//    TDBLayer *dbLayer = TDBLayer::getInstance();
//    dbLayer->bindQuery("SELECT name FROM datasets WHERE device_id=:dev_id")
//            ->bindValue(":dev_id",mDevice->id())
//            ->exec();

//    QStringList _datasets;

//    while(dbLayer->isNext()){
//        _datasets << dbLayer->value("name").toString();
//    }

//    return _datasets;
//}

QStringList ManagerStrategy::list(int device_id)
{
    QStringList _list;
    TDBLayer *dbLayer = TDBLayer::getInstance();

    if(device_id != -1){
        dbLayer->bindQuery("SELECT name FROM strategies WHERE device_id=:device")
                ->bindValue(":device",device_id)
                ->exec();
    }else{
        dbLayer->query("SELECT name FROM strategies");
    }

    while(dbLayer->isNext()){
        _list.append(  dbLayer->value("name").toString() );
    }

    delete dbLayer;
    return _list;


}
