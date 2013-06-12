#include "jfet.h"
#include "core/tcircuit.h"
#include "defines.h"
JFET::JFET(int device_id) : TDevice(device_id){


    addTerminal( "S" );
    addTerminal( "G" );
    addTerminal( "D" );

    QStringList _polars;
    _polars << "N" << "P";

    setPolarities( _polars );

    setPolarity( "P" );
    setGround( "S" );

    addImage( "jfet-n", ":/devices" );
    addImage( "jfet-p", "" );


    setType( DEVICE_JFET );

    addPlot( "in", trUtf8("Входная ВАХ"), "Vgs", "Ids" );
    addPlot( "out", trUtf8("Выходная ВАХ"), "Vds", "Ids" );



}
void JFET::init()
{
    addParameter( "VTO",    "",  -2.0 );
    addParameter( "BETA",   "",  1e-4);
    addParameter( "LAMBDA", "",  0.0);
    addParameter( "RS",     "",  0.0);
    addParameter( "RD",     "",  0.0);
    addParameter( "RG",     "",  0.0);
    addParameter( "IS",   "",  1e-14);
    addParameter( "M", "", 0.33);
    addParameter( "KF", "", 1e-18);
    addParameter( "AF", "", 1);
//    addParameter( )
    addParameter( "PB", "",  1.0);


}
void JFET::simulate(QString _plot_type){

//    qDebug() << QString("Simulate plot: %1").arg(_plot_type);

    double Vd=0.0,Vg=0.0,Vs=0.0,
            Vds = 0.0,
            Vgs = 0.0,
            Ids = 0.0,
            Vt = PHYSIC_VT( param("TNOM") );

//    if(_plot_type == "out"){
//        qDebug() << QString("Vd: %1, Imeasure: %2 ").arg(terminal("D")->getVoltage())
//                    .arg( terminal("D")->getMeasure(TTerminal::CURRENT));

//        qDebug() << QString("RD: %1").arg(param("RD"));
//    }
    Vd = terminal("D")->getVoltage() - terminal("D")->getMeasure(TTerminal::CURRENT) * param("RD");

    Vg = terminal("G")->getVoltage() - terminal("G")->getMeasure(TTerminal::CURRENT) * param("RG");
    Vs = terminal("S")->getVoltage() - terminal("S")->getMeasure(TTerminal::CURRENT) * param("RS");

    Vds = Vd - Vs;
    Vgs = Vg - Vs;


    double Vgsat = 0.0;

//    if(_plot_type == "out"){
//        qDebug()  << "ED";
//    }

    if( polarity() == TDevice::POLARITY_P ){
        if(-Vds >= 0){

            Vgsat = - Vgs - param("VTO");


            //        qDebug() << Vgsat;

            if( Vgsat <= 0 ){
                Ids = 0.0;
            }else{
                Ids = param("BETA")*(1 - param("LAMBDA")*Vds);
                if( Vgsat >= -Vds){
                    Ids *= -Vds*( Vds + Vgsat*2 );
                }else{
                    Ids *=  (Vgsat*Vgsat);
                }
            }
        }else{

            Vgsat = -(Vgs-Vds) - param("VTO");

            if(Vgsat <= 0){
                Ids = 0.0;
            }else{
                Ids = param("BETA")*(1 - param("LAMBDA")*Vds);
                if(Vgsat-Vds >= 0){
                    Ids *= -Vds*( -Vds + Vgsat*2 );
                }else{
                    Ids *= -(Vgsat*Vgsat);
                }
            }

        }
    }



    terminal("D")->setCurrent( -Ids );
    // G - unknown

    // Vsb = 0.0
    // HSPICE Level1
//    double Vsb = 0.0;
//    double Vth = param("VTO") - param("GAMMA")*sqrt(param("PHI")) +
//            param("GAMMA")*sqrt(param("PHI") + Vsb);

//    if(Vgs <= Vth){
//        Ids = 0.0;
//    }else if(Vds < Vgs - Vth){
//        Ids  = param("KP");
//        Ids *= (effectiveW()/effectiveL())*(1+param("LAMBDA")*Vds);
//        Ids *= Vds*(Vgs-Vth-Vds/2);
//    }else if(Vds >= Vgs - Vth){
//        Ids  = param("KP")/2;
//        Ids *= (effectiveW()/effectiveL())*(1+param("LAMBDA")*Vds);
//        Ids *= pow(Vgs-Vth,2.0);
//    }

}

QString JFET::image()
{
    QString _img("");
    if(polarity() == TDevice::POLARITY_N){
        _img = ":/devices/jfet-n";
    }else{
        _img = ":/devices/jfet-p";
    }
    return _img;
}


QStringList JFET::constantTitles(QString plot_type){
    QStringList _consts;

    if(plot_type == "in"){
        _consts << "Vds";
    }else if(plot_type == "out"){
        _consts << "Vgs";
    }

    return _consts;
}

