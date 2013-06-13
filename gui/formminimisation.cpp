#include "formminimisation.h"
#include "ui_formminimisation.h"
#include "minimisations/minimisations.h"
#include "core/tdblayer.h"
#include "dialogs/dialogs.h"
#include "core/tsetting.h"


FormMinimisation::FormMinimisation(int device_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormMinimisation)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel( ui->tblParameters );
    ui->tblParameters->setModel( model );


    managerExtractor = new ManagerExtractor();

    if(!managerExtractor->openDevice( device_id )){
        qDebug() << "Can't open device";
    }

    ui->tabGraphics->clear();

    QStringList _plots;
    _plots << "in" << "out";


    foreach(QString _plot,_plots){
        QCustomPlot *plot = new QCustomPlot(ui->tabGraphics);
        plot->xAxis->setLabel( managerExtractor->device()->plot(_plot).axis_x );
        plot->yAxis->setLabel( managerExtractor->device()->plot(_plot).axis_y );
        plot->setupFullAxesBox();
        plot->setRangeDrag(Qt::Horizontal|Qt::Vertical);
        plot->setRangeZoom(Qt::Horizontal|Qt::Vertical);

//        plot->setInteraction( QCustomPlot::iSelectAxes|QCustomPlot::iSelectPlottables, true );
        plot->setInteraction( QCustomPlot::iSelectAxes, true );
        QCPItemText *label = new QCPItemText(plot);
        label->setText("");
        label->setPositionAlignment( Qt::AlignRight );
        label->position->setType(QCPItemPosition::ptAxisRectRatio);
        label->position->setCoords(0.25, 0.1); // place position at center/top of axis rect
        label->setText("");
        label->setFont(QFont(font().family(), 13)); // make font a bit larger

        plot->addItem( label );



        connect( plot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)),this, SLOT( axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)) );
        connect( plot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(plottableClick(QCPAbstractPlottable*,QMouseEvent*)) );
        ui->tabGraphics->addTab( plot, _plot );
    }

    mInitialParameters = managerExtractor->parameterSet()->initials();
    mOptimizeParameters = mInitialParameters;


    model->setVerticalHeaderLabels( mInitialParameters.keys() );

    QStringList _labelParameters;

    _labelParameters << trUtf8("Начальное") << trUtf8("Оптимизир.");

    model->setHorizontalHeaderLabels(_labelParameters);

    int row=0;

    foreach(QString _param_name,mInitialParameters.keys()){

        QBrush brush(Qt::white);
        if(managerExtractor->parameterSet()->fixed(_param_name)){
            brush.setColor( QColor(0xDA,0xDA,0xDA) );
        }

        double _param_value = mInitialParameters.value( _param_name );
        QStandardItem * _item = new QStandardItem();
        _item->setData(_param_value,Qt::DisplayRole);
        _item->setBackground( brush );
        model->setItem( row, 0, _item );

        _item = new QStandardItem();
        _item->setData(_param_value,Qt::DisplayRole);
        _item->setBackground( brush );
        model->setItem( row, 1, _item );

        row++;
    }




    ui->logger->clear();


    ui->progressMinimisation->setValue(0);


    mStarted = false;

    ui->btnOperation->setText( trUtf8("Запуск")  );

    ui->labelError->setText("NaN");
    //    ui->labelIterations->setText( QString("1/%1").arg(managerExtractor->extractor()->maxIterations()) );
    ui->labelStatus->setText(trUtf8("Остановлено"));

    ui->tblParameters->setEditTriggers( QAbstractItemView::NoEditTriggers );
    ui->btnSaveParameters->setEnabled( false );

    managerExtractor->setMinimisator();
    replotGraphics( mInitialParameters );

    mTimerRunning = new QTimer();
    mTimerRunning->setInterval( 500 );


    ui->tblParameters->setContextMenuPolicy( Qt::CustomContextMenu );

    connect(ui->tblParameters,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT( parametersContextMenu(QPoint) ));
    connect(ui->actionCopyToClipboard,SIGNAL(triggered()),this,SLOT(copyToClipboard()));

    connect(ui->btnOperation,SIGNAL(clicked()),this,SLOT(startExtraction()));
    connect(ui->btnSavePlot,SIGNAL(clicked()),this,SLOT(saveGraphic()));
    connect(ui->btnSaveParameters,SIGNAL(clicked()),this,SLOT(saveParameters()));
    connect(ui->btnStop,SIGNAL(clicked()),this,SLOT(stopMinimisation()));
    connect(mTimerRunning,SIGNAL(timeout()),this,SLOT(timerTimeout()));

}

