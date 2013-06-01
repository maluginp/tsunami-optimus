#include "dialogsaveparameters.h"
#include "ui_dialogsaveparameters.h"

DialogSaveParameters::DialogSaveParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSaveParameters)
{
    ui->setupUi(this);
}

DialogSaveParameters::~DialogSaveParameters()
{
    delete ui;
}

void DialogSaveParameters::setParameterSet(QString _param_set){
//    ui->parameterSetLineEdit->setText( _param_set );
    ui->parameterSetLabel->setText( _param_set );
}

bool DialogSaveParameters::isSaveAs(){
    return ui->saveAsCheckBox->isChecked();
}

QString DialogSaveParameters::parameterSaveAs(){
    return ui->parameterSaveAsLineEdit->text();
}
