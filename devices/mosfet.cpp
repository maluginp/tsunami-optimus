#include "mosfet.h"

#include "core/tcircuit.h"

MOSFET::MOSFET(int device_id) : TDevice(device_id)
{

    addTerminal( "S" );
    addTerminal( "G" );
    addTerminal( "D" );
    addTerminal( "B" );


    setPolarity( "N" );
    setGround( "S" );

    setType( DEVICE_MOSFET );

    addPlot( "in", trUtf8("Входная ВАХ"), "Vg", "Id" );
    addPlot( "out", trUtf8("Выходная ВАХ"), "Vd", "Id" );



}

void MOSFET::init(){
    MODEL_STRUCT _model = getModel();
    if(_model.name.compare( "BSIM3v3", Qt::CaseInsensitive ) == 0){


    } else if( _model.name.compare("LEVEL2", Qt::CaseInsensitive) == 0 ){

        addParameter( "AF",     "",  1.0 );
        addParameter( "CBD",    "",  0.0 );
        addParameter( "CBS",    "",  0.0 );
        addParameter( "CGBO",   "",  0.0 );
        addParameter( "CGDO",   "",  0.0 );
        addParameter( "CGSO",   "",  0.0 );
        addParameter( "CJ",     "",  0.0 );
        addParameter( "CJSW",   "",  0.0 );
        addParameter( "DELTA",  "",  0.0 );
        addParameter( "FC",     "",  0.5 );
        addParameter( "GAMMA",  "",  0.0 );
        addParameter( "IS",     "",  1.0e-14 );
        addParameter( "JS",     "",  0.0 );
        addParameter( "KF",     "",  0.0 );
        addParameter( "KP",     "",  2.0e-15 );
        addParameter( "LAMBDA", "",  0.0 );
        addParameter( "LD",     "",  0.0 );
        addParameter( "MJ",     "",  0.5 );
        addParameter( "MJSW",   "",  0.33 );
        addParameter( "NEFF",   "",  1.0 );
        addParameter( "NFS",    "",  0.0 );
        addParameter( "NSS",    "",  0.0 );
        addParameter( "NSUB",   "",  0.0 );
        addParameter( "PB",     "",  0.8 );
        addParameter( "PHI",    "",  0.6 );
        addParameter( "RD",     "",  0.0 );
        addParameter( "RS",     "",  0.0 );
        addParameter( "RSH",    "",  0.0 );
        addParameter( "TOX",    "",  1.0e-7 );
        addParameter( "TPG",    "",  1.0 );
        addParameter( "UCRIT",  "",  1.0e4 );
        addParameter( "UO",     "",  600.0 );
        addParameter( "VMAX",   "",  0.0 );
        addParameter( "VTO",    "",  0.0 );
        addParameter( "XJ",     "",  0.0 );


    } else if( _model.name.compare("LEVEL3", Qt::CaseInsensitive) == 0){

        addParameter( "AF",     "",  1.0 );
        addParameter( "CBD",    "",  0.0 );
        addParameter( "CBS",    "",  0.0 );
        addParameter( "CGBO",   "",  0.0 );
        addParameter( "CGDO",   "",  0.0 );
        addParameter( "CGSO",   "",  0.0 );
        addParameter( "CJ",     "",  0.0 );
        addParameter( "CJSW",   "",  0.0 );
        addParameter( "DELTA",  "",  0.0 );
        addParameter( "FC",     "",  0.5 );
        addParameter( "GAMMA",  "",  0.0 );
        addParameter( "IS",     "",  1.0e-14 );
        addParameter( "JS",     "",  0.0 );
        addParameter( "KF",     "",  0.0 );
        addParameter( "KP",     "",  2.0e-15 );
        addParameter( "LAMBDA", "",  0.0 );
        addParameter( "LD",     "",  0.0 );
        addParameter( "MJ",     "",  0.5 );
        addParameter( "MJSW",   "",  0.33 );
        addParameter( "NEFF",   "",  1.0 );
        addParameter( "NFS",    "",  0.0 );
        addParameter( "NSS",    "",  0.0 );
        addParameter( "NSUB",   "",  0.0 );
        addParameter( "PB",     "",  0.8 );
        addParameter( "PHI",    "",  0.6 );
        addParameter( "RD",     "",  0.0 );
        addParameter( "RS",     "",  0.0 );
        addParameter( "RSH",    "",  0.0 );
        addParameter( "TOX",    "",  1.0e-7 );
        addParameter( "TPG",    "",  1.0 );
        addParameter( "UCRIT",  "",  1.0e4 );
        addParameter( "UO",     "",  600.0 );
        addParameter( "VMAX",   "",  0.0 );
        addParameter( "VTO",    "",  0.0 );
        addParameter( "XJ",     "",  0.0 );
        addParameter( "THETA",  "",  0.0 );
        addParameter( "ETA",    "",  0.0 );
        addParameter( "KAPPA",  "",  0.2 );

    }

}