FormMinimisation::~FormMinimisation()
{
    delete ui;

    delete managerExtractor;

}

void FormMinimisation::startExtraction()
{
    ///
    mInitRanges.clear();
    ui->btnSaveParameters->setEnabled( false );
    ui->progressMinimisation->setValue( 0 );
    ui->logger->clear();

    managerExtractor->setMinimisator();

    double _startFunctionError = managerExtractor->extractor()->computeFunctionError();

    ui->labelError->setText(QString("%1").arg(_startFunctionError));
    TDataset *dataset = managerExtractor->strategy()->dataset();
    QList<TMeasure *> measures = dataset->measures(  );
    measures.clear();
    delete dataset;

    ui->labelStatus->setText(trUtf8("Выполняется"));
    mTimerRunning->start();
    threadFunc = QtConcurrent::run(managerExtractor->extractor(),&Extractor::runMinimisation);


    ui->labelIterations->setText( QString("0/%1").arg(managerExtractor->extractor()->maxIterations()) );
    ui->btnStop->setEnabled( true );
    ui->btnOperation->setEnabled(false);

    mStarted = true;

    connect(managerExtractor->extractor(),SIGNAL(doneIteration(int,double)),this,SLOT(doneIteration(int,double)));
    connect(managerExtractor->extractor(),SIGNAL(doneMinimisation()),this,SLOT(doneMinimisation()));
    connect(this,SIGNAL(stopExtraction()),managerExtractor->extractor(),SLOT(Stop()));

    return;
}

void FormMinimisation::doneIteration(int iteration,double error){

    //    qDebug() << iteration;
    mCurrentIteration = iteration;

    QMap<QString,double> parameters = managerExtractor->extractor()->parameters();

    foreach(QString _name,mOptimizeParameters.keys()){
        if(parameters.contains(_name)){
            mOptimizeParameters[_name] = parameters.value( _name );
        }
    }



    LogParameters(iteration,mOptimizeParameters);
    Log( trUtf8("Ошибка: ")+QString::number(error) );
    ui->labelError->setText( QString::number(error) );


    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblParameters->model());

    QStandardItem *_item;

    int row = 0;
    foreach(QString _name,mOptimizeParameters.keys()){
        double _param_value = mOptimizeParameters.value( _name );

        QBrush brush(Qt::white);
        if( managerExtractor->parameterSet()->fixed(_name) ){
            brush.setColor(QColor(0xDA,0xDA,0xDA));
        }

        if( _param_value != mInitialParameters.value( _name )){
            brush.setColor(QColor("pink"));
        }

        _item = new QStandardItem();
        _item->setBackground( brush );
        _item->setData( _param_value, Qt::DisplayRole );


        model->setItem( row, 1,  _item);
        row++;
    }

    //    int percent = (iteration*100)/managerExtractor->extractor()->maxIterations();
    //    ui->progressMinimisation->setValue( percent );
    ui->labelIterations->setText( QString("%1/%2").arg(iteration).arg(managerExtractor->extractor()->maxIterations()) );


    replotGraphics(parameters);
    return;
}

void FormMinimisation::stopMinimisation()
{
    emit stopExtraction();
    threadFunc.waitForFinished();
}

void FormMinimisation::doneMinimisation()
{
    // Stop

    mTimerRunning->stop();

    ui->labelStatus->setText(trUtf8("Остановлен"));
    //        ui->labelIterations->setText( QString("%1/%").arg(managerExtractor->extractor()->maxIterations()) );
    ui->btnOperation->setText(trUtf8("Запустить"));


    ui->progressMinimisation->setValue( 0 );

    mStarted = false;

    ui->btnStop->setEnabled( false );

    ui->btnOperation->setEnabled(true);

    disconnect(managerExtractor->extractor(),SIGNAL(doneIteration(int,double)),this,SLOT(doneIteration(int,double)));
    disconnect(managerExtractor->extractor(),SIGNAL(doneMinimisation()),this,SLOT(doneMinimisation()));
    disconnect(this,SIGNAL(stopExtraction()),managerExtractor->extractor(),SLOT(Stop()));

    managerExtractor->extractor()->deleteLater();
    delete managerExtractor->extractor();


    ui->btnSaveParameters->setEnabled( true );



    return;
}

