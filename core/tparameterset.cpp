#include "tparameterset.h"
#include "core/tdblayer.h"

TParameterSet::TParameterSet()
{
    mID = -1;
}

TParameterSet::TParameterSet(int id)
{
    mID = id;
}



TParameterSet::TParameterSet(QString name,int device_id)
{
    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT id FROM parameter_sets WHERE name=:name AND device_id=:id")
            ->bindValue(":name",name)
            ->bindValue(":id",device_id)
            ->exec();
    if(dbLayer->isNext()){
        mID = dbLayer->value("id").toInt();
    }else{
        mID = -1;
    }
    mDeviceID = device_id;
    delete dbLayer;

}

TParameterSet::TParameterSet(TParameterSet &parameterSet){
    mParameters.clear();
    foreach(QString _name,parameterSet.parameters().keys()){
        PARAMETER_SET _set = parameterSet.parameters().value( _name );
        _set.id = -1;

        mParameters.insert( _name,_set );
    }


    mName = parameterSet.name();
    mID = -1;
    mDeviceID = parameterSet.device_id();
}

TParameterSet::~TParameterSet()
{
    mRemove.clear();
    mParameters.clear();
}

bool TParameterSet::Open(){

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT * FROM parameter_sets WHERE id=:id")
            ->bindValue(":id",id())
            ->exec();

    if(dbLayer->isNext()){

        mName = dbLayer->value("name").toString();
        mCreated = dbLayer->value("created").toDate();
        mChanged = dbLayer->value("changed").toDate();
        mDeviceID = dbLayer->value("device_id").toInt();
        // Open parameters

        dbLayer->bindQuery("SELECT * FROM parameters WHERE parameter_set_id=:id")
                ->bindValue(":id",id())
                ->exec();
        while(dbLayer->isNext()){

            PARAMETER_SET param;
            param.id = dbLayer->value("id").toInt();
            param.initial = dbLayer->value("initial").toDouble();
            param.minimum = dbLayer->value("minimum").toDouble();
            param.maximum = dbLayer->value("maximum").toDouble();
            param.fixed   = dbLayer->value("fixed").toBool();
            param.inc     = dbLayer->value("include").toBool();
            QString _name = dbLayer->value("name").toString();
            mParameters.insert(_name, param );

        }
        delete dbLayer;
        return true;
    }
    delete dbLayer;
    return false;

}

bool TParameterSet::Delete(int id){

    if(id <= 0){
        return false;
    }

    TDBLayer *dbLayer = TDBLayer::getInstance();


    bool res = dbLayer->bindQuery("DELETE FROM parameters WHERE id=:id")
            ->bindValue(":id",id)
            ->exec();

    if(res){
        foreach(QString _param,mParameters.keys()){
            if(mParameters[_param].id == id){
                mParameters.remove(_param);
                break;
            }
        }
    }else{
        qDebug() << dbLayer->getError();
    }
    delete dbLayer;

    return res;
}

bool TParameterSet::Delete(){

    if(id() <= 0){
        return false;
    }

    TDBLayer *dbLayer = TDBLayer::getInstance();


    bool res = dbLayer->bindQuery("DELETE FROM parameters WHERE parameter_set_id=:id")
            ->bindValue(":id",id())
            ->exec();

    if(res){

        res = dbLayer->bindQuery("DELETE FROM parameter_sets WHERE id=:id")
                ->bindValue(":id",id())
                ->exec();
    }

    if(res){
        mID = -1;
        mParameters.clear();
    }

    delete dbLayer;

    return res;

}

QMap<QString, double> TParameterSet::initials(){
    QMap<QString,double> _initial;

    foreach(QString name, mParameters.keys()){
        if(mParameters.value( name ).inc){
            _initial.insert( name, initial(name) );
        }
    }

    return _initial;
}

void TParameterSet::addParameter(QString name,double initial, double min, double max, bool fixed){

    PARAMETER_SET _param;


    if(mParameters.contains(name)){
        return;
    }

    _param.id = -1;
    _param.initial = initial;
    _param.minimum = min;
    _param.maximum = max;
    _param.fixed   = fixed;

    mParameters.insert( name, _param );

}

