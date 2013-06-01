#include "formmeasures.h"
#include "ui_formmeasures.h"

#include "gui/editormeasures.h"
#include "core/tdblayer.h"
#include "delegates/delegates.h"
#include "dialogs/dialogs.h"
#include "gui_func.h"

FormMeasures::FormMeasures(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormMeasures)
{
    ui->setupUi(this);

    QStringListModel *modelDataset = new QStringListModel(ui->listDataset),
            *modelMeasures = new QStringListModel(ui->listMeasures);

    ui->listDataset->setModel( modelDataset );
    ui->listMeasures->setModel( modelMeasures );


    QStandardItemModel *model = new QStandardItemModel(ui->tblInfo);
    QStringList labels;
    model->setHorizontalHeaderLabels( labels << trUtf8("1") << trUtf8("2") );
    ui->tblInfo->setModel( model );
    ui->tblInfo->setEditTriggers( QAbstractItemView::NoEditTriggers );

    ui->tblInfo->setItemDelegateForColumn(0, new DelegateReadOnly(ui->tblInfo));


    connect(ui->btnAccept,SIGNAL(clicked()),this,SLOT(clickAccept()));
//    connect(ui->btnAddMeasure,SIGNAL(clicked()),this,SLOT(showEditorMeasures()));
    connect(ui->btnAddMeasure,SIGNAL(clicked()),this,SLOT(clickAddMeasure()));
    connect(ui->listDataset,SIGNAL(clicked(QModelIndex)),this,SLOT(selectDataset(QModelIndex)));
    connect(ui->listMeasures,SIGNAL(clicked(QModelIndex)),this,SLOT(selectMeasure(QModelIndex)));
    connect(ui->actionAddSet,SIGNAL(triggered()),this,SLOT(clickAddSet()));
    connect(ui->btnAddSet,SIGNAL(clicked()),this,SLOT(clickAddSet()));
    connect(ui->actionAddMeasure,SIGNAL(triggered()),this,SLOT(showEditorMeasures()));
    connect(ui->btnEditMeasure,SIGNAL(clicked()),this,SLOT(clickEditMeasure()));
}

void FormMeasures::setDevice(TDevice *device) {
    managerMeasures_ = new ManagerMeasures(device);
    updateDatasetList();
}

FormMeasures::~FormMeasures(){
    dataset_.clear();
    measure_.clear();

    delete managerMeasures_;
    delete ui;
}

void FormMeasures::showEditorMeasures() {
    if(managerMeasures_->dataset_id() == -1){
        QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Выберите набор измерений"));
        return;
    }
    DialogAddMeasure dialog(this);
    dialog.setTypes(  managerMeasures_->device()->plotTitles() );
    if(dialog.exec() != QDialog::Accepted){
        return;
    }
    EditorMeasures *form = new EditorMeasures(dialog.name(),dialog.type(),managerMeasures_, this);
    form->show();

    connect(form,SIGNAL(changeMeasures()),this,SLOT(updateMeasures()));


}

void FormMeasures::updateDatasetList(){
   QStringList datasetList;

   TDBLayer *dbLayer = TDBLayer::getInstance();
   dbLayer->bindQuery("SELECT name FROM datasets WHERE device_id=:id")
           ->bindValue("id",managerMeasures_->device()->id())
           ->exec();
   while(dbLayer->isNext()){
       datasetList.append( dbLayer->value("name").toString() );
   }

   QStringListModel *modelDataset = static_cast<QStringListModel *>(ui->listDataset->model());
   modelDataset->setStringList( datasetList );

   delete dbLayer;

}

void FormMeasures::selectDataset(QModelIndex index){
    QStringListModel *modelMeasures = static_cast<QStringListModel *>(ui->listDataset->model());
    QString _dataset = modelMeasures->data(index, Qt::DisplayRole).toString();

    managerMeasures_->setDataset( _dataset );

    dataset_ = _dataset;

    updateMeasureList( _dataset );

    ui->tblInfo->model()->removeRows(0,ui->tblInfo->model()->rowCount() );
    ui->tblInfo->setEnabled( false );
}

