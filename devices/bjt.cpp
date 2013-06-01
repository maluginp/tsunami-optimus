#include "bjt.h"

#include "core/tparameter.h"


BJT::BJT(int device_id) : TDevice(device_id){

//    setID(device_id);

    addTerminal( "E" );
    addTerminal( "B" );
    addTerminal( "C" );




    QStringList _polarities;

    _polarities << "NPN" << "PNP";
    setPolarities( _polarities );

    // default
    setPolarity( "NPN" );
    setGround( "E" );

    addImage( "NPN", ":/devices/bjt-npn" );
    addImage( "NPN", ":/devices/bjt-npn" );


//    addImage( "NPN_E", ":/devices/bjt_npn_e" );
//    addImage( "NPN_B", ":/devices/bjt_npn_b" );
//    addImage( "NPN_C", ":/devices/bjt_npn_c" );

//    addImage( "PNP_E", ":/devices/bjt_pnp_e" );
//    addImage( "PNP_B", ":/devices/bjt_pnp_b" );
//    addImage( "PNP_C", ":/devices/bjt_pnp_c" );

    setType( DEVICE_BJT );


    addPlot( "in", trUtf8("Входная ВАХ"), "Vb", "Ib" );
    addPlot( "out", trUtf8("Выходная ВАХ") ,  "Vc", "Ic");
    addPlot( "betta", trUtf8("Бетта"),  "Ic", "Betta");




}

void BJT::simulate(QString _plot_type){
    double Ie_m,Ib_m,Ic_m,Ve,Vb,Vc,Vbe,Vbc,Ie,Ib,Ic;

    Ie_m = terminal("E")->getMeasure( TTerminal::CURRENT );
    // test: common_emiit

    Ib_m = terminal("B")->getMeasure( TTerminal::CURRENT );
    Ic_m = terminal("C")->getMeasure( TTerminal::CURRENT );

    Ve = terminal("E")->getVoltage() - Ie_m * parameter("RE")->getDouble();
    Vb = terminal("B")->getVoltage() - Ib_m * parameter("RB")->getDouble();
    Vc = terminal("C")->getVoltage() - Ic_m * parameter("RC")->getDouble();




    Vbe = Vb - Ve;
    Vbc = Vb - Vc;

    double Vth = VT(param("TNOM"));
    double Ibf = param("IS")  * ( exp(Vbe/param("NF")/Vth) - 1.0 );
    double Ile = param("ISE") * ( exp(Vbe/param("NE")/Vth) - 1.0 );
    double Ibr = param("IS")  * ( exp(Vbc/param("NR")/Vth) - 1.0 );
    double Ilc = param("ISC") * ( exp(Vbc/param("NC")/Vth) - 1.0 );
    double Ibe = Ibf / param("BF") + Ile;
    double Ibc = Ibr / param("BR") + Ilc;

    double Ibf1 = (Ibe - Ile) * param("BF"),
            Ibr1 = (Ibc - Ilc) * param("BR"),
            KqBtem = 0.0;

    if(param("IKF")){
        KqBtem = 4.0 * ( Ibf1/param("IKF") );
    }
    if(param("IKR")){
        KqBtem += 4.0 *( Ibr1/param("IKR") );
    }

    double tempVAF=0.0,tempVAR=0.0;
    if(param("VAF")){
        tempVAF = Vbc / param("VAF");
    }

    if(param("VAR")){
        tempVAR = Vbe / param("VAR");
    }

    double KqB = 0.5 * (1.0/( 1.0 - tempVAF - tempVAR ) ) * (1.0 + KqBtem);
    double Ice = (Ibf1-Ibr1) / KqB;
    double ibc = 0.0;

    double Cbcj = 0.0,Cbct=0.0,Cbej=0.0;
    if( Vbc -param("FC")*param("VJC") > 0.0 ){
        Cbcj = param("CJC")*pow(1.0-param("FC"),-1.0-param("MJC"))*(1.0 -param("FC")*(1.0+param("MJC"))+param("MJC")*Vbc/param("VJC"));
    }else{
        Cbcj = param("CJC")*pow( 1.0 - Vbc/param("VJC"),-param("MJC") );
        Cbct = param("TR")*param("IS")*exp( Vbc/param("NR")/Vth )/(param("NR")*Vth);
        ibc = 0.0;
    }

    if(Vbe-param("FC")*param("VJE") > 0.0){
        Cbej=param("CJC")*pow( 1.0 -param("FC"),-1.0-param("MJC") )*(1.0-param("FC")*(1.0+param("MJE"))+param("MJE")*Vbe/param("VJE"));
    }else{
        Cbej = param("CJE")*pow(1.0-Vbe/param("VJE"),-param("MJE"));
    }

    double tZ = 1.0;
    if(param("VTF")){
        tZ = exp(0.69*Vbc/param("VTF"));
    }
    double Cbet = param("IS")*exp(Vbe/param("NF")/Vth)*param("TF")*(1.0+param("XTF")*tZ)/(param("NF")*Vth);
    double ibe = 0.0;

    double Tibe = Ibe+ibe,
            Tibc = Ibc + ibc;

    double rb1 = (param("RBM")+(param("RB")-param("RBM"))/KqB) / param("AREA");
    double Vbx = Vbc + (Tibe+Tibc) * param("RB");

    double Cbx;

    if(Vbx-param("FC")*param("VJC") > 0.0){
        Cbx = (1.0 - param("XCJC"))*param("CJC")*pow(1.0-param("FC"),-1.0-param("MJC"))*(1.0 - param("FC")*(1.0+param("MJC"))+param("MJC")*Vbx/param("VJC"));
    }else{
        Cbx = (1.0 - param("XCJC"))*param("CJC")*pow(1.0-Vbx/param("VJC"),-param("MJC"));
    }
    double ibx = 0.0;


    Ic = Ice - Tibc - ibx;
    Ib = ibx + Tibc+Tibe;
    Ie = -(Ice+Tibe);

    //    Ib = baseCurrent( Vbe, Vbc );
    //    Ic = collectorCurrent( Vbe, Vbc );
    //    Ie = Ic + Ib;


    terminal( "E" )->setCurrent( Ie );
    terminal( "B" )->setCurrent( Ib );
    //    terminal( "B" )->setCurrent( Vbe*Vbe );
    terminal( "C" )->setCurrent( Ic );
}

