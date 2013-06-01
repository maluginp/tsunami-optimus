#include "dialogaddmeasure.h"
#include "ui_dialogaddmeasure.h"

DialogAddMeasure::DialogAddMeasure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddMeasure)
{
    ui->setupUi(this);
}

DialogAddMeasure::~DialogAddMeasure()
{
    delete ui;
}

void DialogAddMeasure::setTypes(QMap<QString,QString> plots)
{
    ui->boxType->clear();
    foreach(QString _name,plots.keys()){
        ui->boxType->addItem( plots.value(_name), _name );
    }
}


QString DialogAddMeasure::name()
{
    return ui->lnName->text();
}

QString DialogAddMeasure::type()
{
    int id = ui->boxType->currentIndex();

    if(id != -1){
        return ui->boxType->itemData(id).toString();
    }
    return QString("");
}