void FormMinimisation::replotGraphics(QMap<QString,double> parameters){
    foreach(QString name,parameters.keys()){
        managerExtractor->device()->parameter(name)->setValue( parameters.value(name) );
    }

    int _count_tabs = ui->tabGraphics->count();
    for(int _tab_index=0; _tab_index < _count_tabs; _tab_index++ ){
        QString _name = ui->tabGraphics->tabText( _tab_index );
        QCustomPlot *plot = static_cast<QCustomPlot *>(ui->tabGraphics->widget(_tab_index));

        plot->clearGraphs();


        mutex.lock();
        QList<EXTRACTOR_PLOT> _plots = managerExtractor->plot( _name);

//        if( ! mInitRanges.contains(_name) ){
//            if(managerExtractor->device()->polarity() == TDevice::POLARITY_N){
//                plot->xAxis->setRange( _ranges[TDevice::AXIS_X].min, _ranges[TDevice::AXIS_X].max );
//                plot->yAxis->setRange( _ranges[TDevice::AXIS_Y].min, _ranges[TDevice::AXIS_Y].max );
//            }else{
//                plot->xAxis->setRange( -_ranges[TDevice::AXIS_X].max,  -_ranges[TDevice::AXIS_X].min );
//                plot->yAxis->setRange( -_ranges[TDevice::AXIS_Y].max,  -_ranges[TDevice::AXIS_Y].min );
//            }
//            mInitRanges <<  _name ;
//        }



        foreach(EXTRACTOR_PLOT _plot,_plots){
            QCPGraph *_graph;
            QPen graphPen;
            graphPen.setWidthF(2);
            graphPen.setColor( Qt::black );

            // measure
            _graph = plot->addGraph();
            _graph->setProperty( "type", "measure" );
            _graph->setProperty( "const", _plot.constant );

            _graph->setLineStyle(QCPGraph::lsNone);

            _graph->setScatterStyle(QCP::ssCross);
//            _graph->setScatterSize(3);

            _graph->addData( _plot.measure_x, _plot.measure_y );

            // model
            _graph = plot->addGraph();
            _graph->setProperty( "type", "model" );
            _graph->setProperty( "const", _plot.constant );
            _graph->setLineStyle(QCPGraph::lsLine);
            _graph->addData( _plot.model_x, _plot.model_y );

        }

        plot->replot();
         plot->rescaleAxes();
        mutex.unlock();

    }

    return;
}

void FormMinimisation::saveParameters()
{
    DialogSaveParameters dialog(this);

    dialog.setParameterSet( managerExtractor->parameterSet()->name() );
    if(dialog.exec() == QDialog::Accepted){
        if(!dialog.isSaveAs()){
            managerExtractor->parameterSet()->setValue( mOptimizeParameters );
            if(managerExtractor->parameterSet()->Save()){
                qDebug() << "Parameters saved";
            }
        }else{
            QString _newSetName = dialog.parameterSaveAs();
            if(_newSetName.isEmpty()){
                return;
            }

            if(TParameterSet::exists( _newSetName )){
                QMessageBox::warning(this,trUtf8("Сохранение набора параметров"),trUtf8("Набор существует в базе данных"));
                return;
            }
            TParameterSet *newSet = new TParameterSet(*(managerExtractor->parameterSet()));
            newSet->setName( _newSetName );

            newSet->setValue( mOptimizeParameters );
            if(newSet->Save()){
                qDebug() << "Saved";
            }

            delete newSet;

        }
    }

    dialog.close();
    return;
}

void FormMinimisation::saveGraphic()
{


    int _tab_id = ui->tabGraphics->currentIndex();
    QString _name = ui->tabGraphics->tabText( _tab_id );
    QCustomPlot *plot = static_cast<QCustomPlot *>(ui->tabGraphics->widget(_tab_id));


    QPixmap pixmap = QPixmap::grabWidget( plot , plot->rect() );
    QClipboard * clipboard = QApplication::clipboard();
    clipboard->setPixmap( pixmap );

    return;

    QFileDialog dlg(this, trUtf8("Сохранить график"),"",tr("PNG (*.png)"));
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setViewMode(QFileDialog::List);
    dlg.selectFile(QString("%1.png").arg(_name));



    if(dlg.exec()){
        QStringList list = dlg.selectedFiles();
        QString name = list.at(0);
        if(list.count() == 1){
            plot->savePng(name);
        }
    }
}

