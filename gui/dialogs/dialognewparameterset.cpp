#include "dialognewparameterset.h"
#include "ui_dialognewparameterset.h"




DialogNewParameterSet::DialogNewParameterSet(ManagerParameterSet *manager,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewParameterSet)
{
    ui->setupUi(this);

    setManager(manager);


    ui->boxTemplates->addItems( manager->listManagers() );

    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(clickAdd()));
}



DialogNewParameterSet::~DialogNewParameterSet(){



    delete ui;
}

void DialogNewParameterSet::clickAdd(){

    QString name,tpl;

    name = ui->lnName->text();
    tpl  = ui->boxTemplates->currentText();

    if(!managerParameterSet->Create( name, tpl )){
        qDebug() << QString("New parameterset didn't add. %s (tpl:%s)").arg(name).arg(tpl);
        reject();
    }

    accept();
}

/*
  <parameter name="" initial="" maximum="" minimum="" fixed="" />

 */
