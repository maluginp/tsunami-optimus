#include "deviceworkspace.h"
#include "ui_deviceworkspace.h"
#include <QtCore>
#include <QtGui>

#include "gui/gui.h"
#include "gui/dialogs/dialogs.h"

DeviceWorkspace::DeviceWorkspace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeviceWorkspace)
{
    ui->setupUi(this);



    workspaceManager_ = new ManagerWorkspace();
    workspaceManager_->connectDatabase();




    //    connect(workspaceManager,SIGNAL(deviceOpened()),this,SLOT(reloadWorkspace()));

    connect(ui->btnSetModel,SIGNAL(clicked()),this,SLOT(showFormModels()));
    //    connect(ui->btnSetGraphics,SIGNAL(clicked()),this,SLOT(showFormGraphics()));
    connect(ui->btnSetParameters,SIGNAL(clicked()),this,SLOT(showFormParameters()));
    connect(ui->btnSetMeasures,SIGNAL(clicked()),this,SLOT(showFormMeasures()));
    connect(ui->btnExtraction,SIGNAL(clicked()),this,SLOT(runExtraction()));
    connect(ui->btnSetStrategy,SIGNAL(clicked()),this,SLOT(showFormStrategy()));
    connect(this,SIGNAL(reload()),this,SLOT(reloadWorkspace()));
    connect(ui->actionNewDevice,SIGNAL(triggered()),this,SLOT(showDialogNewDevice()));
//    connect(ui->boxPolarity,SIGNAL(currentIndexChanged(QString)),this,SLOT(changePolarity(QString)));
//    connect(ui->boxGround,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeGround(QString)));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(showDialogOpenDevice()));
    connect(ui->actionSettings,SIGNAL(triggered()),this,SLOT(showFormSetting()));
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionClose,SIGNAL(triggered()),this,SLOT(closeDevice()));
    connect(ui->actionRemoveDevices,SIGNAL(triggered()),this,SLOT(showDialogRemoveDevice()));
    //    showDialogOpenDevice();
    isDeviceOpened_ = false;


}

DeviceWorkspace::~DeviceWorkspace()
{
    delete ui;
}

TDevice* DeviceWorkspace::device()
{
    return workspaceManager_->device();
}

void DeviceWorkspace::showDialogOpenDevice(){
    DialogOpenDevice dialog(this);
    if(dialog.exec() == QDialog::Accepted){
        if(!workspaceManager_->openDevice( dialog.id() )){
            QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Устройство не может быть открыто"));
            return;
        }

        setWindowTitle( device()->name() +trUtf8(" - � абочая область") );
        QString _polarity_name = device()->polarityName();
        ui->polarityTitleLabel->setText( _polarity_name );
        QString _img = device()->image();
        if(!_img.isEmpty()){

            QPixmap pix(_img);

            ui->deviceImage->setPixmap( pix );

        }


        reloadWorkspace();
        isDeviceOpened_= true;

    }
    dialog.close();
}

void DeviceWorkspace::showDialogNewDevice()
{
    DialogNewDevice dialog(this);
    if(dialog.exec() == QDialog::Accepted){

        workspaceManager_->openDevice( dialog.name(), dialog.device() );

    }
    emit reloadWorkspace();
}

void DeviceWorkspace::showDialogRemoveDevice(){
    QString _name("");
    if(isDeviceOpened()){
        _name = device()->name();
    }
    DialogDeleteDevices dialog(_name,this);

    if(dialog.exec() == QDialog::Accepted && isDeviceOpened()){
        emit reloadWorkspace();
    }

}

void DeviceWorkspace::closeDevice()
{
}

void DeviceWorkspace::showFormModels(){

    if(isDeviceOpened()){
        FormModels *form = new FormModels(device()->deviceType(),this);
        connect(form,SIGNAL(acceptModel(int)),this,SLOT(slotSetModelID(int)));
        form->show();
    }else{
        QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Устройство не выбрано"));
    }

}

void DeviceWorkspace::showFormGraphics(){
    if(isDeviceOpened()){
        FormGraphics *form = new FormGraphics();
        form->show();
    }else{
        QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Устройство не выбрано"));
    }

}

void DeviceWorkspace::showFormParameters(){
    if(isDeviceOpened()){
        FormParameters *form = new FormParameters(this);
        form->setDevice( device() );
        connect(form,SIGNAL(acceptParameters(int)),this,SLOT(slotSetParameterSetID(int)));

        form->show();
    }else{
        QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Устройство не выбрано"));
    }

}

void DeviceWorkspace::showFormMeasures()
{
    if(isDeviceOpened()){
        FormMeasures *form = new FormMeasures(this);
        form->setDevice( device() );
        connect(form,SIGNAL(acceptDataset(int)),this,SLOT(slotSetDataset(int)));
        form->show();
    }else{
        QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Устройство не выбрано"));
    }

}

void DeviceWorkspace::showFormStrategy(){
    if(isDeviceOpened()){
        FormStrategy *form = new FormStrategy(this);
        connect(form,SIGNAL(acceptStrategy(int)),this,SLOT(slotSetStrategyID(int)));
        form->setDevice( device() );
        form->show();
    }else{
        QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Устройство не выбрано"));
    }

}

void DeviceWorkspace::showFormSetting()
{
    FormSetting settingForm(this);
    settingForm.exec();
    settingForm.close();


}

void DeviceWorkspace::runExtraction(){
    if(isDeviceOpened()){
        FormMinimisation form(device()->id(),this);
        form.setModal( true );
        form.exec();
    }else{
        QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Устройство не выбрано"));
    }

}

void DeviceWorkspace::reloadWorkspace(){
    QMap<QString, QString> deviceData = workspaceManager_->loadDataDevice();
    ui->labelModel->setText( deviceData["model"] );
    ui->labelStrategy->setText( deviceData["strategy"] );
    ui->labelParameters->setText( deviceData["parameters"] );
    ui->labelDataset->setText( deviceData["dataset"] );
}

void DeviceWorkspace::slotSetModelID(int id)
{
    workspaceManager_->setDataDevice("model",id);

    reloadWorkspace();
}

void DeviceWorkspace::slotSetStrategyID(int id) {
    workspaceManager_->setDataDevice("strategy",id);
    reloadWorkspace();
}

void DeviceWorkspace::slotSetParameterSetID(int id) {
    workspaceManager_->setDataDevice("parameters",id);
    reloadWorkspace();
}

void DeviceWorkspace::slotSetDataset(int id) {
    workspaceManager_->setDataDevice("dataset",id);
    reloadWorkspace();
}