QVector<QMap<TDevice::Axis, double> > BJT::simulate(QString _plot_type, STEP_RANGE _range){

    QMutexLocker locker(&mutexSimulate);
    QProcess *proc = new QProcess(0);

    QString spicePath( NGSPICE_PATH);
    QStringList spiceArg;
    spiceArg << "-b" << "-objt_sim.out" << "bjt_sim.cir";

    QFile cirFile( "bjt_sim.cir" ),
            outFile("bjt_sim.out");


    if(!cirFile.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate )){

        delete proc;
        //    return;
    }
    // Жёстко земля E
    double Vbe = 0.0, Vce=0.0, Ib = 0.0;

    Vbe = terminal("B")->getVoltage() - terminal("E")->getVoltage();
    Vce = terminal("C")->getVoltage() - terminal("E")->getVoltage();

    Ib = terminal("B")->getCurrent();

    MODEL_STRUCT _model = getModel();

    QByteArray _circuit("");


    _circuit.append( QString("Tsunami\n\n"));
    _circuit.append( QString("q1 2 1 0 qmodel\n"));


    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        // Id(Vg)| Vd = const
        _circuit.append( QString("Vbe 1 0 %1\n").arg(Vbe) );
        _circuit.append( QString("Vce 2 0 %1\n").arg(Vce) );
        _circuit.append( QString(".dc Vbe %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
        _circuit.append( QString(".print dc i(Vbe)\n") );

    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        _circuit.append( QString("Ib 0 1 %1\n").arg(Ib) );
        _circuit.append( QString("Vce 2 0 %1\n").arg(Vce) );
        _circuit.append( QString(".dc Vce %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
        _circuit.append( QString(".print dc i(Vce)\n") );
    }else if(_plot_type.compare( "betta", Qt::CaseInsensitive )==0){
        //        _circuit.append()
        // error;
    }



    _circuit.append( ".options noacct nopage\n" );
    // #TODO: fix
    setPolarity("NPN");

    if( polarity() == TDevice::POLARITY_P ){
        _circuit.append( ".model qmodel PNP\n" );
    }else if( polarity() == TDevice::POLARITY_N ) {
        _circuit.append( ".model qmodel NPN\n" );
    }else{
        _circuit.append( ".model qmodel PNP\n" );
    }


    if(_model.name.compare( "Gummel-Poon", Qt::CaseInsensitive ) == 0){
        _circuit.append("+ LEVEL=1\n");
    }else if(_model.name.compare( "VBIC", Qt::CaseInsensitive ) == 0){
        _circuit.append("+ LEVEL=4\n");
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


    double I=0.0,V=0.0;
    while(!outFile.atEnd()){
        QList<QByteArray> _columns = outFile.readLine().trimmed().split('\t');
        if(_columns.count() == 3){
            QMap<TDevice::Axis,double> _map;
            V = _columns.at(1).toDouble();
            I = _columns.at(2).toDouble();

            _map.insert( AXIS_X, V );
            _map.insert( AXIS_Y, -I);

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

QVector<QMap<TDevice::Axis, double> > BJT::getPlotData(QString _plot_type, STEP_RANGE _range)
{QMutexLocker locker(&mutexSimulate);
    QProcess *proc = new QProcess(this);

    QString spicePath( NGSPICE_PATH );
    QStringList spiceArg;
    spiceArg << "-b" << "-objt_plot.out" << "bjt_plot.cir";

    QFile cirFile( "bjt_plot.cir" ),
            outFile("bjt_plot.out");


    if(!cirFile.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate )){

        delete proc;
        //    return;
    }
    // Жёстко земля E
    double Vbe = 0.0, Vce=0.0, Ib=0.0;

    Vbe = terminal("B")->getVoltage() - terminal("E")->getVoltage();
    Vce = terminal("C")->getVoltage() - terminal("E")->getVoltage();
    Ib = terminal("B")->getCurrent();

    MODEL_STRUCT _model = getModel();

    QByteArray _circuit("");


    _circuit.append( QString("Tsunami\n\n"));
    _circuit.append( QString("q1 2 1 0 qmodel\n"));


    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        // Id(Vg)| Vd = const
        _circuit.append( QString("Vbe 1 0 %1\n").arg(Vbe) );
        _circuit.append( QString("Vce 2 0 %1\n").arg(Vce) );
        _circuit.append( QString(".dc Vbe %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
        _circuit.append( QString(".print dc i(Vbe)\n") );

    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        _circuit.append( QString("Ib 0 1 %1\n").arg(Ib) );
        _circuit.append( QString("Vce 2 0 %1\n").arg(Vce) );
        _circuit.append( QString(".dc Vce %1 %2 %3\n").arg(_range.start).arg(_range.end).arg(_range.step) );
        _circuit.append( QString(".print dc i(Vce)\n") );
    }else{
        // error;
    }



    _circuit.append( ".options noacct nopage\n" );
    // #TODO: fix
//    setPolarity("NPN");

    if( polarity() == TDevice::POLARITY_P ){
        _circuit.append( ".model qmodel PNP\n" );
    }else if( polarity() == TDevice::POLARITY_N ) {
        _circuit.append( ".model qmodel NPN\n" );
    }else{
        _circuit.append( ".model qmodel NPN\n" );
    }


    if(_model.name.compare( "Gummel-Poon", Qt::CaseInsensitive ) == 0){
        _circuit.append("+ LEVEL=1\n");
    }else if(_model.name.compare( "VBIC", Qt::CaseInsensitive ) == 0){
        _circuit.append("+ LEVEL=4\n");
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


    double I=0.0,V=0.0;
    while(!outFile.atEnd()){
        QList<QByteArray> _columns = outFile.readLine().trimmed().split('\t');
        if(_columns.count() == 3){
            QMap<TDevice::Axis,double> _map;
            V = _columns.at(1).toDouble();
            I = _columns.at(2).toDouble();

            _map.insert( AXIS_X, V );
            _map.insert( AXIS_Y, -I);

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

QString BJT::image(){
    QString img("");

    if( polarity() == TDevice::POLARITY_N ){
        img = ":/devices/bjt-npn";
    }else{
        img = ":/devices/bjt-pnp";
    }


    return img;

}

void BJT::init(){
    // Gummel-Poon
    // DC

    MODEL_STRUCT _model = getModel();

    if(_model.name.compare( "Gummel-Poon", Qt::CaseInsensitive ) == 0){



        addParameter( "IS",  "", 1e-15  );
        addParameter( "BF",  "", 100.0  );
        addParameter( "BR",  "",  1.0 );
        addParameter( "VAF",  "", INFINITY   ); //inf
        addParameter( "VAR",  "", INFINITY ); //inf
        addParameter( "NF",  "",  1.0 );
        addParameter( "NR",  "",  1.0 );
        addParameter( "NE",  "",  1.5 );
        addParameter( "NC",  "",  2.0 );
        addParameter( "ISE",  "",  0.0 );
        addParameter( "ISC",  "",  0.0 );
        addParameter( "IKF",  "",  INFINITY ); //inf
        addParameter( "IKR",  "",  INFINITY ); //inf
        // Ohmic parasitics
        addParameter( "RB",  "",   0.0);
        addParameter( "IRB",  "",  INFINITY );
        addParameter( "RBM",  "",  0.0 );
        addParameter( "RE",  "",   0.0 );
        addParameter( "RC",  "",   0.0 );
        addParameter( "TNOM", "", 27.0 );

    }else if(_model.name.compare( "VBIC", Qt::CaseInsensitive ) == 0){
        //sss
        addParameter( "AFN", "Flicker noise exponent for current" , 1.0 );
        addParameter( "AJC", "Base-collector capacitance switching parameter", -0.5 );
        addParameter( "AJE", "Base-emitter capacitance switching parameter", -0.5 );
        addParameter( "AJS", "Substrate-collector capacitance switching parameter", -0.5 );
        addParameter( "AVC1", "Base-collector weak avalanche parameter 1", 0.0 );
        addParameter( "AVC2", "Base-collector weak avalanche parameter 2", 0.0 );
        addParameter( "BFN", "Flicker noise exponent for 1/f dependence", 1.0 );
        addParameter( "CBCO", "Extrinsic base-collector overlap capacitance", 0.0 );
        addParameter( "CBEO", "Extrinsic base-emitter overlap capacitance", 0.0);
        addParameter( "CJC", "Base-collector intrinsic zero bias capacitance", 0.0 );
        addParameter( "CJCP", "Substrate-collector zero bias capacitance", 0.0 );
        addParameter( "CJE", "Base-emitter zero bias capacitance", 0.0 );
        addParameter( "CJEP", "Base-collector extrinsic zero bias capacitance", 0.0 );
        addParameter( "CTH", "Thermal capacitance", 0.0 );
        addParameter( "EA",  "Activation energy for IS", 1.12 );
        addParameter( "EAIC", "Activation energy for IBCI/IBEIP", 1.12 );
        addParameter( "EAIE", "Activation energy for IBEI", 1.12);
        addParameter( "EAIS", "Activation energy for IBCIP", 1.12);
        addParameter( "EANC", "Activation energy for IBCN/IBENP", 1.12);
        addParameter( "EANE", "Activation energy for IBEN", 1.12);
        addParameter( "EANS", "Activation energy for IBCNP", 1.12);
        addParameter( "FC", "Forward bias depletion capacitance limit", 0.0);
        addParameter( "GAMM", "Epi doping parameter", 0.0);
        addParameter( "HRCF", "High-current RC factor", 1.0 );
        addParameter( "IBCI", "Ideal base-collector saturation current", 1e-16);
        addParameter( "IBCIP", "Ideal parasitic base-collector saturation current", 0.0 );
        addParameter( "IBCN", "Non-ideal base-collector saturation current", 1e-15);
        addParameter( "IBCNP", "Non-ideal parasitic base-collector saturation current", 0.0);
        addParameter( "IBEI", "Ideal base-emitter saturation current", 1e-18);
        addParameter( "IBEIP", "Ideal parasitic base-emitter saturation current", 0.0 );
        addParameter( "IBEN", "Non-ideal base-emitter saturation current", 1e-15);
        addParameter( "IBENP", "Non-ideal parasitic base-emitter saturation current", 0.0);
        addParameter( "IKF", "Forward knee current", 2e-3);
        addParameter( "IKP", "Parasitic knee current", 2e-4);
        addParameter( "IKR", "Reverse knee current", 2e-4);
        addParameter( "IS", "Transport saturation current", 1e-16);
        addParameter( "ISP", "Parasitic transport saturation current", 1e-16);
        addParameter( "ITF", "Coefficient of TF dependence in Ic", 1e-3);
        addParameter( "KFN", "Base-emitter flicker noise constant",0.0);
        addParameter( "MC", "Base-collector grading coefficient", 0.33);
        addParameter( "ME", "Base-emitter grading coefficient", 0.33);
        addParameter( "MS", "Substrate-collector grading coefficient", 0.33);
        addParameter( "NCI", "Ideal base-collector emission coefficient", 1.0);
        addParameter( "NCIP", "Ideal parasitic base-collector emission coefficient", 1.0);
        addParameter( "NCN", "Non-ideal base-collector emission coefficient", 2.0);
        addParameter( "NCNP", "Non-ideal parasitic base-collector emission coefficient", 2.0);
        addParameter( "NEI", "Ideal base-emitter emission coefficient", 1.0);
        addParameter( "NEN", "Non-ideal base-emitter emission coefficient", 2.0);
        addParameter( "NF", "Forward emission coefficient", 1.0);
        addParameter( "NFP", "Parasitic forward emission coefficient", 1.0 );
        addParameter( "NR", "Reverse emission coefficient", 1.0);
        addParameter( "PC", "Base-collector built-in potential", 0.75);
        addParameter( "PE", "Base-emitter built-in potential", 0.75);
        addParameter( "PS", "Substrate-collector built-in potential", 0.75);
        addParameter( "QCO", "Epi charge parameter", 0.0);
        addParameter( "QTF", "Variation of TF with base-width modulation", 0.0);
        addParameter( "RBI", "Intrinsic base resistance", 1e-1);
        addParameter( "RBP", "Parasitic base resistance", 1e-1);
        addParameter( "RBX", "Extrinsic base resistance", 1e-1);
        addParameter( "RCI", "Intrinsic collector resistance", 1e-1);
        addParameter( "RCX", "Extrinsic collector resistance", 1e-1);
        addParameter( "RE", "Emitter resistance", 1e-1);
        addParameter( "RS", "Substrate resistance", 1e-1);
        addParameter( "RTH", "Thermal resistance", 0.0);
        addParameter( "TAVC", "Temperature coefficient of AVC2", 0.0);
        addParameter( "TD", "Forward excess-phase delay time", 0.0);
        addParameter( "TF", "Forward transit time", 1e-11);
        addParameter( "TNF", "Temperature coefficient of NF",0.0 );
        addParameter( "TR", "Reverse transit time",1e-11);
        addParameter( "TREF", "Nominal measurement temperature of parameters", 27.0 );
        addParameter( "VEF", "Forward Early voltage", 0.0);
        addParameter( "VER", "Reverse Early voltage", 0.0);
        addParameter( "VO", "Epi drift saturation voltage", 0.0);
        addParameter( "VTF", "Coefficient of TF dependence on Vbc",0.0);
        addParameter( "WBE", "Portion of IBEI from Vbei, 1-WBE from Vbex", 1.0);
        addParameter( "WSP", "Portion of ICCP from Vbep, 1-WSP from Vbci", 1.0);
        addParameter( "XII", "Temperature exponent of IBEI/IBCI/IBEIP/IBCIP", 3.0);
        addParameter( "XIN", "Temperature exponent of IBEN/IBCN/IBENP/IBCNP", 3.0);
        addParameter( "XIS", "Temperature exponent of IS", 3.0);
        addParameter( "XRB", "Temperature exponent of base resistance", 1.0);
        addParameter( "XRC", "Temperature exponent of collector resistance", 1.0);
        addParameter( "XRE", "Temperature exponent of emitter resistance", 1.0);
        addParameter( "XRS", "Temperature exponent of substrate resistance", 1.0);
        addParameter( "XTF", "Coefficient of TF bias dependence", 0.0);
        addParameter( "XVO", "Temperature exponent of VO", 0.0);
    }



}

void BJT::setGround(QString ground)
{
    ground = ground.toUpper();
    if(ground == "E"){
        mCommon = COM_EMITTER;

    }else if(ground == "B"){
        mCommon = COM_BASE;
    }else if(ground == "C"){
        mCommon = COM_COLLECTOR;
    }
}

void BJT::setPolarity(QString polarity)
{
    polarity = polarity.toUpper();
    if(polarity == "NPN" || polarity == "P"){
        TDevice::setPolarity(TDevice::POLARITY_N);
    }else if(polarity == "PNP" || polarity == "N"){
        TDevice::setPolarity(TDevice::POLARITY_P);

    }else{
        TDevice::setPolarity(TDevice::POLARITY_UNDEF);
    }
}

QString BJT::groundName()
{
    switch(mCommon){
    case COM_EMITTER:
        return "E";
    case COM_BASE:
        return "B";
    case COM_COLLECTOR:
        return "C";
    case COM_UNDEF:
    default:
        break;
    }

    return QString("");
}

QString BJT::polarityName()
{
    switch(polarity()){
    case TDevice::POLARITY_P:
        return "PNP";
    case TDevice::POLARITY_N:
        return "NPN";
    case TDevice::POLARITY_UNDEF:
    default:
        break;
    }

    return "";
}

QStringList BJT::constantTitles(QString plot_type){
    QStringList _constants;

    switch(mCommon){
    case COM_EMITTER:
        if(plot_type == "in" || plot_type == "betta"){
            _constants << "Vc";
        }else if(plot_type == "out"){
            _constants <<  "Ib";
        }
        break;
    case COM_BASE:
        if(plot_type == "in" || plot_type == "betta"){
            _constants << "Vc";
        }else if(plot_type == "out"){
            _constants <<  "Ib";
        }
        break;
    case COM_COLLECTOR:
        break;
    case COM_UNDEF:
    default:
        break;
    }

    return _constants;

}

QStringList BJT::columnTitles(QString plot_type)
{
    QStringList _columns;

    switch(mCommon){
    case COM_EMITTER:
        if(plot_type == "in"){
            _columns  << "Vb" << "Ib";
        }else if(plot_type == "out"){
            _columns   << "Vc" <<  "Ic";
        }else if(plot_type == "betta"){
            _columns << "Vb" << "Ib" << "Vc" << "Ic" << "Betta";
        }
        break;
    case COM_BASE:
        if(plot_type == "in"){
            _columns  << "Ve" << "Ie";
        }else if(plot_type == "out"){
            _columns  << "Vc" <<  "Ic";
        }else if(plot_type == "betta"){
            _columns << "Ie" << "Ic" << "Betta";
        }
        break;
    case COM_COLLECTOR:
        if(plot_type == "in"){
            _columns  << "Vb" << "Ib";
        }else if(plot_type == "out"){
            _columns  << "Ve" <<  "Ie";
        }else if(plot_type == "betta"){
            _columns << "Ib" << "Ie" << "Betta";
        }
        break;
    case COM_UNDEF:
    default:
        break;
    }

    return _columns;
}

QMap<TDevice::Axis, double> BJT::computeValue(QString plot_name, QMap<QString, double> values)
{
    QMap<TDevice::Axis, double> value;
    if(plot_name == "in"){
        if(values.contains("Ib") && values.contains("Vb")){
            value.insert( TDevice::AXIS_X , values["Vb"] );
            value.insert( TDevice::AXIS_Y , values["Ib"] );
        }
    }else if(plot_name == "out"){
        if(values.contains("Ic") && values.contains("Vc")){
            value.insert( TDevice::AXIS_X , values["Vc"] );
            value.insert( TDevice::AXIS_Y , values["Ic"] );

        }
    }else if(plot_name == "betta"){
        if(values.contains("Ib") && values.contains("Ic")){
            if(values.contains("Betta")){
                value.insert( TDevice::AXIS_X ,  values["Ic"] );
                value.insert( TDevice::AXIS_Y , values["Betta"] );
            }else if(values.contains("Ib") != 0.0){
                value.insert( TDevice::AXIS_X ,  values["Ic"] );
                value.insert( TDevice::AXIS_Y , values["Ic"] / values["Ib"] );
            }

        }
    }else{
        value.insert( TDevice::AXIS_X , 0 );
        value.insert( TDevice::AXIS_Y , 0 );

    }

    return value;
}


double BJT::baseCurrent(double Vbe, double Vbc)
{
    double Ib = 0.0;

    if(param("BF") != 0.0){
        Ib += Ifrw_dif(Vbe)/param("BF");
    }

    if(param("BR") != 0.0){
        Ib += Irvr_dif(Vbc)/param("BR");
    }

    Ib += Irec_emitter(Vbe) + Irec_collector(Vbc);

    return Ib;
}

double BJT::collectorCurrent(double Vbe, double Vbc)
{
    double Ic = 0.0;

    Ic = (Ifrw_dif(Vbe)-Irvr_dif(Vbc))/NqB(Vbe,Vbc);

    if(param("BR") != 0){
        Ic -=  Irvr_dif(Vbc)/param("BR");
    }

    Ic -= Irec_collector(Vbc);

    return Ic;
}

double BJT::VT(double T)
{
    double Vt;
    Vt = 8.6171e-5*(T+273.15);

    return Vt;
}

double BJT::q1s(double Vbe, double Vbc)
{
    double q = 1;

    if(param("VAR") != 0.0){
        q -= Vbe/param("VAR");
    }

    if(param("VAF") != 0.0){
        q -= Vbc/param("VAF");
    }

    q = 1/q;

    return q;
}

double BJT::q2s(double Vbe, double Vbc)
{
    double q;
    q = 0;

    if(param("IKF") != 0.0){
        q += Ifrw_dif(Vbe)/param("IKF");
    }

    if( param("IKR") != 0.0 ){
        q += Irvr_dif(Vbc)/param("IKR");
    }

    return q;
}

double BJT::NqB(double Vbe, double Vbc)
{
    double N;
    N = (q1s(Vbe,Vbc)/2)*(1+sqrt(1+4*q2s(Vbe,Vbc)));

    return N;
}

double BJT::Ifrw_dif(double Vbe)
{
    double I;
    I = param("IS")*( exp(Vbe/(param("NF")*VT(param("TNOM")))) - 1 );

    return I;
}

double BJT::Irvr_dif(double Vbc)
{
    double I;
    I = param("IS")*( exp(Vbc/(param("NR")*VT(param("TNOM")))) - 1 );

    return I;
}

double BJT::Irec_emitter(double Vbe)
{
    double I;
    I = param("ISE")*( exp(Vbe/(param("NE")*VT(param("TNOM")))) - 1 );

    return I;
}

double BJT::Irec_collector(double Vbc)
{
    double I;
    I = param("ISC")*( exp(Vbc/(param("NC")*VT(param("TNOM")))) - 1 );

    return I;
}
