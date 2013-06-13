#include "managerworkspace.h"

#include "devices/bjt.h"


ManagerWorkspace::ManagerWorkspace()
{
}

bool ManagerWorkspace::openDevice(int device_id)
{
    if(device_id != -1){

        layerDb_->bindQuery("SELECT name,device FROM devices WHERE id=:id")
                ->bindValue(":id",device_id)
                ->exec();

        if(layerDb_->isNext()){

            QString device_type = layerDb_->value("device").toString();


            TDevice *device = createDeviceObject( device_id, device_type );

            if(!device->Open()){
                qDebug() << "Device couldn't load";
            }

            setCurrentDevice( device );

//            emit deviceOpened();
            return true;


        }else{

            Log( QString("Couldn't open device %d").arg(device_id) );

        }

    }

    return false;
}

bool ManagerWorkspace::openDevice(QString name, QString device)
{
    TDBLayer  *dbLayer = TDBLayer::getInstance();


    dbLayer->bindQuery("SELECT id FROM devices WHERE name=:name AND device=:device")
            ->bindValue( ":name", name)
            ->bindValue(":device",device.toUpper())
            ->exec();

    if(!dbLayer->isNext()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return false;
    }

    bool ok;
    int id = dbLayer->value("id").toInt(&ok);

    if(ok){
        delete dbLayer;
        return openDevice(id);
    }

    delete dbLayer;
    return false;

}

TDevice *ManagerWorkspace::device()
{
    return deviceCurrent_;
}

bool ManagerWorkspace::showPolarityForm()
{
    return device()->hasPolarity();
}

bool ManagerWorkspace::showGroundForm()
{
    return true;
}

bool ManagerWorkspace::showImageDevice()
{
    return true;
}


void ManagerWorkspace::connectDatabase()
{
//#ifdef Q_OS_WIN
    layerDb_ = new TDBLayer(QDir::currentPath()+"/optimus.db");
//#else
//    mDBLayer = new TDBLayer("/Developer/Projects/tsunami-optimus/dbase/optimus.db");
//#endif
    if( !layerDb_->isOpened() ){
        Log("Database didn't open.");
    }
}

QMap<QString, QString> ManagerWorkspace::loadDataDevice()
{
    QMap<QString,QString> deviceData;

    deviceData.insert("model","");
    deviceData.insert("strategy","");
    deviceData.insert("parameters","");
    deviceData.insert("dataset","");


    layerDb_->bindQuery("SELECT m.name AS model FROM devices AS d, models AS m "
                        "WHERE d.model_id=m.id AND d.id=:id")
            ->bindValue(":id",device()->id())
            ->exec();
    if(layerDb_->isNext()){
        deviceData["model"]          =  layerDb_->value("model").toString();
    }else{
        qDebug() << layerDb_->getError();
    }

    layerDb_->bindQuery("SELECT s.name AS strategy FROM devices AS d, strategies AS s "
                        "WHERE d.strategy_id=s.id AND d.id=:id")
            ->bindValue(":id",device()->id())
            ->exec();
    if(layerDb_->isNext()){
        deviceData["strategy"]          =  layerDb_->value("strategy").toString();
    }else{
        qDebug() << layerDb_->getError();
    }

    layerDb_->bindQuery("SELECT p.name AS parameters FROM devices AS d, parameter_sets AS p "
                        "WHERE d.set_parameters_id=p.id AND d.id=:id")
            ->bindValue(":id",device()->id())
            ->exec();
    if(layerDb_->isNext()){
        deviceData["parameters"] = layerDb_->value("parameters").toString();
    }else{
        qDebug() << layerDb_->getError();
    }

    layerDb_->bindQuery("SELECT ds.name AS dataset FROM devices AS d, datasets AS ds "
                        "WHERE d.dataset_id=ds.id AND d.id=:id")
            ->bindValue(":id",device()->id())
            ->exec();
    if(layerDb_->isNext()){
        deviceData["dataset"] = layerDb_->value("dataset").toString();
    }else{
        qDebug() << layerDb_->getError();
    }


    return deviceData;
}

void ManagerWorkspace::setDataDevice(QString name, int data_id)
{
    if(name == "model"){

        layerDb_->bindQuery( "UPDATE devices  SET model_id=:id WHERE id=:dev_id" )
                ->bindValue(":id",data_id)
                ->bindValue(":dev_id",device()->id())
                ->exec();

        device()->setModelID( data_id );
    }else if(name == "strategy"){

        layerDb_->bindQuery( "UPDATE devices  SET strategy_id=:id WHERE id=:dev_id" )
                ->bindValue(":id",data_id)
                ->bindValue(":dev_id",device()->id())
                ->exec();
        device()->setStrategyID( data_id );
    }else if(name == "parameters"){

        layerDb_->bindQuery( "UPDATE devices  SET set_parameters_id=:id WHERE id=:dev_id" )
                ->bindValue(":id",data_id)
                ->bindValue(":dev_id",device()->id())
                ->exec();
        device()->setParametersID(data_id);
    }else if(name == "dataset"){
        layerDb_->bindQuery( "UPDATE devices  SET dataset_id=:id WHERE id=:dev_id" )
                ->bindValue(":id",data_id)
                ->bindValue(":dev_id",device()->id())
                ->exec();
        device()->setDatasetID( data_id );
    }
    else{

        Log("Incorrect name for setDataDevice()");
        return;

    }

    if(!layerDb_->isRequested()){
        Log("setDataDevice() return false after query");
        Log(layerDb_->getError());
    }


    return;
}

bool ManagerWorkspace::setSetting(QString name, QVariant value){
    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT settings FROM devices WHERE id=:id")
            ->bindValue(":id",device()->id())
            ->exec();
    if(!dbLayer->isNext()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return false;
    }

    QVariantMap _mapSettings =  device()->parseMap(dbLayer->value("settings").toString());

    _mapSettings.insert( name, value );

    QString _mapString = device()->createMap( _mapSettings );

    dbLayer->bindQuery("UPDATE devices SET settings=:settings WHERE id=:id")
            ->bindValue(":settings",_mapString)
            ->bindValue(":id",device()->id())
            ->exec();

    if(!dbLayer->isRequested()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return false;
    }

    device()->setSettings( name, value );

    delete dbLayer;
    return true;

}

void ManagerWorkspace::setCurrentDevice(TDevice *device)
{
    deviceCurrent_ = device;
}


void ManagerWorkspace::Log(QString log)
{
    qDebug() << log;
}

DEVICE_TYPE ManagerWorkspace::getDeviceType(QString device_type)
{
    device_type = device_type.toUpper();

    if(device_type == "BJT"){
        return DEVICE_BJT;
    }
    if(device_type == "DIODE"){
        return DEVICE_DIODE;
    }
    if(device_type == "JFET"){
        return DEVICE_JFET;
    }
    if(device_type == "MOSFET"){
        return DEVICE_MOSFET;
    }

    return DEVICE_UNDEF;
}

TDevice *ManagerWorkspace::createDeviceObject(int device_id, QString type)
{

    return TDevice::createObject(device_id,type);
//    TDevice *device;
//    DEVICE_TYPE deviceType = getDeviceType( type );

//    if(deviceType == DEVICE_UNDEF){
//        Log("Device Undefined");
//        return NULL;
//    }

//    switch(  deviceType ){
//    case DEVICE_BJT:
//        device = new BJT(device_id);
//        break;
//    }

//    return device;
}


bool ManagerWorkspace::isDatabaseOpened()
{
    return layerDb_->isOpened();
}