QString MOSFET::image()
{
    QString _img("");
    if(polarity() == TDevice::POLARITY_N){
        _img = ":/devices/nmos";
    }else{
        _img = ":/devices/pmos";
    }
    return _img;
}



QVector< QPointF > MOSFET::simulate(QString _plot_type, STEP_RANGE _range){

    QMutexLocker locker(&mutexSimulate);

    // Жёстко земля S
    double Vds = 0.0, Vgs = 0.0 ,Vbs = 0.0;

    Vds = terminal("D")->getVoltage() - terminal("S")->getVoltage();
    Vgs = terminal("G")->getVoltage() - terminal("S")->getVoltage();
    Vbs = terminal("B")->getVoltage() - terminal("S")->getVoltage();


    MODEL_STRUCT model = getModel();

    double L = setting( "L" ).toDouble(),
            W = setting( "W" ).toDouble();

    TCircuit* circuit = new TCircuit("MOSFET simulate","mos.cir",NGSPICE_PATH);
    TNet* net;
    QVector<QVariant> values;

    values << "mos" << QString("L=%1").arg(L) << QString("W=%1").arg(W);
    net = TNet::createNet( "m1" );
    net->setTerminals( 4, 2, 1, 0, 3 );
    net->addValue( values );
    circuit->addNet( net );

    net = TNet::createNet( "Vds" );
    net->setTerminals(2, 2, 0 );
    net->addValue( Vds );
    circuit->addNet( net );

    net = TNet::createNet( "Vgs" );
    net->setTerminals(2, 1, 0 );
    net->addValue( Vgs );
    circuit->addNet( net );

    net = TNet::createNet( "Vbs" );
    net->setTerminals(2, 3, 0 );
    net->addValue( Vbs );
    circuit->addNet( net );
    CIRCUIT_ANALYZE_DC dcAnalyze = { "", _range.start, _range.end, 0.01 };
    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        strcpy( dcAnalyze.name, "Vgs" );
    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        strcpy( dcAnalyze.name, "Vds" );
    }

    circuit->setAnalyze(dcAnalyze);
    circuit->addPrint(3,"dc","i(Vds)","i(Vbs)");

    CIRCUIT_MODEL circuitModel = {"mos", "NMOS",0};

    if(polarity() == TDevice::POLARITY_P){
        circuitModel.polarity[0] = 'P';
    }

    circuitModel.level = getLevel( &model.name );
    foreach( TParameter *param,getParameters() ){
        circuitModel.parameters.insert(param->name(),param->value());
    }

    circuit->addModel( circuitModel );

    QVector<QPointF> simulatedData;

    if(!circuit->simulate()){
        TSLog( "Simulated data" );
        return simulatedData;
    }

    QVector< QVector<double> > results = circuit->getResult();
    for(int i=0; i < results.count(); i++){
        QVector<double> row = results.at(i);
        QPointF point( row.at(0), row.at(1) );
        simulatedData << point;
    }

    return simulatedData;
}