void FormMeasures::selectMeasure(QModelIndex index)
{
    ui->tblInfo->setEnabled( true );
    QStringListModel *modelMeasures = static_cast<QStringListModel *>(ui->listMeasures->model());

    QString _measure = modelMeasures->data(index, Qt::DisplayRole).toString();


    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT m.author AS author, m.created AS created, m.changed AS changed, d.name AS dataset_name, m.plot_type AS plot_type "
                       "FROM measures AS m, datasets AS d WHERE d.device_id=:id AND d.id=:dataset AND d.id=m.dataset_id AND m.name=:name")
            ->bindValue(":id",managerMeasures_->device()->id())
            ->bindValue(":dataset",managerMeasures_->dataset_id())
            ->bindValue(":name",_measure)
            ->exec();

    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblInfo->model());

    model->removeRows(0, model->rowCount());

    if(!dbLayer->isNext()){
        measure_ = "";
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return;
    }

    measure_ = _measure;
    QString _plot_type = dbLayer->value("plot_type").toString();
    _plot_type = managerMeasures_->device()->plot(_plot_type).title;

    model->appendRow( rowInfo( trUtf8("Набор"),   dbLayer->value("dataset_name").toString() ) );
    model->appendRow( rowInfo( trUtf8("Тип"),     _plot_type ) );
    model->appendRow( rowInfo( trUtf8("Автор"),   dbLayer->value("author").toString() ) );
    model->appendRow( rowInfo( trUtf8("Создан"),  dbLayer->value("created").toDate().toString("dd.MM.yyyy") ) );
    model->appendRow( rowInfo( trUtf8("Изменён"), dbLayer->value("changed").toDate().toString("dd.MM.yyyy") ) );

    delete dbLayer;
}

void FormMeasures::clickAddSet(){
    QString _name_set = QInputDialog::getText(this,trUtf8("Добавить набор"),trUtf8("Название:"));

    if(managerMeasures_->CreateSet(_name_set)){
        messageInfo("Набор измерений добавлен");
        updateDatasetList();
    }else{
        messageInfo("При создании набора измерений возникла ошибка");
    }
}

void FormMeasures::clickAddMeasure(){
    if(managerMeasures_->dataset_id() == -1){
        messageWarning("Выберите набор измерений");
        return;
    }
    DialogAddMeasure dialog(this);
    dialog.setTypes(  managerMeasures_->device()->plotTitles() );
    if(dialog.exec() != QDialog::Accepted){
       return;
    }

    int measureId = TMeasure::create( managerMeasures_->dataset_id(), dialog.name(), dialog.type() );
    if(measureId == -1){
        messageError( "Измерение не создано" );
    }else{
        messageInfo( "Измерение создано" );
        updateMeasures();
    }

    return;
}

void FormMeasures::clickEditMeasure()
{
    if(dataset_.isEmpty() || measure_.isEmpty()){
        return;
    }
    int id = managerMeasures_->getMeasureID( dataset_,  measure_);

    if(id == -1){
        return;
    }

    EditorMeasures *form = new EditorMeasures(id,managerMeasures_, this);
    form->show();

    connect(form,SIGNAL(changeMeasures()),this,SLOT(updateMeasures()));
}

void FormMeasures::updateMeasures()
{
    if(!dataset_.isEmpty()){
        updateMeasureList( dataset_ );
    }
}

void FormMeasures::clickAccept(){

    emit  acceptDataset( managerMeasures_->dataset_id() );
    close();
}


void FormMeasures::updateMeasureList(QString dataset)
{
    QStringList measureList;
    QStringListModel *modelMeasures = static_cast<QStringListModel *>(ui->listMeasures->model());

    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT m.name AS name FROM measures AS m, datasets AS d WHERE d.device_id=:id AND d.name=:name AND d.id=m.dataset_id")
            ->bindValue(":id",managerMeasures_->device()->id())
            ->bindValue(":name",dataset)
            ->exec();
    if(!dbLayer->isRequested()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return;
    }

    while(dbLayer->isNext()){
        measureList.append( dbLayer->value("name").toString() );
    }

     modelMeasures->setStringList( measureList );
     delete dbLayer;

}

QList<QStandardItem *> FormMeasures::rowInfo(QString name, QString value)
{
    QList<QStandardItem *> row;

    row.append( new QStandardItem( name ) );
    row.append( new QStandardItem( value ) );

    return row;
}
