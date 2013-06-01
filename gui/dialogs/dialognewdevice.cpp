#include "dialognewdevice.h"
#include "ui_dialognewdevice.h"
#include "core/tdevice.h"

const char *DEVICE_NAMES[] = { "DIODE" , "BJT", "JFET" , "MOSFET" };

DialogNewDevice::DialogNewDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewDevice)
{
    ui->setupUi(this);
    QStringList items;
    int count = count_of(DEVICE_NAMES);
    for(int i=0; i < count; i++){
        items.append( QString(DEVICE_NAMES[i]) );
    }

    ui->boxType->addItems( items );

    ui->boxType->setCurrentIndex( 0 );

    ui->boxGround->hide();
    ui->labelGround->hide();

    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(clickAdd()));
}

DialogNewDevice::~DialogNewDevice()
{
    delete ui;
}

QString DialogNewDevice::name()
{
    return ui->lnName->text();
}

QString DialogNewDevice::device()
{
    return ui->boxType->currentText();
}

QString DialogNewDevice::polarity(){
    return ui->boxPolarity->currentText();
}
void DialogNewDevice::clickAdd(){

    QString name,device;
    int device_id = -1;
    name = ui->lnName->text();
    device = ui->boxType->currentText();

    if(!TDevice::Create( name, device,device_id )){
        QMessageBox::information(this,trUtf8("Ошибка"),trUtf8("Устройство не создано"),QMessageBox::Ok);
        reject();
    }

    // #TODO:
    TDevice *_device = TDevice::createObject( device_id, device );

    if(_device->Open()){
        QVariantMap _map;

        if(device.toUpper() == "BJT"){
            if(polarity().compare( "PNP",Qt::CaseInsensitive ) == 0){
                _map.insert( "polarity", "N" );
            }else if(polarity().compare( "NPN",Qt::CaseInsensitive ) == 0){
                _map.insert( "polarity", "P" );
            }
            _map.insert( "ground", "E" );
        }else if(device.toUpper() == "JFET"){
            if(polarity().compare( "NFET",Qt::CaseInsensitive ) == 0){
                _map.insert( "polarity", "N" );
            }else if(polarity().compare( "PFET",Qt::CaseInsensitive ) == 0){
                _map.insert( "polarity", "P" );
            }

            _map.insert( "ground", "S" );
        }else if(device.compare( "MOSFET", Qt::CaseInsensitive ) == 0 ){

            if(polarity().compare( "NMOS",Qt::CaseInsensitive ) == 0){
                _map.insert( "polarity", "N" );
            }else if(polarity().compare( "PMOS",Qt::CaseInsensitive ) == 0){
                _map.insert( "polarity", "P" );
            }

            _map.insert( "ground", "S" );

            double _temp = 0.0;
            bool ok;
            _temp = ui->widthChannelLineEdit->text().toDouble(&ok);
            if(!ok){
                _temp = 0.0;
            }
            _map.insert( "W", _temp );
            _temp = ui->lengthChannelLineEdit->text().toDouble(&ok);
            if(!ok){
                _temp = 0.0;
            }
            _map.insert( "L", _temp );

        }

        //
        _device->saveSetting( _map  );


    }
    delete _device;




    accept();
}

void DialogNewDevice::on_boxType_currentIndexChanged(const QString &arg1){
    ui->boxPolarity->show();
    ui->labelPolarity->show();

    if(arg1.compare("MOSFET",Qt::CaseInsensitive) == 0){
        ui->widthChannelLabel->show();
        ui->widthChannelLineEdit->show();
        ui->lengthChannelLabel->show();
        ui->lengthChannelLineEdit->show();

    }else{
        ui->widthChannelLabel->hide();
        ui->widthChannelLineEdit->hide();
        ui->lengthChannelLabel->hide();
        ui->lengthChannelLineEdit->hide();
        if(arg1.compare("DIODE",Qt::CaseInsensitive) == 0){
            ui->boxPolarity->hide();
            ui->labelPolarity->hide();
        }
    }

    ui->boxPolarity->clear();
    QStringList _items;
    if(arg1.compare("MOSFET",Qt::CaseInsensitive) == 0){
        _items << "NMOS" << "PMOS";
    }else if(arg1.compare("BJT",Qt::CaseInsensitive) == 0){
        _items << "NPN" << "PNP";
    }else if(arg1.compare("JFET",Qt::CaseInsensitive) == 0){
        _items << "NFET" << "PFET";
    }
    if(_items.count() > 0){
        ui->boxPolarity->addItems( _items );
    }



}
