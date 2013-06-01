#include "extractor.h"
#include "minimisations/minimisations.h"
#include "core/tdblayer.h"
#include "core/tsetting.h"
#include "defines.h"


#define MAX_VALUE( val1, val2 ) ( (val1) > (val2) ?  (val1) : (val2) )

Extractor::Extractor( int id ){
    device_ =  createDevice( id ) ;
    device_->Open();

    device()->init();

    strategy_ = new TStrategy(device()->strategyId());
    strategy_->Open();

    setParameter_ = new TParameterSet( device()->parameterSetId() );

    if(!setParameter_->Open()){
        qDebug() << "parameters set didn't open";
    }

    // init
    QMap<QString,double> initial = setParameter_->initials();
    foreach( QString _param, initial.keys() ){
        device()->parameter( _param )->setValue(_param, initial.value(_param) );
    }

    TDataset *dataset = strategy_->dataset();

//    mMeasures = dataset->measures( mStrategy->excludePlots() );
    measures_ = dataset->measures(  );


    if(TSetting::isEq( "optimisation", "error", "absolute" )){
        typeError_ = ERROR_ABSOLUTE;
    }else{
        typeError_ = ERROR_RELATIVE;
    }
}

Extractor::~Extractor()
{
    delete device_;
    delete strategy_;
    delete setParameter_;

    lastParameters_.clear();
    measures_.clear();



}



void Extractor::runMinimisation(){

    setParameter_ = new TParameterSet( device()->parameterSetId() );
    if(!setParameter_->Open()){
        qDebug() << "parameters set didn't open";
    }

    // init
    QMap<QString,double> initial = setParameter_->initials();
    foreach( QString _param, initial.keys() ){
        device()->parameter( _param )->setValue(_param, initial.value(_param) );
    }

    minimisation();
}

void Extractor::Stop()
{
    stopped_ = true;
}

TDevice *Extractor::createDevice(int device_id)
{
    TDBLayer *dbLayer = TDBLayer::getInstance();
    if(device_id != -1){

        dbLayer->bindQuery("SELECT name,device FROM devices WHERE id=:id")
                ->bindValue(":id",device_id)
                ->exec();

        if(dbLayer->isNext()){

            QString device_type = dbLayer->value("device").toString();

            delete dbLayer;
            return TDevice::createObject( device_id, device_type );
        }
    }
    delete dbLayer;
    return NULL;

}


// #TODO: Для различных типов графиков своя функция ошибки?????
double Extractor::computeFunctionError(){

    QMutexLocker locker(&mutexFunctionError_);
    double _error = 0.0;
    QVector< QMap<TDevice::Axis,double> > _spiceValues;
    strategy()->beginDb();
    while( strategy()->isNextDb() ){
        double error_db = 0.0;
        strategy()->nextDb();
        MEASURE_DB _db = strategy()->measureDb();

        // нет проверки на steps
        // Симуляция SPICE модели
        if( _db.steps.count() != 1 ){
            // error_code
            continue;
        }

        QMap<QString,QVariant> _deviceSettings = strategy()->strategyDb().settings;
        foreach(QString _setName, _deviceSettings.keys()){
            device()->setSetting( _setName, _deviceSettings.value( _setName ) );
        }

        device()->setMeasureTerminal(_db.constants );
        device()->setSourceTerminal( _db.constants );

        _spiceValues = device()->simulate( strategy()->typeDb() ,
                            _db.steps.value(_db.steps.keys().at(0)) );

        int count_row = _db.table.count();
        for(int row=0; row < count_row;row++){
            QList<double> _row = _db.table.at(row).row;
            QMap<QString,double> _values = _db.constants;

            for(int col=0; col < _db.columns.count(); col++){
                _values.insert( _db.columns.at(col), _row.at(col) );
            }

            QMap<TDevice::Axis, double> _measureValues, _modelValues;

            _measureValues = device()->computeValue(strategy()->typeDb(), _values );

            bool _findValue=false;
            int _countSpiceValues = _spiceValues.count();
            for(int i=0; i < _countSpiceValues;i++){
                if(_spiceValues.at(i).value(TDevice::AXIS_X) == _measureValues.value( TDevice::AXIS_X )){
                    _modelValues = _spiceValues.at(i);
                    _findValue = true;
                    break;
                }
            }

            if(!_findValue){
                continue;
            }

            double _temp = 0.0;
            double _error_tmp=0.0;
            if( typeError_ == ERROR_ABSOLUTE ){
                //
                _temp   = _modelValues.value( TDevice::AXIS_Y ) - _measureValues.value( TDevice::AXIS_Y );
                _temp  /= strategy()->weight( _modelValues.value( TDevice::AXIS_X ));
                _error_tmp = (_temp * _temp);

                error_db += _error_tmp;
                _error += (_temp * _temp);
            }else{
                _temp   = MAX_VALUE( fabs(_modelValues.value( TDevice::AXIS_Y )), fabs(_measureValues.value(TDevice::AXIS_Y)) );
                if(_temp != 0.0){
                    _temp   = (fabs(_modelValues.value( TDevice::AXIS_Y )) - fabs(_measureValues.value( TDevice::AXIS_Y )))/_temp;
                    _temp  /= strategy()->weight( _modelValues.value( TDevice::AXIS_X ));
                    _error_tmp = (_temp * _temp);
                    error_db += _error_tmp;
                    _error += (_temp * _temp);
                }
            }
        }

    }


    return _error;

}

void Extractor::setParameter(QString name, double value){

    if(value != value){
        qDebug() << "NAN";
    }

    if(setParameter_->fixed(name)){
        return;
    }

    if(setParameter_->min(name) > value ){
        device_->parameter( name )->setValue( name, setParameter_->min(name) );
        return;
    }
    if(setParameter_->max(name) < value ){
        device_->parameter( name )->setValue( name, setParameter_->max(name) );
        return;
    }

     device_->parameter( name )->setValue( name, value );
     return;
}

double Extractor::paramValue(QString name)
{
    return device_->parameter(name)->value().toDouble();
}

bool Extractor::nextIteration()
{
    if(iteration_+1  > maxIterations_){
        return false;
    }
    iteration_++;
    return true;
}

inline void Extractor::doneExtraction() {
    delete device_;
    delete strategy_;
    delete setParameter_;
}

void Extractor::saveParameters(){
    QMutex lock;
    QMap<QString, double> _params;
    foreach(QString _name,parameterSet()->parameterNames()){
        _params.insert( _name, paramValue(_name) );
    }

    lock.unlock();

    lastParameters_ = _params;
    return;

}
