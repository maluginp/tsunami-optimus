#include "dialogdeletedevices.h"
#include "ui_dialogdeletedevices.h"

#include <QtCore>
#include <QtGui>
#include "core/tdblayer.h"
#include "core/tdevice.h"
DialogDeleteDevices::DialogDeleteDevices(QString filter, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDeleteDevices)
{
    ui->setupUi(this);

    QStringListModel *modelDevices = new QStringListModel(ui->devicesListView),
            *modelRemoves = new QStringListModel(ui->removesListView);

    ui->devicesListView->setModel( modelDevices );
    ui->removesListView->setModel( modelRemoves );





    loadDeviceList(filter);

    connect(ui->toRemoveButton,SIGNAL(clicked()),this,SLOT(appendToRemoveList()));
    connect(ui->fromRemoveButton,SIGNAL(clicked()),this,SLOT(removeFromRemoveList()));
    connect(ui->removeButton,SIGNAL(clicked()),this,SLOT(removeButtonClicked()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}

DialogDeleteDevices::~DialogDeleteDevices()
{
    delete ui;
}
void DialogDeleteDevices::loadDeviceList(QString filter){

    QStringListModel *model = static_cast<QStringListModel *>(ui->devicesListView->model());

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT name FROM devices")
            ->exec();

    QStringList _listDevices;

    while(dbLayer->isNext()){
        if(filter.compare( dbLayer->value("name").toString(), Qt::CaseInsensitive ) != 0){
            _listDevices << dbLayer->value("name").toString();
        }
    }

    model->setStringList( _listDevices );

    delete dbLayer;
}

void DialogDeleteDevices::appendToRemoveList(){
    QStringListModel *modelDevices = static_cast<QStringListModel *>(ui->devicesListView->model()),
            *modelRemoves = static_cast<QStringListModel *>(ui->removesListView->model());

    QStringList _devices,_removes;

    _removes = modelRemoves->stringList();
    _devices = modelDevices->stringList();

    QModelIndexList _list = ui->devicesListView->selectionModel()->selectedIndexes();
    foreach(QModelIndex idx,_list){
        if(_devices.removeOne( idx.data().toString() )){
            _removes << idx.data().toString();
        }
    }

    modelDevices->setStringList( _devices );
    modelRemoves->setStringList( _removes );

}

void DialogDeleteDevices::removeFromRemoveList()
{
    QStringListModel *modelDevices = static_cast<QStringListModel *>(ui->devicesListView->model()),
            *modelRemoves = static_cast<QStringListModel *>(ui->removesListView->model());

    QStringList _devices,_removes;

    _removes = modelRemoves->stringList();
    _devices = modelDevices->stringList();

    QModelIndexList _list = ui->removesListView->selectionModel()->selectedIndexes();
    foreach(QModelIndex idx,_list){
        if(_removes.removeOne( idx.data().toString() )){
            _devices << idx.data().toString();
        }
    }

    modelDevices->setStringList( _devices );
    modelRemoves->setStringList( _removes );

}

void DialogDeleteDevices::removeButtonClicked(){
    QStringListModel *modelRemoves = static_cast<QStringListModel *>(ui->removesListView->model());

    QStringList _removes;

    _removes = modelRemoves->stringList();

    foreach(QString _remove,_removes){

        int _id = TDevice::getIdByName( _remove );
        TDevice *device = TDevice::openDevice( _id );
        device->Delete();
        delete device;

    }
    _removes.clear();
    modelRemoves->setStringList( _removes );
}
