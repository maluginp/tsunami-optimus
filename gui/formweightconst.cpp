#include "formweightconst.h"
#include "ui_formweightconst.h"
#include <QtCore>
#include <QtGui>

#include "core/tmeasure.h"
#include "core/tdevice.h"
#include "gui/delegates/delegates.h"



FormWeightConst::FormWeightConst(int strategy_id, int measure_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormWeightConst)
{
    ui->setupUi(this);


    mStrategyId = strategy_id;
    mMeasureId  = measure_id;
    //open measure id

    // open graph weights

    ui->plotter->setRangeZoom( Qt::Horizontal | Qt::Vertical );
    ui->plotter->setRangeDrag( Qt::Horizontal | Qt::Vertical );
    ui->plotter->setupFullAxesBox();

    mMeasures = TStrategy::measures( strategy_id, measure_id  );

    int device_id = TStrategy::deviceIdByStrategyId( strategy_id ) ;

    TDevice *device = TDevice::openDevice( device_id );

    device->Open();


//    TDevice *device = new TDevice();
//    device->setID( TStrategy::deviceIdByStrategyId( strategy_id ) );
//    device->Open();


    QStandardItemModel *model =  new QStandardItemModel(ui->weightsTableView);
    ui->weightsTableView->setModel( model );

    int count_db = mMeasures.count();
    for(int graph_id=0; graph_id < count_db; graph_id++){

        QCPGraph *graph =  ui->plotter->addGraph();
        graph->setProperty("id",graph_id);

        STRATEGY_DB _strategy_db = mMeasures.at( graph_id );

        QVariantMap _map;
        foreach(QString _constName, _strategy_db.db.constants.keys()){
            _map.insert( _constName,_strategy_db.db.constants.value(_constName) );
        }


        graph->setProperty( "constants", _map);

        QVector<double> X,Y;
        int count_row = _strategy_db.db.table.count();
        for(int row=0; row < count_row; row++){

            MEASURE_ROW _row = _strategy_db.db.table.at( row );
            QMap<QString,double> _values = _strategy_db.db.constants;
            int col_index = 0;
            foreach( QString _colname, _strategy_db.db.columns ){
                _values.insert( _colname, _row.row.at( col_index ) );
                col_index++;
            }


            QPointF point = device->computeValue( _strategy_db.type, _values );
            X << point.x();
            Y << point.y();
        }

        graph->addData( X, Y );
        graph->setScatterStyle(QCP::ssCircle);
        graph->setScatterSize(3);

    }
    ui->plotter->rescaleAxes();

    double _range = ui->plotter->yAxis->range().upper + ui->plotter->yAxis->range().upper/4;
    ui->plotter->yAxis->setRangeUpper(_range);


    mColumnWeightIndex =  mMeasures.at( 0 ).db.columns.count();


    ui->plotter->setInteractions( QCustomPlot::iSelectPlottables
                                  | QCustomPlot::iSelectItems );



    QCPItemText *textLabel = new QCPItemText(ui->plotter);
    ui->plotter->addItem(textLabel);
    textLabel->setPositionAlignment(Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText("");
    textLabel->setFont(QFont(font().family(), 16)); // make font a bit larger



//    graph =  ui->plotter->addGraph();
//    graph->addData(X ,Y1);
//    graph->setName( "VB2" );




    QCPItemTracer *tracer = new QCPItemTracer(ui->plotter);
    tracer->setProperty("graph","0");
//    tracer->setGraph( graph );
//    tracer->setGraphKey( 2 );
//    tracer->setStyle( QCPItemTracer::tsCircle );
    tracer->setStyle( QCPItemTracer::tsSquare );
    QPen _pen(Qt::red);
    _pen.setWidth(2);
    tracer->setPen(_pen);
//    tracer->setBrush(QBrush(Qt::red ));
//    tracer->setSize(30);
    tracer->setSize(6);

    ui->plotter->addItem(tracer);

//    ui->plotter->setAntialiasedElement( QCP::aeAll,true );

    ui->weightsTableView->setContextMenuPolicy(Qt::CustomContextMenu);


    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(SaveGraph()));
    connect(ui->weightsTableView,SIGNAL(clicked(QModelIndex)),this,SLOT(weightsTableClick(QModelIndex)));
//    connect(tracer,SIGNAL(selectionChanged(bool))
    connect(ui->plotter,SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)),this,SLOT(plottableClick(QCPAbstractPlottable*,QMouseEvent*)));
//    connect(ui->plotter,SIGNAL(itemClick(QCPAbstractItem*,QMouseEvent*)),this,SLOT(itemClick(QCPAbstractItem*,QMouseEvent*)));

    connect(ui->weightsTableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(weightsTableContextMenu(QPoint)));

}

FormWeightConst::~FormWeightConst()
{
    delete ui;
}

