#include "tdevice.h"
#include "core/tdblayer.h"
#include "tstrategy.h"
//devices.h
#include "tparameterset.h"
#include "devices/devices.h"

TDevice::TDevice(QObject *parent) :
    QObject(parent){
    id_ = -1;

}

TDevice::~TDevice(){

    foreach(TParameter *parameter, parameters_){
        delete parameter;
    }
    parameters_.clear();

    foreach(TTerminal *terminal , terminals_){
        delete terminal;
    }
    terminals_.clear();
    plots_.clear();
    images_.clear();



}


void TDevice::setPolarities(QStringList polarities){
    polarities_ = polarities;
    hasPolarity_ = true;
}

MODEL_STRUCT TDevice::getModel(){

    MODEL_STRUCT _model = { "", false, "", ""};

    TDBLayer  *dbLayer = TDBLayer::getInstance();

    int _id = modelId();
    dbLayer->bindQuery("SELECT * FROM models WHERE id=:id")
            ->bindValue( ":id", _id)
            ->exec();

    if(dbLayer->isNext()){

        _model.author = dbLayer->value( "author" ).toString();
        _model.path   = dbLayer->value( "path").toString();
        _model.user_defined = dbLayer->value("user_defined").toBool();
        _model.name   = dbLayer->value( "name" ).toString();

    }
    delete dbLayer;

    return _model;

}

QVariantMap TDevice::parseMap(QString map)
{
    QVariantMap _map;
    QStringList _items = map.split(";");
    foreach(QString _item,_items){

        if(_item.isEmpty() || _item.split("=").count() != 2){
            continue;
        }

        QString _name  = _item.split("=").at(0);
        QString _value = _item.split("=").at(1);

        _map.insert( _name, QVariant(_value) );

    }

    return _map;

}

QString TDevice::createMap(QVariantMap map)
{
    QString _map;

    foreach(QString _key, map.keys()){

        _map += QString("%1=%2;").arg(_key).arg( map.value(_key).toString() );

    }

    return _map;
}

void TDevice::setMeasureTerminal(QString type, double value){
    QChar _char = type[0].toUpper();
    QString _terminal_name = type.mid(1).toUpper();

    if(_char == QChar('I')){
        terminal(_terminal_name)->setMeasure(TTerminal::CURRENT,value);
    }else if(_char == QChar('V')){
        terminal(_terminal_name)->setMeasure(TTerminal::VOLTAGE,value);
    }
}

void TDevice::setMeasureTerminal(QMap<QString, double> values){
    foreach(QString _key, values.keys()){
        setMeasureTerminal( _key, values.value( _key ) );
    }
}

QMap<QString, double> TDevice::measureTerminals()
{
    QMap<QString,double> _values;
    foreach(TTerminal *terminal,terminals()){
        _values.insert( QString("I")+terminal->name().toLower(), terminal->getMeasure( TTerminal::CURRENT ) );
        _values.insert( QString("V")+terminal->name().toLower(), terminal->getMeasure( TTerminal::VOLTAGE ) );
    }

    return _values;

}

void TDevice::setSourceTerminal(QString type, double value)
{
    QChar _char = type[0].toUpper();
    QString _terminal_name = type.mid(1).toUpper();

    if(_char == QChar('I')){
        terminal(_terminal_name)->setCurrent(value);
    }else if(_char == QChar('V')){
        terminal(_terminal_name)->setVoltage( value );
    }
}

void TDevice::setSourceTerminal(QMap<QString, double> values)
{
    foreach(QString _key, values.keys()){
        setSourceTerminal( _key, values.value( _key ) );
    }
}

QMap<QString, double> TDevice::sourceTerminals(){
    QMap<QString,double> _values;
    foreach(TTerminal *terminal,terminals()){
        _values.insert( QString("I")+terminal->name().toLower(), terminal->getCurrent() );
        _values.insert( QString("V")+terminal->name().toLower(), terminal->getVoltage() );
    }

    return _values;

}

bool TDevice::Create(QString name, QString device, int &device_id)
{
    device_id = -1;

    int model_id = -1;
    // #TODO
    if(device.toUpper() == "BJT"){
        model_id = 1;
    }else if(device.toUpper() == "JFET"){
        model_id = 2;
    }

    TDBLayer  *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT 1 FROM devices WHERE name=:name AND device=:device")
            ->bindValue( ":name", name)
            ->bindValue( ":device",device)
            ->exec();

    if(dbLayer->count() > 0){
        qDebug() << "Device exist";
        delete dbLayer;
        return false;
    }

    dbLayer->bindQuery("INSERT INTO devices(name,device,model_id,strategy_id,set_parameters_id,settings,created,changed,dataset_id) "
                       "VALUES(:name,:device,:model_id,-1,-1,'',:created,:changed,-1)")
            ->bindValue( ":name", name)
            ->bindValue(":device",device)
            ->bindValue(":model_id",model_id)
            ->bindValue(":created",QDate::currentDate())
            ->bindValue(":changed",QDate::currentDate())
            ->exec();

    if(!dbLayer->isRequested()){
        qDebug() << "INSERT device error:";
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return false;
    }

    device_id = dbLayer->getInsertID();




    delete dbLayer;
    return true;

}