QStringList JFET::columnTitles(QString plot_type){

    QStringList _columns;

    if(plot_type == "in"){
        _columns << "Vgs" << "Ids";
    }else if(plot_type == "out"){
        _columns << "Vds" << "Ids";
    }

    return _columns;

}

QVector<QPointF> JFET::simulate(QString _plot_type, QMap<QString,STEP_RANGE> ranges)
{
    QMutexLocker locker(&mutexSimulate);
    QVector<QPointF> simulatedData;
    double Vds = 0.0, Vgs = 0.0;
    Vds = terminal("D")->getVoltage() - terminal("S")->getVoltage();
    Vgs = terminal("G")->getVoltage() - terminal("S")->getVoltage();

    TCircuit* circuit = new TCircuit("JFET simulate","jfet.cir",NGSPICE_PATH);
    TNet* net;


    net = TNet::createNet( "j1" );
    net->setTerminals( 3, 2, 1, 0 );
    net->addValue( "fet" );
    circuit->addNet( net );

    net = TNet::createNet( "Vds" );
    net->setTerminals(2, 2, 0 );
    net->addValue( Vds );
    circuit->addNet( net );

    net = TNet::createNet( "Vgs" );
    net->setTerminals(2, 1, 0 );
    net->addValue( Vgs );
    circuit->addNet( net );

    CIRCUIT_ANALYZE_DC dcAnalyze = { "", 0, 0, 0.01 };
    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        strcpy( dcAnalyze.name, "Vgs" );
    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        strcpy( dcAnalyze.name, "Vds" );
    }
    if(!ranges.contains(dcAnalyze.name)){
        TSLog("Can't find ranges");
        return simulatedData;
    }

    dcAnalyze.start = ranges.value(dcAnalyze.name).start;
    dcAnalyze.end = ranges.value(dcAnalyze.name).end;
    circuit->setAnalyze(dcAnalyze);
    circuit->addPrint(2,"dc","i(Vds)");

    CIRCUIT_MODEL circuitModel = {"fet", "NJF",0};

    if(polarity() == TDevice::POLARITY_P){
        circuitModel.polarity[0] = 'P';
    }
    MODEL_STRUCT model = getModel();
    circuitModel.level = getLevel( &model.name );
    foreach( TParameter *param,getParameters() ){
        if(param->isInclude()){
            circuitModel.parameters.insert(param->name(),param->value());
        }
    }

    circuit->addModel( circuitModel );



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

QVector<QPointF> JFET::getPlotData(QString _plot_type, QMap<QString,STEP_RANGE> ranges)
{
    QMutexLocker locker(&mutexSimulate);
    QVector<QPointF> simulatedData;
    double Vgs=0.0,Vds=0.0;
    Vds = terminal("D")->getVoltage() - terminal("S")->getVoltage();
    Vgs = terminal("G")->getVoltage() - terminal("S")->getVoltage();

    TCircuit* circuit = new TCircuit("JFET simulate","jfetp.cir",NGSPICE_PATH);
    TNet* net;


    net = TNet::createNet( "j1" );
    net->setTerminals( 3, 2, 1, 0 );
    net->addValue( "fet" );
    circuit->addNet( net );

    net = TNet::createNet( "Vds" );
    net->setTerminals(2, 2, 0 );
    net->addValue( Vds );
    circuit->addNet( net );

    net = TNet::createNet( "Vgs" );
    net->setTerminals(2, 1, 0 );
    net->addValue( Vgs );
    circuit->addNet( net );

    CIRCUIT_ANALYZE_DC dcAnalyze = { "", 0, 0, 0.01 };
    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        strcpy( dcAnalyze.name, "Vgs" );
    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        strcpy( dcAnalyze.name, "Vds" );
    }
    if(!ranges.contains(dcAnalyze.name)){
        TSLog("Can't find ranges");
        return simulatedData;
    }

    dcAnalyze.start = ranges.value(dcAnalyze.name).start;
    dcAnalyze.end = ranges.value(dcAnalyze.name).end;
    circuit->setAnalyze(dcAnalyze);
    circuit->addPrint(2,"dc","i(Vds)");

    CIRCUIT_MODEL circuitModel = {"fet", "NJF",0};

    if(polarity() == TDevice::POLARITY_P){
        circuitModel.polarity[0] = 'P';
    }
    MODEL_STRUCT model = getModel();
    circuitModel.level = getLevel( &model.name );
    foreach( TParameter *param,getParameters() ){
        if(param->isInclude()){
            circuitModel.parameters.insert(param->name(),param->value());
        }
    }

    circuit->addModel( circuitModel );



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

QPointF JFET::computeValue(QString plot_name, QMap<QString, double> values){

    QPointF point;
    if(plot_name == "in"){
            point = QPointF(values.value("Vgs",INFINITY),values.value("Ids",INFINITY));
    }else if(plot_name == "out"){
        point = QPointF(values.value("Vds",INFINITY),values.value("Ids",INFINITY));
    }else{
        point = QPointF(INFINITY,INFINITY);
    }

    return point;


}



