#include "formstrategy.h"
#include "ui_formstrategy.h"
#include <QtCore>
#include <QtGui>
#include "delegates/delegates.h"
#include "gui/formweightconst.h"

FormStrategy::FormStrategy(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormStrategy)
{
    ui->setupUi(this);

    QStandardItemModel *modelMeasures = new QStandardItemModel(ui->tblMeasures),
            *modelDescription = new QStandardItemModel(ui->descriptionTableView);
//    *modelGraphics = new QStandardItemModel(ui->tblGraphics),
//            *modelMeasures = new QStandardItemModel(ui->tblMeasures),
//            *modelIncludes = new QStandardItemModel(ui->tblIncludes);

//    ui->tblGraphics->setModel( modelGraphics );
//    ui->tblIncludes->setModel( modelIncludes );
    ui->tblMeasures->setModel( modelMeasures );
    ui->descriptionTableView->setModel( modelDescription );

    ui->listStrategies->setModel( new QStringListModel(ui->listStrategies) );



    QStringList labelsStandard,labelsIncludes;

    labelsStandard << trUtf8("#") << trUtf8("Название");
    labelsIncludes << trUtf8("#") << trUtf8("Контакт") << trUtf8("Значения");



//    modelGraphics->setHorizontalHeaderLabels( labelsStandard );
    modelMeasures->setHorizontalHeaderLabels( labelsStandard << "id" );
//    modelIncludes->setHorizontalHeaderLabels( labelsIncludes );

//    ui->tblGraphics->setItemDelegateForColumn(0, new DelegateCheckBox(ui->tblGraphics) );
    ui->tblMeasures->setItemDelegateForColumn(0, new DelegateCheckBox(ui->tblMeasures) );
//    ui->tblIncludes->setItemDelegateForColumn(0, new DelegateCheckBox(ui->tblIncludes) );

//    ui->tblGraphics->setColumnWidth(0,30);
//    ui->tblGraphics->hideColumn(2);
//    ui->tblIncludes->setColumnWidth(0,30);
    ui->tblMeasures->setColumnWidth(0,30);
//    ui->tblIncludes->setColumnWidth(1,60);

//    ui->tblIncludes->setEnabled( false );

    connect(ui->setWeightsButton,SIGNAL(clicked()),this,SLOT(setWeightsCoeff()));

    connect(ui->actionNewStrategy,SIGNAL(triggered()),this,SLOT(newStrategy()));
    connect(ui->listStrategies,SIGNAL(clicked(QModelIndex)),this,SLOT(selectStrategy(QModelIndex)));
    connect(ui->acceptButton,SIGNAL(clicked()),this,SLOT(clickAccept()));
    connect(ui->tblMeasures,SIGNAL(doubleClicked(QModelIndex)),this, SLOT(selectMeasure(QModelIndex) ));

}

FormStrategy::~FormStrategy()
{
    delete ui;
}

void FormStrategy::setDevice(TDevice *dev)
{
    strategyManager_ = new ManagerStrategy(dev);
    updateStrategyList();



}

void FormStrategy::Open(int id)
{
    setStrategy( id );
}

void FormStrategy::newStrategy(){
    bool ok;
    QString _strategy = QInputDialog::getText( this, trUtf8("Новая стратегия"), trUtf8("Название:"),QLineEdit::Normal,QString(""),&ok);

    strategyManager_->Create( _strategy );
    updateStrategyList();



}

void FormStrategy::selectStrategy(QModelIndex index)
{
    QString _name = index.data().toString();

    setStrategy( _name );



}

void FormStrategy::clickAccept(){
    int _id = id();

    saveStrategy();

    if(_id != -1){
        emit acceptStrategy( _id );
    }

    close();

}

void FormStrategy::setWeightsCoeff()
{
    FormWeightConst form( mId, measureId_, this );
    form.exec();



}

void FormStrategy::setStrategy(int id){

    strategyManager_->setId( id );

    mId = id;
    ui->labelDataset->setText( strategyManager_->datasetName() );

    ui->weightsCheckBox->setChecked( strategyManager_->strategy()->isIncludeWeight() );


    updateMeasureList();
}

void FormStrategy::setStrategy(QString name)
{
    int id = strategyManager_->strategyId( name );
    setStrategy( id );

}