int TDevice::getIdByName(QString name)
{
    int id = -1;
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT id FROM devices WHERE name=:name")
            ->bindValue(":name",name)
            ->exec();
    if(dbLayer->isNext()){
        id = dbLayer->value("id").toInt();
    }

    delete dbLayer;
    return id;
}

DEVICE_PLOT TDevice::plot(QString name){
    DEVICE_PLOT _plot;
    _plot.title = "";
    _plot.axis_x = "";
    _plot.axis_y = "";

    if(plots_.contains(name)){
        _plot = plots_[name];
    }

    return _plot;
}

QMap<QString, QString> TDevice::plotTitles()
{
    QMap<QString, QString> _types;
    QMap<QString,DEVICE_PLOT> _plots = plots();

    foreach(QString _name,_plots.keys()){
        _types.insert( _name, _plots.value(_name).title );
    }

    return _types;
}

bool TDevice::setSettings(QString name, QVariant value){

    QString _name = name.toLower();

    if(_name == "ground"){
        setGround( value.toString() );
    }else if(_name == "polarity"){
        setPolarity( value.toString()  );
    }

    return true;
}

bool TDevice::setSettings(QVariantMap values)
{


    foreach( QString _name, values.keys() ){

        setSettings( _name, values.value(_name) );

    }


    return true;

}

bool TDevice::saveSetting(QVariantMap values){
    QString _map = createMap(values);
    TDBLayer  *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("UPDATE devices SET settings=:map WHERE id=:id")
            ->bindValue( ":id", id())
            ->bindValue(":map",_map)
            ->exec();

    bool _res = dbLayer->isRequested();
    if(!_res){
        qDebug() << dbLayer->getError();
    }

    delete dbLayer;
    return _res;
}

TDevice *TDevice::createObject(int device_id, QString device_type)
{
    TDevice *device;
    device_type = device_type.toUpper();

    if(device_type.compare("BJT", Qt::CaseInsensitive) == 0){
        device = new BJT(device_id);
        //        device->Open();
        return device;
    }
    if(device_type.compare( "JFET", Qt::CaseInsensitive) == 0){
        device = new JFET(device_id);
        //        device->Open();
        return device;
    }

    if(device_type.compare("MOSFET", Qt::CaseInsensitive) == 0){
        device = new MOSFET(device_id);
        //        device->Open();
        return device;
    }

    return NULL;
}

TDevice *TDevice::openDevice(int device_id)
{
//    TDBLayer *dbLayer ;

    QString device_type("");

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT device FROM devices WHERE id=:id")
            ->bindValue(":id",device_id)
            ->exec();
    if(!dbLayer->isNext()){
        qDebug() << "TDevice::openDevice() error";
    }else{

        device_type = dbLayer->value("device").toString();

    }

    return TDevice::createObject( device_id, device_type );

}


void TDevice::addImage(QString name, QString path)
{
    images_.insert( name, path );
    return;
}

void TDevice::setName(QString name)
{
    name_ = name;
    return;
}

QString TDevice::deviceType()
{
    if(type_ == DEVICE_BJT){
        return QString("bjt");
    }else if(type_ == DEVICE_JFET){
        return QString("jfet");
    }else if(type_ == DEVICE_MOSFET){
        return QString("mosfet");
    }else if(type_ == DEVICE_DIODE){
        return QString("diode");
    }

    return QString("");
}

QList<TParameter *> TDevice::getParameters(){
    return parameters_;
}

void TDevice::setModel(QString model){
    model_ = model;
    return;
}

TParameter *TDevice::addParameter(QString param, QString desc, TParameter::TYPE_VALUE type){
    TParameter *parameter;

    switch(type){
    case TParameter::PARAMETER_DOUBLE:
        parameter = new TParameter(param,(double)0);
        break;
    case TParameter::PARAMETER_FLOAT:
        parameter = new TParameter(param,(float)0);
        break;
    case TParameter::PARAMETER_INT:
        parameter = new TParameter(param,(int)0);
        break;
    case TParameter::PARAMETER_STRING:
        parameter = new TParameter(param,QString(""));
        break;
    }

    if(parameter != NULL){
        parameter->setDescription( desc );
    }

    parameters_.append( parameter );
    return parameter;
}