//void FormWeightConst::plottableDoubleClick(QCPAbstractPlottable *plot, QMouseEvent *mouse)
//{
//    QCPItemText *textLabel = static_cast<QCPItemText *>(ui->plotter->item(0));

//    textLabel->setText( plot->name() + " DoubleClick" );

//}

void FormWeightConst::plottableClick(QCPAbstractPlottable *plot, QMouseEvent *mouse)
{

    QCPItemText *textLabel = static_cast<QCPItemText *>(ui->plotter->item(0));
    QCPGraph *graph = static_cast<QCPGraph *>(plot);

    int graph_id = graph->property("id").toInt();

    if(mSelectedGraph == graph_id){
        return;
    }


    STRATEGY_DB _strategy_db = mMeasures.at( graph_id );

    QStringList _text;
    foreach( QString _name, _strategy_db.db.constants.keys() ){
        _text << QString("%1=%2").arg(_name)
                 .arg( _strategy_db.db.constants.value( _name ) );
    }
    textLabel->setText( _text.join("\n") );


    if(mLastClickGraph != graph_id){
        mLastClickGraph = graph_id;
        return;
    }

    mSelectedGraph = graph_id;

    qDebug() << graph_id;

    // Определить X
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->weightsTableView->model());

    model->clear();

    QStringList _labels = _strategy_db.db.columns;
    _labels << trUtf8("Вес");

    int count_columns = _strategy_db.db.columns.count();
    for(int i=0; i < count_columns;i++){
        ui->weightsTableView->setItemDelegateForColumn( i, new DelegateReadOnly(ui->weightsTableView) );
    }


    model->setHorizontalHeaderLabels( _labels );

    int count_row = _strategy_db.db.table.count();
//    QStandardItem *item = new QStandardItem(count_row,_strategy_db.db.columns.count()+1);
    for(int row=0; row < count_row; row++){
        QList<QStandardItem *> items;
        MEASURE_ROW _row = _strategy_db.db.table.at( row );
        int col = 0;
        foreach(QString _colname,_strategy_db.db.columns){
            items << new QStandardItem( QString::number( _row.row.at(col) ) );
            col++;
        }
        items << new QStandardItem( QString::number( _strategy_db.weights.value(_row.row.at(0),1.0) )  );

        model->appendRow( items );

    }



//    QCPItemTracer *tracer = static_cast<QCPItemTracer *>(ui->plotter->item(1));
////    tracer->setParent();
//    tracer->setGraph( (QCPGraph *)plot );
//    tracer->setGraphKey(5);
//    textLabel->setText( plot->name() + "\n Click" );



//    plot-


}

void FormWeightConst::itemClick(QCPAbstractItem *item, QMouseEvent *event)
{
//    qDebug() << item->property("ssss");
    return;
}

void FormWeightConst::weightsTableClick(QModelIndex index){
    int row =  index.row();
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->weightsTableView->model());

    double X = model->item(row)->data(Qt::DisplayRole).toDouble();

    QCPItemTracer *tracer = static_cast<QCPItemTracer *>(ui->plotter->item(1));
    QCPGraph *graph = ui->plotter->graph(mSelectedGraph);
    tracer->setGraph( graph );
    tracer->setGraphKey( X );
    ui->plotter->replot();

    return;

}

void FormWeightConst::SaveGraph(){

    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->weightsTableView->model());

    STRATEGY_DB _strategy_db = mMeasures.at( mSelectedGraph );

    int count_row = model->rowCount();

    QMap<double,double> _weights;

    for( int row=0; row < count_row; row++){
        double _value = model->item(row,mColumnWeightIndex)->data(Qt::DisplayRole).toDouble();
        if( _value != 1.0 ){
            double _name = model->item(row)->data(Qt::DisplayRole).toDouble();
            _weights.insert( _name, _value );
        }
    }

    _strategy_db.weights = _weights;
    mMeasures[mSelectedGraph] = _strategy_db;

    TStrategy *strategy = new TStrategy( mStrategyId );
    strategy->saveWeights( mMeasures );




}

void FormWeightConst::weightsTableContextMenu(QPoint point){

    QMenu *menu = new QMenu(ui->weightsTableView);

    menu->addAction(trUtf8("Установить значения"),this,SLOT(weightsTableSetValueAction()));


    menu->popup( ui->weightsTableView->mapToGlobal( point ) );
//    menu.exec( point );

}

void FormWeightConst::weightsTableSetValueAction(){
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->weightsTableView->model());

    QModelIndexList _list = ui->weightsTableView->selectionModel()->selection().indexes();

    bool ok;
    double _value = QInputDialog::getDouble(this,trUtf8("Присвоить значение"),trUtf8("Значение"),1.0,0.1,100.0,1,&ok);

    if(!ok){
        return;
    }

    qDebug() << "selected;";
    foreach( QModelIndex _index, _list ){
        model->setItem( _index.row(), 2, new QStandardItem( QString::number(_value)));
    }

}
