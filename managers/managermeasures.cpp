#include "managermeasures.h"
#include "core/tdblayer.h"

ManagerMeasures::ManagerMeasures(TDevice *device)
{
    setDevice(device);
    mDatasetID = -1;
}

ManagerMeasures::~ManagerMeasures(){
    mDatasetID = -1;
    mMeasureID = -1;
}

bool ManagerMeasures::CreateSet(QString name){

    if(name.isEmpty()){
        return false;
    }

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("INSERT INTO datasets(name,device_id,created,changed) "
                       "VALUES(:name,:dev_id,:created,:changed)")
            ->bindValue(":name",name)
            ->bindValue(":dev_id",device()->id())
            ->bindValue(":created",QDate::currentDate())
            ->bindValue(":changed",QDate::currentDate())
            ->exec();

    bool res =  dbLayer->isRequested();
    delete dbLayer;

    return res;

}

void ManagerMeasures::setDevice(TDevice *device)
{
    mDevice = device;
}

void ManagerMeasures::setDatasetID(int dataset_id)
{
    mDatasetID = dataset_id;
}

void ManagerMeasures::setDataset(QString name)
{
    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT id FROM datasets WHERE device_id=:id AND name=:name")
            ->bindValue(":id",device()->id())
            ->bindValue(":name",name)
            ->exec();

    if(!dbLayer->isNext()){
        setDatasetID(-1);
        return;
    }

    bool ok;
    int dataset_id = dbLayer->value("id").toInt(&ok);
    if(!ok){
        setDatasetID(-1);
        return;
    }

    setDatasetID( dataset_id );
    delete dbLayer;
    return;
}

bool ManagerMeasures::CreateMeasure(TMeasure *measure){
    return measure->Save();
}

bool ManagerMeasures::saveMeasure(QMap<QString,QVariant> info, QList<MEASURE_DB> databases){

    TMeasure measure;

    measure.setID( info["id"].toInt() );
    measure.setName( info["name"].toString() );
    measure.setAuthor( info["author"].toString() );
    measure.setPlotType( info["type"].toString() );
    measure.setMeasureDB( databases );
    measure.setSetting( info["settings"].toString() );

    measure.setDatasetID( dataset_id() );

    if(measure.Save()){
        mMeasureID = measure.id();
        return true;
    }

    return false;


}
TMeasure *ManagerMeasures::openMeasure(QString name){

    TMeasure *measure = new TMeasure(dataset_id(),name);

    measure->Open();

    return measure;
}

TMeasure *ManagerMeasures::openMeasure(int measure_id)
{
    TMeasure *measure = new TMeasure(measure_id);

    measure->Open();

    return measure;
}


QStringList ManagerMeasures::getColumnsName(QStringList exclude){
    QStringList _columns = getColumnsName(),
            _names;

    foreach(QString _name,_columns){
        if(!exclude.contains(_name)){
            _names << _name;
        }
    }

    return _names;
}


QStringList ManagerMeasures::getColumnsName()
{

    QStringList _names;
    foreach(TTerminal *_terminal,device()->terminals()){
        _names << "I"+_terminal->name().toLower();
        _names << "V"+_terminal->name().toLower();
    }

    return _names;
}

int ManagerMeasures::getMeasureID(QString dataset, QString measure)
{

    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery( "SELECT m.id AS id FROM measures AS m, datasets AS d "
                        "WHERE m.dataset_id = d.id AND d.name=:dataset "
                        "AND d.device_id=:dev_id AND m.name=:measure")
            ->bindValue(":dataset",dataset)
            ->bindValue(":dev_id",device()->id())
            ->bindValue(":measure",measure)
            ->exec();

    if(!dbLayer->isNext()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return -1;
    }


    int id;
    bool ok;
    id = dbLayer->value("id").toInt( &ok );
    if(!ok){
        delete dbLayer;
        return -1;
    }
    delete dbLayer;
    return id;
}