QVector<QPointF> MOSFET::getPlotData(QString _plot_type, STEP_RANGE _range){
    QMutexLocker locker(&mutexSimulate);
    // Жёстко земля S
    double Vds = 0.0, Vgs = 0.0 ,Vbs = 0.0;

    Vds = terminal("D")->getVoltage() - terminal("S")->getVoltage();
    Vgs = terminal("G")->getVoltage() - terminal("S")->getVoltage();
    Vbs = terminal("B")->getVoltage() - terminal("S")->getVoltage();


    MODEL_STRUCT model = getModel();

    double L = setting( "L" ).toDouble(),
            W = setting( "W" ).toDouble();

    TCircuit* circuit = new TCircuit("MOSFET simulate","mosp.cir",NGSPICE_PATH);
    TNet* net;
    QVector<QVariant> values;

    values << "mos" << QString("L=%1").arg(L) << QString("W=%1").arg(W);
    net = TNet::createNet( "m1" );
    net->setTerminals( 4, 2, 1, 0, 3 );
    net->addValue( values );
    circuit->addNet( net );

    net = TNet::createNet( "Vds" );
    net->setTerminals(2, 2, 0 );
    net->addValue( Vds );
    circuit->addNet( net );

    net = TNet::createNet( "Vgs" );
    net->setTerminals(2, 1, 0 );
    net->addValue( Vgs );
    circuit->addNet( net );

    net = TNet::createNet( "Vbs" );
    net->setTerminals(2, 3, 0 );
    net->addValue( Vbs );
    circuit->addNet( net );
    CIRCUIT_ANALYZE_DC dcAnalyze = { "", _range.start, _range.end, 0.01 };
    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        strcpy( dcAnalyze.name, "Vgs" );
    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        strcpy( dcAnalyze.name, "Vds" );
    }

    circuit->setAnalyze(dcAnalyze);
    circuit->addPrint(3,"dc","i(Vds)","i(Vbs)");

    CIRCUIT_MODEL circuitModel = {"mos", "NMOS",0};

    if(polarity() == TDevice::POLARITY_P){
        circuitModel.polarity[0] = 'P';
    }

    circuitModel.level = getLevel( &model.name );
    foreach( TParameter *param,getParameters() ){
        circuitModel.parameters.insert(param->name(),param->value());
    }

    circuit->addModel( circuitModel );

    QVector<QPointF> simulatedData;

    if(!circuit->simulate()){
        TSLog( "Simulated data" );
        return simulatedData;
    }

    QVector< QVector<double> > results = circuit->getResult();
    for(int i=0; i < results.count(); i++){
        QVector<double> row = results.at(i);
        QPointF point( row.at(0), row.at(1) );
        simulatedData << point;
    }

    return simulatedData;
}

QStringList MOSFET::constantTitles(QString plot_type){

    QStringList _consts;

    if(plot_type.compare("out",Qt::CaseInsensitive) == 0){
        _consts << "Vd" << "Vb";
    }else if(plot_type.compare("in",Qt::CaseInsensitive) == 0){
        _consts << "Vg" << "Vb";
    }

    return _consts;


}

QStringList MOSFET::columnTitles(QString plot_type){
    QStringList _columns;
    if(plot_type.compare("in",Qt::CaseInsensitive) == 0){
        _columns << "Vg" << "Id";
    }else if(plot_type.compare("out",Qt::CaseInsensitive) == 0){
        _columns << "Vd" << "Id";
    }
    return _columns;

}

QPointF MOSFET::computeValue(QString plot_name, QMap<QString, double> values){

    QPointF point;

    if( plot_name.compare("in",Qt::CaseInsensitive) == 0 ){
        point.setX( values.value( "Vg",0.0 )  );
        point.setY( values.value( "Id",0.0 )  );
    } else if( plot_name.compare("out",Qt::CaseInsensitive) == 0 ){
        point.setX( values.value( "Vd",0.0 )  );
        point.setY( values.value( "Id",0.0 )  );
    }else{
        point = QPointF(INFINITY,INFINITY);
    }

    return point;
}
