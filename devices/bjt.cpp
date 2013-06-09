#include "bjt.h"

#include "core/tparameter.h"
#include "core/tcircuit.h"

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

    setType( DEVICE_BJT );


    addPlot( "in", trUtf8("Входная ВАХ"), "Vb", "Ib" );
    addPlot( "out", trUtf8("Выходная ВАХ") ,  "Vc", "Ic");
    addPlot( "betta", trUtf8("Бетта"),  "Ic", "Betta");




}

QVector<QPointF> BJT::simulate(QString _plot_type, STEP_RANGE _range){

    QMutexLocker locker(&mutexSimulate);

    TCircuit* circuit = new TCircuit("BJT simulate","bjt.cir",NGSPICE_PATH);
    TNet* net;

    // Жёстко земля E
    double Vbe = 0.0, Vce=0.0, Ib = 0.0;
    Vbe = terminal("B")->getVoltage() - terminal("E")->getVoltage();
    Vce = terminal("C")->getVoltage() - terminal("E")->getVoltage();
    Ib = terminal("B")->getCurrent();

    net = TNet::createNet( "q1" );
    net->setTerminals(3, 2, 1, 0 );
    net->addValue( "bjt" );
    circuit->addNet( net );
    net = TNet::createNet( "Vce" );
    net->setTerminals(2, 2, 0 );
    net->addValue( Vce );
    circuit->addNet( net );

    CIRCUIT_ANALYZE_DC analyzeDc = { "", _range.start, _range.end, 0.01 };



    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        // Id(Vg)| Vd = const
        net = TNet::createNet( "Vbe" );
        net->setTerminals(2, 1, 0 );
        net->addValue( Vbe );
        circuit->addNet( net );
        ::strcpy( analyzeDc.name, "Vbe");

        circuit->addPrint(2, "dc", "i(Vbe)" );
    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        net = TNet::createNet( "Ib" );
        net->setTerminals(2, 0, 1 );
        net->addValue( Ib );
        circuit->addNet( net );
        ::strcpy( analyzeDc.name, "Vce");
        circuit->addPrint(2, "dc", "i(Vce)" );
    }
    circuit->setAnalyze( analyzeDc );

    CIRCUIT_MODEL circuitModel = {"bjt", "NPN",0};
    if( polarity() == TDevice::POLARITY_P ){
        strcpy(circuitModel.polarity,"PNP");
    }

    MODEL_STRUCT model = getModel();
    circuitModel.level = getLevel( &model.name );

    foreach( TParameter *param,getParameters() ){
        if(param->isInclude()){
            circuitModel.parameters.insert(param->name(),param->value());
        }
    }

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

QVector<QPointF> BJT::getPlotData(QString _plot_type, STEP_RANGE _range)
{   QMutexLocker locker(&mutexSimulate);
    TCircuit* circuit = new TCircuit("BJT simulate","bjtp.cir",NGSPICE_PATH);
    TNet* net;

    // Жёстко земля E
    double Vbe = 0.0, Vce=0.0, Ib = 0.0;
    Vbe = terminal("B")->getVoltage() - terminal("E")->getVoltage();
    Vce = terminal("C")->getVoltage() - terminal("E")->getVoltage();
    Ib = terminal("B")->getCurrent();

    net = TNet::createNet( "q1" );
    net->setTerminals(3, 2, 1, 0 );
    net->addValue( "bjt" );
    circuit->addNet( net );
    net = TNet::createNet( "Vce" );
    net->setTerminals(2, 2, 0 );
    net->addValue( Vce );
    circuit->addNet( net );

    CIRCUIT_ANALYZE_DC analyzeDc = { "", _range.start, _range.end, 0.01 };

    if(_plot_type.compare( "in", Qt::CaseInsensitive )==0){
        // Id(Vg)| Vd = const
        net = TNet::createNet( "Vbe" );
        net->setTerminals(2, 1, 0 );
        net->addValue( Vbe );
        circuit->addNet( net );
        ::strcpy( analyzeDc.name, "Vbe");

        circuit->addPrint(2, "dc", "i(Vbe)" );
    }else if(_plot_type.compare("out", Qt::CaseInsensitive)==0){
        net = TNet::createNet( "Ib" );
        net->setTerminals(2, 0, 1 );
        net->addValue( Ib );
        circuit->addNet( net );
        ::strcpy( analyzeDc.name, "Vce");
        circuit->addPrint(2, "dc", "i(Vce)" );
    }
    circuit->setAnalyze( analyzeDc );

    CIRCUIT_MODEL circuitModel = {"bjt", "NPN",0};
    if( polarity() == TDevice::POLARITY_P ){
        strcpy(circuitModel.polarity,"PNP");
    }

    MODEL_STRUCT model = getModel();
    circuitModel.level = getLevel( &model.name );

    foreach( TParameter *param,getParameters() ){
        if(param->isInclude()){
            circuitModel.parameters.insert(param->name(),param->value());
        }
    }

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

QPointF BJT::computeValue(QString plot_name, QMap<QString, double> values)
{
    QPointF point;
    if(plot_name == "in"){
        if(values.contains("Ib") && values.contains("Vb")){
            point = QPointF( values["Vb"], values["Ib"] );
        }
    }else if(plot_name == "out"){
        if(values.contains("Ic") && values.contains("Vc")){
            point = QPointF( values["Vc"], values["Ic"] );
        }
    }else if(plot_name == "betta"){
//        if(values.contains("Ib") && values.contains("Ic")){
//            if(values.contains("Betta")){
//                value.insert( TDevice::AXIS_X ,  values["Ic"] );
//                value.insert( TDevice::AXIS_Y , values["Betta"] );
//            }else if(values.contains("Ib") != 0.0){
//                value.insert( TDevice::AXIS_X ,  values["Ic"] );
//                value.insert( TDevice::AXIS_Y , values["Ic"] / values["Ib"] );
//            }

//        }
    }else{
        point = QPointF( INFINITY, INFINITY );

    }

    return point;
}

