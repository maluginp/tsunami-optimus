#include "formsetting.h"
#include "ui_formsetting.h"

FormSetting::FormSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormSetting)
{
    ui->setupUi(this);

    ui->methodOptimisatonComboBox->clear();
    ui->methodOptimisatonComboBox->addItem( trUtf8("Хука-Дживса"), "HookeJeeves" );
    ui->methodOptimisatonComboBox->addItem( trUtf8("Квази-Ньютоновский"), "QuasiNewton" );
//    ui->methodOptimisatonComboBox->addItem( trUtf8("Сопряжённых градиентов"), "Gn" );


    openSetting();

    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveSetting()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}

FormSetting::~FormSetting()
{
    delete ui;
}

void FormSetting::saveSetting(){
    QString _dir;
#ifdef Q_OS_WIN
    _dir = QDir::currentPath()+"/";
#else
    _dir = "/Developer/Projects/tsunami-optimus/";
#endif

    QSettings options(_dir+"setting.ini", QSettings::IniFormat);

    options.beginGroup( "optimisation" );

    options.setValue( "method", ui->methodOptimisatonComboBox->itemData( ui->methodOptimisatonComboBox->currentIndex() ) );

    //type function error ( default = relative)
    if( ui->errorRelativeRadioButton->isChecked() ){
        options.setValue( "error", "relative" );
    }else{
        options.setValue( "error", "absolute" );
    }

    options.setValue( "error_eps", ui->errorEpsSpinBox->value() );
    options.setValue( "iteration", ui->iterationCountSpinBox->value() );
    if(ui->reportSaveCheckBox->isChecked()){
        options.setValue( "report_enable", true );
        options.setValue( "report_format", "html" ); // default
    }else{
        options.setValue( "report_enable", false );
        options.setValue( "report_format", "" );
    }



    options.endGroup();


    accept();

}

void FormSetting::openSetting(){
    QString _dir;
#ifdef Q_OS_WIN
    _dir = QDir::currentPath()+"/";
#else
    _dir = "/Developer/Projects/tsunami-optimus/";
#endif

    QSettings options(_dir+"setting.ini", QSettings::IniFormat);

    options.beginGroup( "optimisation" );

    int index =0;

    index = ui->methodOptimisatonComboBox->findData(options.value( "method", "QuasiNewton" ));
    ui->methodOptimisatonComboBox->setCurrentIndex( index );

    if(options.value("error","relative").toString().compare( "absolute", Qt::CaseInsensitive) == 0){
        ui->errorAbsoluteRadioButton->setChecked(true);
    }else{
        ui->errorRelativeRadioButton->setChecked(true);
    }

    ui->errorEpsSpinBox->setValue( options.value("error_eps").toInt() );
    ui->iterationCountSpinBox->setValue( options.value("iteration").toInt() );

    if(options.value("report_enable").toBool()){
        ui->reportSaveCheckBox->setChecked( true );

        QString _format = options.value("report_format").toString().toLower();

        if( _format.isEmpty() || _format == "html" ){
            ui->reportFormatHtmlRadioButton->setChecked(true);
        }else if(_format == "text"){
            ui->reportFormatTextRadioButton->setChecked(true);
        }else if(_format == "xml"){
            ui->reportFormatXmlRadionButton->setChecked(true);
        }

    }else{
        ui->reportSaveCheckBox->setChecked( false );
    }

    options.endGroup();
}
