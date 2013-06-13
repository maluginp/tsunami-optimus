#include "formparameters.h"
#include "ui_formparameters.h"
#include <QtCore>
#include <QtGui>

#include "delegates/delegates.h"
#include "gui/dialogs/dialogs.h"

#include "core/tdblayer.h"
#include "core/tdataset.h"

FormParameters::FormParameters(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormParameters)
{
    ui->setupUi(this);


    QStandardItemModel *model = new QStandardItemModel(0,6,ui->tblParameters);
    ui->tblParameters->setModel(model);

    QStringList labels;
    labels << trUtf8("ID") <<trUtf8("Вкл") << trUtf8("Параметр") << trUtf8("Значение") << trUtf8("Минимум") <<
              trUtf8("Максимум") << trUtf8("Константа");

    model->setHorizontalHeaderLabels(labels);

    ui->tblParameters->hideColumn(0);


    mCurrentParameterSet = "";

    ui->tblParameters->setItemDelegateForColumn( 6, new DelegateCheckBox(this) );
    ui->tblParameters->setItemDelegateForColumn( 1, new DelegateCheckBox(this) );

    ui->tblParameters->setColumnWidth(1,40);
    ui->tblParameters->setColumnWidth(3,150);
    ui->tblParameters->setColumnWidth(4,150);
    ui->tblParameters->setColumnWidth(5,150);
    ui->tblParameters->setColumnWidth(6,90);

    connect(ui->boxParameterSets,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeParameterSets(QString)));
    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(clickBtnAdd()));
    connect(ui->btnRemove,SIGNAL(clicked()),this,SLOT(clickBtnRemove()));
    connect(ui->btnAccept,SIGNAL(clicked()),this,SLOT(clickApply()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(clickCancel()));

    connect(ui->actionAddSet,SIGNAL(triggered()),this,SLOT(clickAddSet()));
    connect(ui->btnAddSet,SIGNAL(clicked()),this,SLOT(clickAddSet()));
    connect(ui->actionSaveTemplate,SIGNAL(triggered()),this,SLOT(clickSaveTemplate()));

}

FormParameters::~FormParameters()
{
    delete ui;
}

void FormParameters::setDevice(TDevice *device)
{
    mDevice = device;

    managerParameterSet = new ManagerParameterSet(device);

    reloadListSets( TDataset::name( device->parameterSetId() ) );
}

void FormParameters::changeParameterSets(QString parameterSet){

    if(parameterSet.isEmpty()){
        return;
    }

    mParameterSet = new TParameterSet(parameterSet,mDevice->id());
    if(!mParameterSet->Open()){
        qDebug() << "parameter set didn't open";
        return;
    }

    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblParameters->model());

    model->removeRows(0,model->rowCount());

    QStringList _params = mParameterSet->parameterNames( true );
    QList<QStandardItem *> items;
    foreach(QString _param,_params){

        items.append(new QStandardItem( QString::number( mParameterSet->id( _param ))));
        items.append(new QStandardItem( QString::number( mParameterSet->included(_param) ) ));
        items.append(new QStandardItem(_param));
        items.append(new QStandardItem( QString::number( mParameterSet->initial(_param) ) ));
        items.append(new QStandardItem( QString::number( mParameterSet->min(_param)) ));
        items.append(new QStandardItem( QString::number( mParameterSet->max(_param)) ));
        items.append(new QStandardItem( QString::number( mParameterSet->fixed(_param) ) ));

        model->appendRow( items );
        items.clear();
    }

    managerParameterSet->setID( mParameterSet->id() );



    return;

}

void FormParameters::clickBtnAdd(){
    QStandardItemModel *model = (QStandardItemModel *)ui->tblParameters->model();

    QList<QStandardItem *> items;

    items.append(new QStandardItem(QString::number( -1 )));
    items.append(new QStandardItem("1"));
    items.append(new QStandardItem(""));
    items.append(new QStandardItem(""));
    items.append(new QStandardItem(""));
    items.append(new QStandardItem(""));
    items.append(new QStandardItem(""));
    model->appendRow( items );

}

void FormParameters::clickBtnRemove(){
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblParameters->model());


    QModelIndex remove_index = ui->tblParameters->currentIndex();

    int id = model->item(remove_index.row())->text().toInt();

    qDebug() << QString("Remove parameter: ").arg(  model->item(remove_index.row(),1)->text() );

    // remove from base
    model->removeRow(remove_index.row());
    mParameterSet->addRemove( id );
    //    mParameterSet->addRemove(  );


}

void FormParameters::clickApply(){


    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblParameters->model());

    int count_row = model->rowCount();
    for(int row=0; row < count_row; row++){

        PARAMETER_SET _set;
        _set.id  = model->item(row,0)->text().toInt();
        _set.initial = model->item(row,3)->data(Qt::DisplayRole).toDouble();
        _set.minimum = model->item(row,4)->data(Qt::DisplayRole).toDouble();
        _set.maximum = model->item(row,5)->data(Qt::DisplayRole).toDouble();
        _set.name = model->item(row,2)->data(Qt::DisplayRole).toString();
        _set.fixed = model->item(row,6)->data(Qt::DisplayRole).toBool();
        _set.inc   = model->item(row,1)->data(Qt::DisplayRole).toBool();
        mParameterSet->setParameter( _set.name, _set );

    }

    if(mParameterSet->Save()){
        emit acceptParameters(mParameterSet->id());
    }
    close();
}

void FormParameters::clickCancel(){
    close();
}

void FormParameters::clickAddSet()
{
    DialogNewParameterSet dialog(managerParameterSet,this);

    dialog.setModal( true );
    if(dialog.exec() == QDialog::Accepted){
        reloadListSets(managerParameterSet->getCurrentName());
    }

    dialog.close();
}

void FormParameters::clickSaveTemplate(){

    QString _tpl_name = QInputDialog::getText(this,trUtf8("Сохранить как шаблон"),trUtf8("Название:"));

    if(_tpl_name.isEmpty()){
        return;
    }

    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblParameters->model());

    QMap<QString,PARAMETER_SET> _template_vars;

    int count_row = model->rowCount();
    for(int row=0; row < count_row; row++){
        PARAMETER_SET _param;
        QString name;

        name = model->item(row,2)->text();

        _param.id = -1;
        _param.initial = model->item(row,3)->text().toDouble();
        _param.minimum = model->item(row,4)->text().toDouble();
        _param.maximum = model->item(row,5)->text().toDouble();
        _param.fixed   = false;
        _param.inc     = true;
        _template_vars.insert( name, _param );

    }

    if(!managerParameterSet->CreateTemplate( _tpl_name, _template_vars )){
        qDebug() << "Template didn't create";
    }


}


void FormParameters::reloadListSets(QString selectName){
    ui->boxParameterSets->clear();

    ui->boxParameterSets->addItems( managerParameterSet->listSets() );

    if(selectName.isEmpty()){
        ui->boxParameterSets->setCurrentIndex(0);
        return;
    }

    int index = ui->boxParameterSets->findText(selectName);

    ui->boxParameterSets->setCurrentIndex( index );

}
