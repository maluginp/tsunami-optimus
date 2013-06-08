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



QVector< QMap<TDevice::Axis, double> > MOSFET::simulate(QString _plot_type, STEP_RANGE _range){

    QMutexLocker locker(&mutexSimulate);

    // Жёстко земля S
    double Vds = 0.0, Vgs = 0.0 ,Vbs = 0.0;

    Vds = terminal("D")->getVoltage() - terminal("S")->getVoltage();
    Vgs = terminal("G")->getVoltage() - terminal("S")->getVoltage();
    Vbs = terminal("B")->getVoltage() - terminal("S")->getVoltage();


    MODEL_STRUCT _model = getModel();

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

    CIRCUIT_MODEL circuitModel = {"mos", "NMOS"};

//    if( polarity() == TDevice::POLARITY_N ){
//        _circuit.append( ".model mos NMOS\n" );
//    }else if( polarity() == TDevice::POLARITY_P ) {
//        _circuit.append( ".model mos PMOS\n" );
//    }else{
//        _circuit.append( ".model mos NMOS\n" );
//    }


//    if(_model.name.compare( "BSIM3v3", Qt::CaseInsensitive ) == 0){
//        _circuit.append("+ LEVEL=8\n");
//    } else if( _model.name.compare("LEVEL2", Qt::CaseInsensitive) == 0 ){
//        _circuit.append("+ LEVEL=2\n");
//    } else if( _model.name.compare("LEVEL3", Qt::CaseInsensitive) == 0){
//        _circuit.append("+ LEVEL=3\n");
//    }

//    foreach( TParameter *param,getParameters() ){
//        if(param->isInclude()){
//            _circuit.append( QString("+ %1=%2\n").arg(param->getName()).arg(param->getDouble()) );
//        }
//    }


//    _circuit.append( "\n.end" );

//    int _writed = cirFile.write( _circuit );
//    if(_writed == -1){
//        qDebug() << "sss";
//        //error;
//        //    return;
//    }
//    cirFile.flush();
//    cirFile.close();

//    if(!cirFile.exists()){
//        qDebug() << "ss";
//    }

//    proc->start( spicePath, spiceArg );
//    if(!proc->waitForStarted()){
//        qDebug() << "sss";
//    }

//    if(!proc->waitForFinished()){
//        qDebug() << "sss1";
//    }

//    if(!outFile.open( QIODevice::ReadOnly )){
//        qDebug() << outFile.errorString();

////        delete proc;
//        //    return;
//    }

//    QVector< QMap<TDevice::Axis, double> > _vec;


//    double Ids=0.0,Ibs=0.0,V;
//    while(!outFile.atEnd()){
//        QList<QByteArray> _columns = outFile.readLine().trimmed().split('\t');
//        if(_columns.count() == 4){
//            QMap<TDevice::Axis,double> _map;
//            V = _columns.at(1).toDouble();
//            Ibs = _columns.at(3).toDouble();
//            Ids = _columns.at(2).toDouble();

//            _map.insert( AXIS_X, V );
//            _map.insert( AXIS_Y, -Ids);

//            _vec.append(_map);

//        }
//    }

//    outFile.close();

////    outFile.remove();
////    cirFile.remove();

////    proc->close();
////    if(proc->isOpen()){
////        qDebug() << "Proc open";
////    }
//    try{
//        delete proc;
//    }catch(...){
//        //
//    }

    QVector< > _vec;

    return _vec;
}

