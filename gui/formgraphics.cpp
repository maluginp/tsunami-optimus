#include "formgraphics.h"
#include "ui_formgraphics.h"

FormGraphics::FormGraphics(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormGraphics)
{
    ui->setupUi(this);
}

FormGraphics::~FormGraphics()
{
    delete ui;
}
