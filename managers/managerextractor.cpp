#include "managerextractor.h"
#include "core/tdblayer.h"

#include "minimisations/minimisations.h"
#include "float.h"
#include "core/tsetting.h"

ManagerExtractor::ManagerExtractor(){
}

ManagerExtractor::~ManagerExtractor(){

    mutex.unlock();

    delete mStrategy;
    delete mParameterSet;
    delete mDevice;
//    delete mExtractor;

}

bool ManagerExtractor::openDevice(int device_id){

    TDBLayer *dbLayer = TDBLayer::getInstance();
    if(device_id != -1){

        dbLayer->bindQuery("SELECT name,device FROM devices WHERE id=:id")
                ->bindValue(":id",device_id)
                ->exec();

        if(dbLayer->isNext()){

            QString device_type = dbLayer->value("device").toString();


            TDevice *_device = TDevice::createObject( device_id, device_type );

            if(!_device->Open()){
                qDebug() << "Device couldn't load";
            }


            setCurrentDevice( _device );
            device()->init();


            mStrategy = new TStrategy( device()->strategyId() );
            mStrategy->Open();


            mParameterSet = new TParameterSet( device()->parameterSetId() );
            if(!parameterSet()->Open()){

            }



            // load


            //            emit deviceOpened();
            delete dbLayer;
            return true;


        }else{
            //            Log( QString("Couldn't open device %d").arg(device_id) );
        }

    }
    delete dbLayer;
    return false;
}

QList<EXTRACTOR_PLOT> ManagerExtractor::plot(QString plot_type, QMap<TDevice::Axis,PLOT_AXIS_RANGE> &_ranges){

    //    TDataset *dataset = mStrategy->dataset();
    //    QList<TMeasure *> measures = dataset->measures( mStrategy->excludePlots() );



    QList<EXTRACTOR_PLOT> _plots;

    PLOT_AXIS_RANGE _range;
    _range.max = -DBL_MAX;
    _range.min = DBL_MAX;
    _ranges.clear();
    _ranges.insert( TDevice::AXIS_X, _range );
    _ranges.insert( TDevice::AXIS_Y, _range );

    QMap<QString,double> _measures;


    strategy()->beginDb();

    while( strategy()->isNextDb() ){
        strategy()->nextDb();

        if(strategy()->typeDb() != plot_type){
            continue;
        }

        QMap<QString,QVariant> _deviceSettings = strategy()->strategyDb().settings;
        foreach(QString _setName, _deviceSettings.keys()){
            device()->setSetting( _setName, _deviceSettings.value( _setName ) );
        }


        MEASURE_DB _db  = strategy()->measureDb();

        QStringList _columns = _db.columns;
        int _row_count = _db.table.count();

        STEP_RANGE _step;
        if(_db.steps.count() > 0){
            _step = _db.steps.value( _db.steps.keys().at(0) );
        }else{
            qDebug() << "step0";
        }

        device()->setMeasureTerminal( _db.constants );
        device()->setSourceTerminal( _db.constants );


        QVector< QMap<TDevice::Axis, double> > _vec;


        _vec =  device()->getPlotData( plot_type , _step  );

        EXTRACTOR_PLOT _plot;

        int _count_vec = _vec.count();

        for(int i=0; i < _count_vec;i++){
            if(device()->polarity() == TDevice::POLARITY_P){
                _plot.model_x << -_vec.at(i).value(TDevice::AXIS_X);
                _plot.model_y << -_vec.at(i).value(TDevice::AXIS_Y);
            }else{
                _plot.model_x << _vec.at(i).value(TDevice::AXIS_X);
                _plot.model_y << _vec.at(i).value(TDevice::AXIS_Y);
            }
        }




        for(int row=0; row < _row_count; row++){
            MEASURE_ROW _row = _db.table.at(row);


            _measures = _db.constants;

            QStringList _constants;
            foreach(QString _const,_db.constants.keys()){
                _constants << QString("%1=%2").arg(_const).arg( _db.constants.value(_const) );
            }

            _plot.constant = _constants.join(", ");

            for(int col=0; col < _columns.count(); col++){
                _measures.insert( _columns.at(col), _row.row.at(col)  );
            }

            //                device()->setMeasure( _measures );

            //                foreach(TTerminal *terminal,mDevice->terminals()){
            //                      terminal->setCurrent( terminal->getMeasure(TTerminal::CURRENT) );
            //                      terminal->setVoltage( terminal->getMeasure(TTerminal::VOLTAGE) );
            //                }

            QMap<TDevice::Axis,double> _plot_values = device()->computeValue(plot_type,_measures);


            if(device()->polarity() == TDevice::POLARITY_P){
                _plot.measure_x << -_plot_values[TDevice::AXIS_X];
                _plot.measure_y << -_plot_values[TDevice::AXIS_Y];
            }else{
                _plot.measure_x << _plot_values[TDevice::AXIS_X];
                _plot.measure_y << _plot_values[TDevice::AXIS_Y];
            }

            // X
            if(_plot_values[TDevice::AXIS_X] > _ranges[TDevice::AXIS_X].max){
                _ranges[TDevice::AXIS_X].max = _plot_values[TDevice::AXIS_X];
            }
            if(_plot_values[TDevice::AXIS_X] < _ranges[TDevice::AXIS_X].min){
                _ranges[TDevice::AXIS_X].min = _plot_values[TDevice::AXIS_X];
            }
            // Y
            if(_plot_values[TDevice::AXIS_Y] > _ranges[TDevice::AXIS_Y].max){
                _ranges[TDevice::AXIS_Y].max = _plot_values[TDevice::AXIS_Y];
            }
            if(_plot_values[TDevice::AXIS_Y] < _ranges[TDevice::AXIS_Y].min){
                _ranges[TDevice::AXIS_Y].min = _plot_values[TDevice::AXIS_Y];
            }



            //                device()->simulate(measure->plotType());

            //                QMap<QString,double> _models;
            //                foreach(TTerminal *terminal,mDevice->terminals()){
            //                    _models.insert( QString("I"+terminal->name().toLower()), terminal->getCurrent());
            //                    _models.insert( QString("V"+terminal->name().toLower()), terminal->getVoltage());
            //                }


            //                _plot_values = device()->plot_value(plot_type,_models);

            //                _plot.model_x << _plot_values[TDevice::AXIS_X];
            //                _plot.model_y << _plot_values[TDevice::AXIS_Y];

            _measures.clear();


        }

        _plots << _plot;




        //        delete measure;
    }

    //    delete dataset;

    return _plots;

}

QStringList ManagerExtractor::plotNames(){
    return device()->plots().keys();
}

void ManagerExtractor::setMinimisator()
{

    QString _method = TSetting::value("optimisation","method").toString();

    //    mExtractor = new MinQuasiNewton( device()->id() );
    if(_method.compare("QuasiNewton",Qt::CaseInsensitive) == 0){
        mExtractor = new MinQuasiNewton( device()->id() );
    }else{
        mExtractor = new MinHookeJeeves( device()->id() );
    }

    //init

}
