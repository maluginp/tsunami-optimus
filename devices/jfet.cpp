#include "jfet.h"
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

    addPlot( "in", trUtf8("Входная ВАХ"), "Vg", "Id" );
    addPlot( "out", trUtf8("Выходная ВАХ"), "Vd", "Id" );



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
        _consts << "Vd";
    }else if(plot_type == "out"){
        _consts << "Vg";
    }

    return _consts;
}

QStringList JFET::columnTitles(QString plot_type){

    QStringList _columns;

    if(plot_type == "in"){
        _columns << "Vg" << "Id";
    }else if(plot_type == "out"){
        _columns << "Vd" << "Id";
    }

    return _columns;

}

QVector<QMap<TDevice::Axis, double> > JFET::simulate(QString _plot_type, STEP_RANGE _range)
{
    QMutexLocker locker(&mutexSimulate);
    QProcess *proc = new QProcess();

    QString spicePath( NGSPICE_PATH );
    QStringList spiceArg;
    spiceArg << "-b" << "-ofet_sim.out" << "fet_sim.cir";

    QFile cirFile( "fet_sim.cir" ),
            outFile("fet_sim.out");


    if(!cirFile.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate )){

        delete proc;
        //    return;
    }
    // Жёстко земля S
    double Vds = 0.0, Vgs = 0.0 ,Vbs = 0.0;

    Vds = terminal("D")->getVoltage() - terminal("S")->getVoltage();
    Vgs = terminal("G")->getVoltage() - terminal("S")->getVoltage();
//    Vbs = terminal("B")->getVoltage() - terminal("S")->getVoltage();


    MODEL_STRUCT _model = getModel();

    QByteArray _circuit("");

    double L = 10e-6,
            W = 100e-6;
    _circuit.append( QString("Tsunami\n\n"));
    _circuit.append( QString("j1 2 1 0 fet\n"));
    _circuit.append( QString("Vds 2 0 %1\n").arg(Vds) );
    _circuit.append( QString("Vgs 1 0 %1\n").arg(Vgs) );

    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        // Id(Vg)| Vd = const
        _circuit.append( QString(".dc Vgs %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        _circuit.append( QString(".dc Vds %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
    }else{
        // error;
    }
    _circuit.append( ".options noacct nopage\n" );
    _circuit.append( QString(".print dc i(Vds)\n") );

    // #TODO: fix
    setPolarity(TDevice::POLARITY_P);

    if( polarity() == TDevice::POLARITY_N ){
        _circuit.append( ".model fet NJF\n" );
    }else if( polarity() == TDevice::POLARITY_P ) {
        _circuit.append( ".model fet PJF\n" );
    }else{
        _circuit.append( ".model fet NJF\n" );
    }



//    if(_model.name.compare( "BSIM3v3", Qt::CaseInsensitive ) == 0){
//        _circuit.append("+ LEVEL=8\n");
//    } else if( _model.name.compare("LEVEL2", Qt::CaseInsensitive) == 0 ){
//        _circuit.append("+ LEVEL=2\n");
//    } else if( _model.name.compare("LEVEL3", Qt::CaseInsensitive) == 0){
//        _circuit.append("+ LEVEL=3\n");
//    }

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
        if(_columns.count() == 3){
            QMap<TDevice::Axis,double> _map;
            V = _columns.at(1).toDouble();
//            Ibs = _columns.at(3).toDouble();
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

QVector<QMap<TDevice::Axis, double> > JFET::getPlotData(QString _plot_type, STEP_RANGE _range)
{
    QMutexLocker locker(&mutexSimulate);
    QProcess *proc = new QProcess();

    QString spicePath( NGSPICE_PATH );
    QStringList spiceArg;
    spiceArg << "-b" << "-ofet_plot.out" << "fet_plot.cir";

    QFile cirFile( "fet_plot.cir" ),
            outFile("fet_plot.out");


    if(!cirFile.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate )){

        delete proc;
        qDebug() << "can't open";
        qDebug() << cirFile.errorString();
        //    return;
    }else{
        QFileInfo info(cirFile);

        qDebug() << "Path circuit file:" << info.canonicalPath();
    }
    // Жёстко земля S
    double Vds = 0.0, Vgs = 0.0 ,Vbs = 0.0;

    Vds = terminal("D")->getVoltage() - terminal("S")->getVoltage();
    Vgs = terminal("G")->getVoltage() - terminal("S")->getVoltage();
//    Vbs = terminal("B")->getVoltage() - terminal("S")->getVoltage();


    MODEL_STRUCT _model = getModel();

    QByteArray _circuit("");

    double L = 10e-6,
            W = 100e-6;
    _circuit.append( QString("Tsunami\n\n"));
    _circuit.append( QString("j1 2 1 0 fet\n") );
    _circuit.append( QString("Vds 2 0 %1\n").arg(Vds) );
    _circuit.append( QString("Vgs 1 0 %1\n").arg(Vgs) );

    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        // Id(Vg)| Vd = const
        _circuit.append( QString(".dc Vgs %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        _circuit.append( QString(".dc Vds %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
    }else{
        // error;
    }
    _circuit.append( ".options noacct nopage\n" );
    _circuit.append( QString(".print dc i(Vds)\n") );

    // #TODO: fix
//    setPolarity(TDevice::N);

    if( polarity() == TDevice::POLARITY_N ){
        _circuit.append( ".model fet NJF\n" );
    }else if( polarity() == TDevice::POLARITY_P ) {
        _circuit.append( ".model fet PJF\n" );
    }else{
        _circuit.append( ".model fet NJF\n" );
    }



//    if(_model.name.compare( "BSIM3v3", Qt::CaseInsensitive ) == 0){
//        _circuit.append("+ LEVEL=8\n");
//    } else if( _model.name.compare("LEVEL2", Qt::CaseInsensitive) == 0 ){
//        _circuit.append("+ LEVEL=2\n");
//    } else if( _model.name.compare("LEVEL3", Qt::CaseInsensitive) == 0){
//        _circuit.append("+ LEVEL=3\n");
//    }

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
        if(_columns.count() == 3){
            QMap<TDevice::Axis,double> _map;
            V = _columns.at(1).toDouble();
//            Ibs = _columns.at(3).toDouble();
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

QMap<TDevice::Axis, double> JFET::computeValue(QString plot_name, QMap<QString, double> values){

    QMap<TDevice::Axis, double> value;
    if(plot_name == "in"){
        if(values.contains( "Vg" ) && values.contains( "Id" )){
            value.insert( TDevice::AXIS_X, values["Vg"] );
            value.insert( TDevice::AXIS_Y, values["Id"] );
        }

    }else if(plot_name == "out"){
        if(values.contains( "Vd" ) && values.contains( "Id" )){
            value.insert( TDevice::AXIS_X, values["Vd"] );
            value.insert( TDevice::AXIS_Y, values["Id"] );
        }
    }

    return value;


}



