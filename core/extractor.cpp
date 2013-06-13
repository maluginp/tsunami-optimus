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

double Extractor::normalizeDouble(const double val, const int digits){
    double power = pow(10, digits);
    return floor((val * power) + 0.5) / power;
}


// #TODO: Для различных типов графиков своя функция ошибки?????
double Extractor::computeFunctionError(){

//    QFile* file = new QFile("function_error.txt");
//    if(!file->open(QIODevice::WriteOnly)){
//        //
//    }
//    file->write("X\tYsim\tYmea\tError\n");

    QMutexLocker locker(&mutexFunctionError_);
    double _error = 0.0;
    QVector< QPointF > _spiceValues;
    strategy()->beginDb();
    while( strategy()->isNextDb() ){
        strategy()->nextDb();
        MEASURE_DB _db = strategy()->measureDb();

        QMap<QString,STEP_RANGE> ranges = strategy()->getDbRanges();
        QMap<QString,QVariant> _deviceSettings = strategy()->strategyDb().settings;
        foreach(QString _setName, _deviceSettings.keys()){
            device()->setSetting( _setName, _deviceSettings.value( _setName ) );
        }

        device()->setMeasureTerminal(_db.constants );
        device()->setSourceTerminal( _db.constants );

        _spiceValues = device()->simulate( strategy()->typeDb() ,
                                           ranges);

        int count_row = _db.table.count();
        for(int row=0; row < count_row;row++){
            QList<double> _row = _db.table.at(row).row;
            QMap<QString,double> _values = _db.constants;

            for(int col=0; col < _db.columns.count(); col++){
                _values.insert( _db.columns.at(col), _row.at(col) );
            }

            QPointF pointMeasure, pointSimulate;

            pointMeasure = device()->computeValue(strategy()->typeDb(), _values );


            bool _findValue=false;
            for(int i=0; i < _spiceValues.count();i++){
                double spiceValue = normalizeDouble(_spiceValues.at(i).x(),2);
                if(spiceValue == pointMeasure.x() ){
                    pointSimulate = _spiceValues.at(i);
                    _findValue = true;
                    break;
                }
            }

            double _temp = 0.0;



            if(!_findValue){
                continue;
            }





            if( typeError_ == ERROR_ABSOLUTE ){
                //
                _temp   = fabs(pointSimulate.y()) -  fabs(pointMeasure.y());
                _temp  /= strategy()->weight( pointSimulate.x() );
                _error += (_temp * _temp);
            }else{
                _temp   = MAX_VALUE( fabs(pointSimulate.y()), fabs(pointMeasure.y()) );
                _temp = fabs(pointMeasure.y());
                if(_temp != 0.0){
                    _temp   = fabs(pointSimulate.y())- fabs(pointMeasure.y())/_temp;
                    _temp  /= strategy()->weight( pointSimulate.x() );

                    _error += (_temp * _temp);
                }
            }

//            file->write( QString("%1\t%2\t%3\t%4\n").arg(pointMeasure.x()).
//                         arg(pointSimulate.y()).arg(pointMeasure.y()).
//                         arg( _temp*_temp ).toAscii() );
        }

    }
//    file->flush();
//    file->close();

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
