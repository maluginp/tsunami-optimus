#include "tstrategy.h"
#include "core/tdblayer.h"

#include <QtXml>

TStrategy::TStrategy(){
    mID = -1;
}

TStrategy::TStrategy(int id)
{
    mID = id;
}

TStrategy::~TStrategy(){
    //    mPlots.clear();
    //    mFilters.clear();

    mDataset.measures.clear();

}

bool TStrategy::Open(){


    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT * FROM strategies WHERE id=:id")
            ->bindValue(":id",id())
            ->exec();

    QList<int> _measures_id;

    if(!dbLayer->isNext()){
        delete dbLayer;
        return false;
    }

    mName = dbLayer->value("name").toString();
    mDeviceId = dbLayer->value("device_id").toInt();
    // mDatasetId = ;
    mDatasetId = dbLayer->value("dataset_id").toInt();

    mIncludeWeight = dbLayer->value("inc_weight").toBool();

    QStringList _measures = dbLayer->value("measures").toString().split(",");
    foreach(QString _measure,_measures){
        _measures_id <<  _measure.toInt();
    }

    mIncludeMeasure = _measures_id;

    mMeasures.clear();

    TDataset *dataset = new TDataset( mDatasetId );
    if(dataset->Open()){
        foreach(TMeasure *measure,dataset->measures()){
            if(!_measures_id.contains(measure->id()) ){
                continue;
            }

            QVector<GRAPH_WEIGHTS> _weights = openWeights( measure->id() );

            QList<MEASURE_DB> _dbs = measure->databases();
            int count_db = _dbs.count();
            for(int i=0; i < count_db;i++){
                MEASURE_DB _db = _dbs.at(i);

                if(!_db.inc){
                    continue;
                }

                // Clear table
                QList< MEASURE_ROW > _cleared_table;
                int count_row = _db.table.count();
                for(int row=0; row < count_row; row++){
                    if(_db.table.at(row).inc){
                        _cleared_table.append( _db.table.at(row) );
                    }
                }
                if(_cleared_table.count() == 0){
                    continue;
                }

                _db.table = _cleared_table;

                STRATEGY_DB _strategy_db;
                GRAPH_WEIGHTS _weight = findWeightByConst( _weights, _db.constants );

                _strategy_db.type       = measure->plotType();
                _strategy_db.measure_id = measure->id();
                _strategy_db.db         = _db;
                _strategy_db.weights    = _weight.weights;
                _strategy_db.settings   = measure->settingMap();

                mMeasures.append( _strategy_db );

            }

        }
    }


    delete dataset;
    delete dbLayer;
    return true;
}

// #TODO
bool TStrategy::Save(){
    TDBLayer *dbLayer = TDBLayer::getInstance();
    if(id() > 0){

        // Save plots
        //        foreach(QString _plot,mPlots.keys()){

        //            dbLayer->bindQuery("UPDATE strategy_plots SET enable=:enable WHERE plot=:plot AND strategy_id=:id")
        //                    ->bindValue(":enable",plotEnabled(_plot))
        //                    ->bindValue(":plot",_plot)
        //                    ->bindValue(":id",id())
        //                    ->exec();
        //            if(!dbLayer->isRequested()){
        //                qDebug() << dbLayer->getError();
        //                delete dbLayer;
        //                return false;
        //            }
        //        }

        QStringList _values;
        foreach(int _measure_id,mIncludeMeasure){
            _values << QString::number( _measure_id );
        }
        QString _value = _values.join(",");

//        int inc_w = 0;
//        if(mIncludeWeight){
//            inc_w = 1;
//        }
        // Save measures
        dbLayer->bindQuery("UPDATE strategies SET measures=:measures, dataset_id=:dataset, inc_weight=:inc_w WHERE id=:id")
                ->bindValue(":dataset",mDatasetId)
                ->bindValue(":measures",_value)
                ->bindValue(":id",id())
                ->bindValue(":inc_w",mIncludeWeight)
                ->exec();

        if(!dbLayer->isRequested()){
            qDebug() << dbLayer->getError();
            delete dbLayer;
            return false;
        }

    }else{

    }
    delete dbLayer;
    return true;
}

bool TStrategy::Delete()
{
    TDBLayer *dbLayer = TDBLayer::getInstance();
    bool res = false;

    if(id() != -1){

        res = dbLayer->bindQuery("DELETE FROM strategies WHERE id=:id")
                ->bindValue(":id",id())
                ->exec();
        if(res){
            res = dbLayer->bindQuery("DELETE FROM strategy_weights WHERE strategy_id=:id")
                    ->bindValue(":id",id())
                    ->exec();

        }

    }

    delete dbLayer;
    return res;
}