TParameter *TDevice::addParameter(QString param, QString desc, double value)
{

    TParameter *parameter = new TParameter(param,value);
    parameter->setDescription( desc );

    parameters_.append( parameter );
    return parameter;
}


void TDevice::addTerminal(QString term_name)
{
    TTerminal *terminal = new TTerminal(term_name);

    terminals_.append( terminal );
}


QString TDevice::image(QString name)
{
    if(images_.contains( name )){
        return images_[name];
    }

    return QString("");
}


QString TDevice::name() {
    return name_;
}



TTerminal *TDevice::terminal(QString name) {
    foreach(TTerminal *terminal,terminals_){

        if(terminal->getName() == name){
            return terminal;
        }
    }

    return NULL;
}

QList<TTerminal *> TDevice::terminals(){
    return terminals_;
}

TParameter *TDevice::parameter(QString name) {
    foreach(TParameter *parameter,parameters_){
        if(parameter->getName() == name){
            return parameter;
        }
    }
    return addParameter( name, "", 0.0 );
}


QStringList TDevice::polarities()
{
    return polarities_;
}

bool TDevice::hasPolarity()
{
    return hasPolarity_;
}

TDevice::Polarity TDevice::polarity()
{
    if(hasPolarity()){
        return polarity_;
    }

    return POLARITY_UNDEF;
}

void TDevice::setPolarity(TDevice::Polarity _polarity)
{
    if(hasPolarity()){
        polarity_ = _polarity;
    }
}

void TDevice::setPolarity(QString polarity){
    polarity = polarity.toUpper();
    if(polarity == "N"){
        setPolarity(POLARITY_N);
    }else if(polarity == "P"){
        setPolarity(POLARITY_P);
    }else{
        setPolarity(POLARITY_UNDEF);
    }
}

double TDevice::param(QString name){

    if(parameter(name) != NULL){
        return parameter(name)->getDouble();
    }

    return INFINITY;
}
QString TDevice::groundName(){

    foreach(TTerminal *terminal,terminals()){
        if(terminal->isGnd()){
            return terminal->name();
        }
    }

    return QString("");

}

QString TDevice::polarityName(){

    switch(polarity()){
    case TDevice::POLARITY_N:
        return QString("N");
    case TDevice::POLARITY_P:
        return QString("P");
    default:
        break;
    }

    return QString("");
}

void TDevice::setGround(QString ground){
    if(terminal(ground) != NULL){
        terminal(ground)->setGnd();
    }
}

QStringList TDevice::constantTitles(QString plot_type)
{
    QStringList _list;
    qDebug() << plot_type;
    return _list;
}

QStringList TDevice::columnTitles(QString plot_type){
    QStringList _list;
    qDebug() << plot_type;
    return _list;
}




bool TDevice::Save()
{


    return false;
}

bool TDevice::Open(){

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT * FROM devices WHERE id=:id")
            ->bindValue(":id",id())
            ->exec();

    if(!dbLayer->isRequested()){
        qDebug() << dbLayer->getError();
    }

    if(dbLayer->isNext()){
        // type

        setModelID( dbLayer->value("model_id").toInt() );
        setStrategyID( dbLayer->value("strategy_id").toInt() );
        setParametersID( dbLayer->value("set_parameters_id").toInt() );
        setDatasetID(dbLayer->value("dataset_id").toInt());

        QVariantMap _mapSettings =  parseMap(dbLayer->value("settings").toString());
        setSettings( _mapSettings );

        created_ = dbLayer->value("created").toDate();
        changed_ = dbLayer->value("changed").toDate();


        name_ = dbLayer->value("name").toString();

        delete dbLayer;
        return true;

    }

    delete dbLayer;
    return false;
}

bool TDevice::Delete()
{
    TDBLayer *dbLayer = TDBLayer::getInstance();
    bool res = false;
    QList<int> _list;
    if(id() != -1){


        res = dbLayer->bindQuery("DELETE FROM devices WHERE id=:id")
                ->bindValue(":id",id())
                ->exec();
        if(res){

            _list = TStrategy::listStrategyByDeviceId( id() );
            foreach(int strategy_id,_list){

                TStrategy *strategy = new TStrategy(strategy_id);
                strategy->Delete();
                delete strategy;
            }

            _list = TDataset::listDatasetByDeviceId( id() );
            foreach(int dataset_id,_list){

                TDataset *dataset = new TDataset(dataset_id);
                dataset->Delete();
                delete dataset;
            }

            _list = TParameterSet::listParameterSetByDeviceId(id());

            foreach(int param_id,_list){

                TParameterSet *set = new TParameterSet(param_id);
                set->Delete();
                delete set;
            }


        }

    }

    delete dbLayer;
    return res;
}