void TParameterSet::setParameter(QString name, double initial, double min, double max, bool fixed){

    if(mParameters.contains(name)){

        mParameters[name].initial = initial;
        mParameters[name].minimum = min;
        mParameters[name].maximum = max;
        mParameters[name].fixed   = fixed;

    }
}

void TParameterSet::setParameter(QString name, PARAMETER_SET set)
{
    mParameters.insert( name,set);
}

bool TParameterSet::Save(){
    TDBLayer *dbLayer = TDBLayer::getInstance();

    foreach(int _id,mRemove){
        if(!Delete(_id)){
            qDebug() << QString("Can't delete id:%d").arg(_id);
        }
    }

    if(id() == -1){
        dbLayer->bindQuery("INSERT INTO parameter_sets(device_id,name,created,changed) "
                           "VALUES(:dev_id,:name,:created,:changed)")
                ->bindValue(":dev_id",device_id())
                ->bindValue(":name",name())
                ->bindValue(":created",QDate::currentDate())
                ->bindValue(":changed",QDate::currentDate())
                ->exec();
        if(!dbLayer->isRequested()){
            delete dbLayer;
            return false;
        }

        mID = dbLayer->getInsertID();
    }

    foreach(QString _name,mParameters.keys()){

        PARAMETER_SET _set = mParameters.value( _name );

        if(_set.id == -1){
            dbLayer->bindQuery("INSERT INTO parameters(parameter_set_id,name,initial,optimized,minimum,maximum,fixed,include,changed) "
                               "VALUES(:id,:name,:initial,:optimized,:min,:max,:fix,:inc,:changed)")
                    ->bindValue(":id",id())
                    ->bindValue(":name",_name)
                    ->bindValue(":initial",_set.initial)
                    ->bindValue(":optimized",0.0)
                    ->bindValue(":min",_set.minimum)
                    ->bindValue(":max",_set.maximum)
                    ->bindValue(":fix",_set.fixed)
                    ->bindValue(":changed",QDate::currentDate())
                    ->bindValue(":inc",_set.inc)
                    ->exec();
            if(!dbLayer->isRequested()){
                qDebug() << dbLayer->getError();
                delete dbLayer;
                return false;
            }

        }else{
            dbLayer->bindQuery("UPDATE parameters SET name=:name, initial=:initial, optimized=:optimized, "
                               "minimum=:min, maximum=:max,fixed=:fix,changed=:changed,include=:inc WHERE id=:id")
                    ->bindValue(":name",_name)
                    ->bindValue(":initial",_set.initial)
                    ->bindValue(":optimized",0.0)
                    ->bindValue(":min",_set.minimum)
                    ->bindValue(":max",_set.maximum)
                    ->bindValue(":fix",_set.fixed)
                    ->bindValue(":changed",QDate::currentDate())
                    ->bindValue(":inc",_set.inc)
                    ->bindValue(":id",_set.id)
                    ->exec();

            if(!dbLayer->isRequested()){
                qDebug() << dbLayer->getError();
                delete dbLayer;
                return false;
            }

        }
    }
    delete dbLayer;
    return true;
}

void TParameterSet::setValue(QMap<QString, double> values)
{
    foreach(QString _name,values.keys()){

        if(mParameters.contains(_name)){
            mParameters[_name].initial = values.value(_name);
        }

    }
}

bool TParameterSet::exists(QString name){
    TDBLayer *dbLayer = TDBLayer::getInstance();

    bool _exists = true;
    dbLayer->bindQuery("SELECT id FROM parameter_sets WHERE name=:name")
            ->bindValue(":name",name)
            ->exec();
    _exists = dbLayer->isNext();

    delete dbLayer;
    return _exists;
}

QList<int> TParameterSet::listParameterSetByDeviceId(int device_id)
{
    QList<int> _list;
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT id FROM parameter_sets WHERE device_id=:id")
            ->bindValue(":id",device_id)
            ->exec();
    while(dbLayer->isNext()){
        _list << dbLayer->value( "id" ).toInt();
    }

    delete dbLayer;
    return _list;
}