void FormStrategy::updateStrategyList()
{
    QStringListModel *model = static_cast<QStringListModel *>(ui->listStrategies->model());

    QStringList _list = strategyManager_->list( strategyManager_->device()->id() ) ;
    model->setStringList( _list );

}

void FormStrategy::selectMeasure(QModelIndex index){
    if(index.column() != 1){
        return;
    }

    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblMeasures->model());
    QStandardItemModel *modelDesc = static_cast<QStandardItemModel *>(ui->descriptionTableView->model());

    modelDesc->clear();

    measureId_ = model->item( index.row(), 2 )->data(Qt::DisplayRole).toInt();

    ui->descriptionGroupBox->setEnabled( true );

    TMeasure *measure = new TMeasure(measureId_);
    if(measure->Open()){

        QList<QStandardItem *> items;
        items << new QStandardItem( trUtf8("Название") ) << new QStandardItem( measure->name() );
        modelDesc->appendRow( items );
        items.clear();

        items << new QStandardItem( trUtf8("Тип") ) << new QStandardItem( measure->plotType() );
        modelDesc->appendRow( items );
        items.clear();

        items << new QStandardItem( trUtf8("Автор") ) << new QStandardItem( measure->author() );
        modelDesc->appendRow( items );
        items.clear();

        items << new QStandardItem( trUtf8("Создан") ) << new QStandardItem( measure->created() );
        modelDesc->appendRow( items );
        items.clear();

        items << new QStandardItem( trUtf8("Изменён") ) << new QStandardItem( measure->changed());
        modelDesc->appendRow( items );


        ui->descriptionTableView->setItemDelegateForColumn( 0, new DelegateReadOnly() );
    }

}

QList<QStandardItem *> FormStrategy::getRow(bool enable,  QString name)
{
    QList<QStandardItem *> row;
    if(enable){
        row.append( new QStandardItem("1") );
    }else{
        row.append( new QStandardItem("0") );
    }
    row.append( new QStandardItem(name) );

    return row;
}

void FormStrategy::updateMeasureList(){
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblMeasures->model());
    model->removeRows(0, model->rowCount());

    QList<STRATEGY_MEASURE> _measures = strategyManager_->measures();
    QList<int> _listId = strategyManager_->strategy()->measures_id();

    int _measure_count = _measures.count();
    for(int i=0; i < _measure_count; i++){
        STRATEGY_MEASURE _measure = _measures.at(i);

        QList<QStandardItem *> row;
        if( _listId.contains( _measure.id ) ){
            row << new QStandardItem("1");
        }else{
            row << new QStandardItem("0");
        }

        row << new QStandardItem(_measure.name);
        row << new QStandardItem(QString::number(_measure.id));

        model->appendRow(row);
    }
    ui->tblMeasures->hideColumn(2);

    ui->tblMeasures->setItemDelegateForColumn(1,new DelegateReadOnly(ui->tblMeasures) );

}

void FormStrategy::saveStrategy(){
   QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblMeasures->model());
   DATASET_STRATEGY _measure;


   int _measure_count = model->rowCount();
   bool ok;
   for(int row=0; row < _measure_count;row++){
       int _id = model->item(row,2)->data(Qt::DisplayRole).toInt(&ok);
       if(!ok){
           qDebug() << model->item(row,2)->data(Qt::DisplayRole).toString();
           continue;
       }

       if(model->item(row,0)->data(Qt::DisplayRole).toBool()){
          _measure.measures << _id;
       }
   }


   strategyManager_->strategy()->setIncludeMeasures( _measure.measures );
//   strategyManager->strategy()->setDatasetStrategy( _measure );
   strategyManager_->strategy()->setDatasetId( strategyManager_->device()->datasetId() );
   strategyManager_->strategy()->setIncludeWeight( ui->weightsCheckBox->isChecked() );

   //Graphics
//   QMap<QString,bool> _plots;
//   model = static_cast<QStandardItemModel *>(ui->tblGraphics->model());
//   int _plot_count = model->rowCount();
//   for(int row=0; row < _plot_count;row++){
//       QString _name = model->item(row,2)->data(Qt::DisplayRole).toString();
//       bool _inc = model->item(row,0)->data(Qt::DisplayRole).toBool();

//       _plots.insert( _name,_inc );

//   }
//   strategyManager->strategy()->setPlots( _plots );

   strategyManager_->strategy()->Save();

}
