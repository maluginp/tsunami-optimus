#include "dialogopendevice.h"
#include "ui_dialogopendevice.h"
#include "gui/delegates/delegates.h"
#include "core/tdblayer.h"
#include "dialogs.h"

DialogOpenDevice::DialogOpenDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOpenDevice)
{
    ui->setupUi(this);
    QStringListModel *model = new QStringListModel( ui->listDevices );
    QStandardItemModel *modelInfo = new QStandardItemModel(ui->tblInfo);
    ui->tblInfo->setModel( modelInfo );
    //    ui->tblInfo->setItemDelegateForColumn(0, new DelegateReadOnly(ui->tblInfo));

    QStringList _labels;
    _labels << "a" << "b";
    modelInfo->setHorizontalHeaderLabels( _labels );

    ui->listDevices->setModel( model );
    ui->tblInfo->setItemDelegateForColumn(0, new DelegateReadOnly(ui->tblInfo));
    ui->listDevices->setEditTriggers( QAbstractItemView::NoEditTriggers );

    updateDeviceList();

    connect(ui->btnAccept,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->listDevices,SIGNAL(clicked(QModelIndex)),this,SLOT(setDevice(QModelIndex)));
    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(newDevice()));
}

DialogOpenDevice::~DialogOpenDevice(){
    delete ui;
}

QString DialogOpenDevice::device(){
    return type_;
}

QString DialogOpenDevice::name(){
    return name_;
}

int DialogOpenDevice::id(){
    return id_;
}


void DialogOpenDevice::setDevice(QModelIndex index){

    QString _name = index.data(Qt::DisplayRole).toString();

    // Load
    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT * FROM devices WHERE name=:name")
            ->bindValue(":name",_name)
            ->exec();

    if(!dbLayer->isNext()){
        qDebug() << dbLayer->getError();
        id_ = -1;
        name_ = "";
        type_ = "";
        return;
    }

    id_ = dbLayer->value("id").toInt();
    name_ = dbLayer->value("name").toString();
    type_ = dbLayer->value("device").toString();

    // Fetch polarity & ground
    QVariantMap _mapSetting = TDevice::parseMap( dbLayer->value("settings").toString() );



    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblInfo->model());
    model->removeRows( 0, model->rowCount() );

    //    QStringList _labels;
    //    _labels << "1" << "2";
    //    model->setHorizontalHeaderLabels( _labels );

    model->appendRow( rowInfo( trUtf8("Название"), dbLayer->value("name").toString() ) );

    QString _type = dbLayer->value("device").toString();
    if(_mapSetting.contains("polarity")){
        _type = _mapSetting.value("polarity").toString()+"-"+_type;
    }

    model->appendRow( rowInfo( trUtf8("Тип"),    _type   ) );
    //    if(_mapSetting.contains("polarity")){
    //        model->appendRow( rowInfo( trUtf8("Полярность"), _mapSetting.value( "polarity" ).toString() )  );
    //    }
    //    if(_mapSetting.contains( "ground" )){
    //        model->appendRow( rowInfo( trUtf8("Земля"), _mapSetting.value( "ground" ).toString() )  );
    //    }


    model->appendRow( rowInfo( trUtf8("Создан"),   dbLayer->value("created").toDate().toString("dd.MM.yyyy") ) );
    model->appendRow( rowInfo( trUtf8("Изменён"),  dbLayer->value("changed").toDate().toString("dd.MM.yyyy") ) );


    delete dbLayer;
    return;


}

void DialogOpenDevice::newDevice(){
    DialogNewDevice dialog(this);

    if(dialog.exec() != QDialog::Accepted){
        return;
    }
    updateDeviceList();

}

void DialogOpenDevice::updateDeviceList() {
    QStandardItemModel *modelInfo = static_cast<QStandardItemModel *>(ui->tblInfo->model());
    modelInfo->removeRows( 0, modelInfo->rowCount() );
    id_ = -1;
    type_ = "";
    name_ = "";

    QStringListModel *model = static_cast<QStringListModel *>(ui->listDevices->model());

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT name FROM devices")
            ->exec();

    QStringList _listDevices;

    while(dbLayer->isNext()){
        _listDevices << dbLayer->value("name").toString();
    }

    model->setStringList( _listDevices );

    delete dbLayer;



}

QList<QStandardItem *> DialogOpenDevice::rowInfo(QString name, QString value){
    QList<QStandardItem *> row;

    row.append( new QStandardItem( name ) );
    row.append( new QStandardItem( value ) );

    return row;
}