TDataset *TStrategy::dataset(){

    TDataset *dataset = new TDataset(mDataset.id);

    if(!dataset->Open()){
        qDebug() << "Dataset didn't open";
    }

    return dataset;

}

QList<TMeasure *> TStrategy::measures(bool only_enable){
    QList<TMeasure *> _measures;


    TDataset *dataset = new TDataset(mDataset.id);

    if(dataset->Open()){
        if(only_enable){
            _measures = dataset->measures( mDataset.measures );
        }else{
            QList<int> _empty;
            _measures = dataset->measures( _empty );
        }
    }

    //    delete  dataset;

    return _measures;
}

int TStrategy::countDb(){
return mMeasures.count();
}

int TStrategy::deviceIdByStrategyId(int strategy_id)
{
    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT device_id FROM strategies WHERE id=:id")
            ->bindValue(":id",strategy_id)
            ->exec();

    if(!dbLayer->isNext()){
        delete dbLayer;
        return -1;
    }
    bool ok;
    int device_id = dbLayer->value( "device_id" ).toInt(&ok);
    if(!ok){
        device_id = -1;
    }

    return device_id;
}

QList<int> TStrategy::measures_id(){
   return mIncludeMeasure;
}

bool TStrategy::saveWeights(QVector<STRATEGY_DB> strategy_dbs)
{
    if(strategy_dbs.count() <= 0){
        return false;
    }

    int count_db = strategy_dbs.count();
    int measure_id = strategy_dbs.at(0).measure_id;

    QDomDocument xml_doc;
    QDomElement xml_w = xml_doc.createElement( "w" );

    for(int i=0; i < count_db; i++){
        STRATEGY_DB _db = strategy_dbs.at(i);

        if(_db.weights.count() == 0){
            continue;
        }

        QDomElement xml_r = xml_doc.createElement("r");

        // const
        foreach(QString _constName,_db.db.constants.keys()){
            QDomElement xml_c = xml_doc.createElement( "c" );
            xml_c.setAttribute( "n", _constName );
            xml_c.setAttribute( "v", _db.db.constants.value(_constName) );

            xml_r.appendChild( xml_c );
        }
        foreach( double key, _db.weights.keys() ){

            QDomElement xml_i = xml_doc.createElement( "i" );
            xml_i.setAttribute( "x", key );
            xml_i.setAttribute( "w", _db.weights.value(key,1.0) );

            xml_r.appendChild( xml_i );
        }


        xml_w.appendChild( xml_r );
    }
    xml_doc.appendChild( xml_w );

    QString _data = xml_doc.toString(0);

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT 1 FROM strategy_weights WHERE strategy_id=:str_id AND measure_id=:meas_id")
            ->bindValue(":str_id",id())
            ->bindValue(":meas_id",measure_id)
            ->exec();

    if( dbLayer->count() != 0){
        dbLayer->bindQuery("UPDATE strategy_weights SET data=:data WHERE strategy_id=:str_id AND measure_id=:meas_id")
                ->bindValue(":data",_data)
                ->bindValue(":str_id",id())
                ->bindValue(":meas_id",measure_id)
                ->exec();
    }else{
        dbLayer->bindQuery("INSERT INTO strategy_weights(strategy_id,measure_id,data) VALUES(:str_id,:meas_id,:data)")
                ->bindValue(":data",_data)
                ->bindValue(":str_id",id())
                ->bindValue(":meas_id",measure_id)
                ->exec();

    }

    if(!dbLayer->isRequested()){
       delete dbLayer;
        return false;

    }

    delete dbLayer;
    return true;

}

QList<int> TStrategy::listStrategyByDeviceId(int device_id){

    QList<int> _list;
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT id FROM strategies WHERE device_id=:id")
            ->bindValue(":id",device_id)
            ->exec();
    while(dbLayer->isNext()){
        _list << dbLayer->value( "id" ).toInt();
    }

    delete dbLayer;
    return _list;

}


//QStringList TStrategy::plots(bool only_enable)
//{
//    QStringList _plots;
//    if(only_enable){
//        foreach(QString _plot,mPlots.keys()){
//            if(mPlots.value(_plot)){
//                _plots.append( _plot );
//            }
//        }
//    }else{
//        _plots = mPlots.keys();
//    }

//    return _plots;
//}


void TStrategy::beginDb(){
    mCurrentDb = -1;
}

bool TStrategy::isNextDb()
{

    if( mCurrentDb+1 <  mMeasures.count() ){
        return true;
    }

    return false;

}

STRATEGY_DB TStrategy::nextDb(){
    if(isNextDb()){
        mCurrentDb++;
        return mMeasures.at(  mCurrentDb );
    }

    STRATEGY_DB _db;
    return _db;
}