void FormMinimisation::timerTimeout(){
    //    qDebug() << ui->progressMinimisation->value();
    if(ui->progressMinimisation->value() < 99){
        ui->progressMinimisation->setValue( ui->progressMinimisation->value()+5 );
    }else{
        ui->progressMinimisation->setValue( 0 );
    }
}

void FormMinimisation::copyToClipboard()
{

    QString cbStr;
    QClipboard *cb = QApplication::clipboard();
    QModelIndexList list =   ui->tblParameters->selectionModel()->selectedIndexes();
    int i, j, firstRow, lastRow, rowCount;

    if( list.isEmpty() ) return;

    firstRow = list.first().row();  lastRow = list.last().row();
    rowCount = lastRow - firstRow + 1;

    for(i = 0; i < rowCount; ++i, cbStr += '\n'){
        cbStr += ui->tblParameters->model()->headerData(i,Qt::Vertical).toString() + "\t";
        for(j = i; j < list.count(); j += rowCount, cbStr += '\t'){
            cbStr += ui->tblParameters->model()->data(list[ j ], Qt::EditRole).toString();

        }
    }
    cb->setText(cbStr);

}

void FormMinimisation::axisDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event){

    bool ok;

    if(part == QCPAxis::spAxisLabel){
        QString _label =  QInputDialog::getText( this, trUtf8("Название оси"),trUtf8("Название:"), QLineEdit::Normal, axis->label(), &ok );

        if(ok && !_label.isEmpty()){
            axis->setLabel( _label );
        }
    }
}



void FormMinimisation::Log(char *text)
{
    Log(text,LOG_DEFAULT);
}

void FormMinimisation::Log(QString text)
{
    Log(text,LOG_DEFAULT);
}

void FormMinimisation::Log(char *text,FormMinimisation::TYPE_LOG type)
{

    QString _text("");

    _text = trUtf8(text);
    Log(_text,type);

}

void FormMinimisation::Log(QString text, FormMinimisation::TYPE_LOG type)
{
    QString _color;

    switch(type){
    case LOG_PARAMETER:
        _color = "#8B4513";
        break;
    case LOG_WARNING:
        _color = "#B8860B";
        break;
    case LOG_ERROR:
    case LOG_ITERATION:
    case LOG_DEFAULT:
    default:
        _color = "black";

    }

    QString _text = QString("<font color=\"%2\">%1</font> ").arg(text).arg(_color);

    ui->logger->append( _text );

    //    qDebug() << _text;
}

void FormMinimisation::LogParameters(int iteration,QMap<QString, double> parameters)
{
    QStringList _params;



    if(iteration == 0){
        Log( trUtf8("Начальные значения"), LOG_PARAMETER );
    }else{
        Log( trUtf8("<br/>Итерация №")+QString::number(iteration), LOG_PARAMETER );
    }
    Log("-------------------------------------", LOG_PARAMETER);
    foreach(QString _param, parameters.keys()){
        _params << QString("%1=%2").arg(_param).arg(parameters.value(_param));
    }
    Log(_params.join(", "),LOG_DEFAULT);



}

void FormMinimisation::LogIteration(int iteration)
{
}



void FormMinimisation::parametersContextMenu(QPoint pos){

    QMenu *menu = new QMenu( ui->tblParameters );

    menu->addAction( trUtf8("Скопировать"), this, SLOT(copyToClipboard()) );

    menu->popup( ui->tblParameters->mapToGlobal( pos ) );

}

void FormMinimisation::plottableClick(QCPAbstractPlottable *graph, QMouseEvent *e){
    QCustomPlot *plot = static_cast<QCustomPlot *>( ui->tabGraphics->currentWidget() );

    QCPItemText *label = static_cast<QCPItemText *>(plot->item(0));

    label->setText( graph->property("const").toString() );
    plot->replot();

}
