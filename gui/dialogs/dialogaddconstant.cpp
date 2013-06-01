#include "dialogaddconstant.h"
#include "ui_dialogaddconstant.h"

DialogAddConstant::DialogAddConstant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddConstant)
{
    ui->setupUi(this);
    connect( ui->addButton, SIGNAL(clicked()), this, SLOT(accept()) );
}

DialogAddConstant::~DialogAddConstant()
{
    delete ui;
}

void DialogAddConstant::setLabels(QString const1, QString const2){

    ui->const1Label->setText( const1 );
    ui->const2Label->setText( const2 );
}

double DialogAddConstant::value(int constNo){
    double _value = 0.0;
    bool ok;
    if(constNo == 1){
        _value = ui->const1LineEdit->text().toDouble(&ok);
    }else if(constNo == 2){
        _value = ui->const2LineEdit->text().toDouble(&ok);
    }
    return _value;

}