QString TStrategy::typeDb(){
    //    QString _type("");
    return mMeasures.at( mCurrentDb ).type;
}

MEASURE_DB TStrategy::measureDb()
{
    return mMeasures.at( mCurrentDb ).db;
}

STRATEGY_DB TStrategy::strategyDb()
{
    return mMeasures.at( mCurrentDb );
}

double TStrategy::weight(double x){

    if(!mIncludeWeight){
        return 1.0;
    }

    QMap<double, double> _weights = mMeasures.at(mCurrentDb).weights;
    double _value = _weights.value( x, 1.0 );

    return _value;
}

GRAPH_WEIGHTS TStrategy::findWeightByConst(QVector<GRAPH_WEIGHTS> weights, QMap<QString, double> constants){

    int count_w = weights.count();
    int count_repeat = constants.count();

    for(int i=0; i < count_w; i++){

        int repeat = 0;
        GRAPH_WEIGHTS _weight = weights.at(i);

        foreach(QString _constName, constants.keys() ){
            if(_weight.constants.value(_constName,INFINITY) == constants.value(_constName)){
                repeat++;
            }
        }

        if(repeat == count_repeat){
            return _weight;
        }

    }
    GRAPH_WEIGHTS _weight;
    return _weight;
}

QVector<STRATEGY_DB> TStrategy::measures(int strategy_id, int measure_id){

    QVector<STRATEGY_DB> _vec;

    TMeasure *measure = new TMeasure(measure_id);
    if(!measure->Open()){
        delete measure;
        return _vec;
    }

    TStrategy *strategy = new TStrategy(strategy_id);
    QVector<GRAPH_WEIGHTS> _graph_weights = strategy->openWeights( measure_id );

    delete strategy;

    QList<MEASURE_DB> _dbs = measure->databases();
    for(int i=0; i < _dbs.count();i++){
        MEASURE_DB _db = _dbs.at(i);

        if(!_db.inc){
            continue;
        }

        GRAPH_WEIGHTS _graph_weight = TStrategy::findWeightByConst( _graph_weights, _db.constants );

        QList< MEASURE_ROW > _cleared_table;
        int count_row = _db.table.count();
        for(int row=0; row < count_row; row++){
            if(_db.table.at(row).inc){
                _cleared_table.append( _db.table.at(row) );
            }
        }
        if(_cleared_table.count() == 0){
            continue;
        }

        _db.table = _cleared_table;

        STRATEGY_DB _strategy_db;
        _strategy_db.db = _db;
        _strategy_db.measure_id = measure_id;
        _strategy_db.type = measure->plotType();
        _strategy_db.weights = _graph_weight.weights;

        _vec.append(  _strategy_db );
    }

    return _vec;
}


QVector<GRAPH_WEIGHTS> TStrategy::openWeights(int measure_id){

    QVector<GRAPH_WEIGHTS> _vec;

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT data FROM strategy_weights WHERE strategy_id=:str_id AND measure_id=:meas_id")
            ->bindValue(":str_id",id())
            ->bindValue(":meas_id",measure_id)
            ->exec();


    if(!dbLayer->isNext()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return _vec;
    }

    QString data = dbLayer->value("data").toString();

    if(!data.isEmpty()){
        QDomDocument xml_doc;
        xml_doc.setContent( data );

        QDomElement xml_begin = xml_doc.firstChildElement();

        QDomNodeList _weights = xml_begin.elementsByTagName("r");
        for(int i=0; i < _weights.count(); i++){

            QDomElement _weight = _weights.at(i).toElement();

            //const
            QMap<QString,double> _constValues;
            QDomNodeList _consts = _weight.elementsByTagName("c");
            for(int j=0; j < _consts.count();j++){

                QDomElement _const = _consts.at(j).toElement();

                QString _name = _const.attribute( "n", "" );
                double _value = _const.attribute("v", "11111111").toDouble();

                if(_name.isEmpty() || _value == 11111111){
                    continue;
                }

                _constValues.insert(_name,_value);
            }

            //item
            QMap<double,double> _weightValues;
            QDomNodeList _items = _weight.elementsByTagName("i");
            for(int j=0; j < _items.count(); j++){

                QDomElement _item = _items.at(j).toElement();
                double _name = _item.attribute( "x", "11111111" ).toDouble();
                double _value = _item.attribute( "w", "11111111" ).toDouble();

                if(_name == 11111111 || _value == 11111111){
                    continue;
                }

                _weightValues.insert( _name, _value );

            }

            GRAPH_WEIGHTS _graph_weight;
            _graph_weight.constants = _constValues;
            _graph_weight.weights   = _weightValues;

            _vec.append( _graph_weight );

        }
    }

    delete dbLayer;
    return _vec;

}