QVector<QMap<TDevice::Axis, double> > MOSFET::getPlotData(QString _plot_type, STEP_RANGE _range)
{
    QMutexLocker locker(&mutexSimulate);
    QProcess *proc = new QProcess();

    QString spicePath( NGSPICE_PATH );
    QStringList spiceArg;
    spiceArg << "-b" << "-omosfet_plot.out" << "mosfet_plot.cir";

    QFile cirFile( "mosfet_plot.cir" ),
            outFile("mosfet_plot.out");


    if(!cirFile.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate )){

        delete proc;
        //    return;
    }
    // Жёстко земля S
    double Vds = 0.0, Vgs = 0.0 ,Vbs = 0.0;

    Vds = terminal("D")->getVoltage() - terminal("S")->getVoltage();
    Vgs = terminal("G")->getVoltage() - terminal("S")->getVoltage();
    Vbs = terminal("B")->getVoltage() - terminal("S")->getVoltage();


    MODEL_STRUCT _model = getModel();

    QByteArray _circuit("");


    double L = setting( "L" ).toDouble(),
            W = setting( "W" ).toDouble();

    _circuit.append( QString("Tsunami\n\n"));
    _circuit.append( QString("m1 2 1 0 3 mos L=%1 W=%2\n").arg(L).arg(W) );
    _circuit.append( QString("Vds 2 0 %1\n").arg(Vds) );
    _circuit.append( QString("Vgs 1 0 %1\n").arg(Vgs) );
    _circuit.append( QString("Vbs 3 0 %1\n").arg(Vbs) );

    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        // Id(Vg)| Vd = const

        _circuit.append( QString(".dc Vgs %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        _circuit.append( QString(".dc Vds %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
    }else{
        // error;
    }
    _circuit.append( ".options noacct nopage\n" );
    _circuit.append( QString(".print dc i(Vds) i(Vbs)\n") );

    // #TODO: fix
    setPolarity(TDevice::POLARITY_N);

    if( polarity() == TDevice::POLARITY_N ){
        _circuit.append( ".model mos NMOS\n" );
    }else if( polarity() == TDevice::POLARITY_P ) {
        _circuit.append( ".model mos PMOS\n" );
    }else{
        _circuit.append( ".model mos NMOS\n" );
    }


    if(_model.name.compare( "BSIM3v3", Qt::CaseInsensitive ) == 0){
        _circuit.append("+ LEVEL=8\n");
    } else if( _model.name.compare("LEVEL2", Qt::CaseInsensitive) == 0 ){
        _circuit.append("+ LEVEL=2\n");
    } else if( _model.name.compare("LEVEL3", Qt::CaseInsensitive) == 0){
        _circuit.append("+ LEVEL=3\n");
    }

    foreach( TParameter *param,getParameters() ){
        if(param->isInclude()){
            _circuit.append( QString("+ %1=%2\n").arg(param->getName()).arg(param->getDouble()) );
        }
    }


    _circuit.append( "\n.end" );

    int _writed = cirFile.write( _circuit );
    if(_writed == -1){
        qDebug() << "sss";
        //error;
        //    return;
    }
    cirFile.flush();
    cirFile.close();

    if(!cirFile.exists()){
        qDebug() << "ss";
    }

    proc->start( spicePath, spiceArg );
    if(!proc->waitForStarted()){
        qDebug() << "sss";
    }

    if(!proc->waitForFinished()){
        qDebug() << "sss1";
    }

    if(!outFile.open( QIODevice::ReadOnly )){
        qDebug() << outFile.errorString();

//        delete proc;
        //    return;
    }

    QVector< QMap<TDevice::Axis, double> > _vec;


    double Ids=0.0,Ibs=0.0,V;
    while(!outFile.atEnd()){
        QList<QByteArray> _columns = outFile.readLine().trimmed().split('\t');
        if(_columns.count() == 4){
            QMap<TDevice::Axis,double> _map;
            V = _columns.at(1).toDouble();
            Ibs = _columns.at(3).toDouble();
            Ids = _columns.at(2).toDouble();

            _map.insert( AXIS_X, V );
            _map.insert( AXIS_Y, -Ids);

            _vec.append(_map);

        }
    }

    outFile.close();

//    outFile.remove();
//    cirFile.remove();

//    proc->close();
//    if(proc->isOpen()){
//        qDebug() << "Proc open";
//    }
    try{
        delete proc;
    }catch(...){
        //
    }



    return _vec;
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

QMap<TDevice::Axis, double> MOSFET::computeValue(QString plot_name, QMap<QString, double> values){

    QMap<TDevice::Axis, double> _point;

    if( plot_name.compare("in",Qt::CaseInsensitive) == 0 ){
        _point.insert( TDevice::AXIS_X, values.value( "Vg",0.0 ) );
        _point.insert( TDevice::AXIS_Y, values.value( "Id",0.0 ) );
    } else if( plot_name.compare("out",Qt::CaseInsensitive) == 0 ){
        _point.insert( TDevice::AXIS_X, values.value( "Vd",0.0 ) );
        _point.insert( TDevice::AXIS_Y, values.value( "Id",0.0 ) );
    }else{
        _point.insert( TDevice::AXIS_X , 0 );
        _point.insert( TDevice::AXIS_Y , 0 );

    }

    return _point;
}
