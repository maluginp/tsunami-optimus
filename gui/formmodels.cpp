#include "formmodels.h"
#include "ui_formmodels.h"

#include "delegates/delegates.h"
#include "core/tdblayer.h"

FormModels::FormModels(QString device_type, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormModels)
{
    ui->setupUi(this);

    setDevice( device_type );

    ui->tblInfo->setItemDelegateForColumn(0,new DelegateReadOnly());


     QStringListModel *modelListModels = new QStringListModel(ui->listModels);


     ui->listModels->setModel( modelListModels );


     QStandardItemModel *model = new QStandardItemModel(ui->tblInfo);

     ui->tblInfo->setModel( model );


     // Test case
     updateListModels();

     connect(ui->btnAccept,SIGNAL(clicked()),this,SLOT(clickAccept()));
     connect(ui->lnModelsFIlter,SIGNAL(textEdited(QString)),this,SLOT(applyFilter(QString)));
     connect(ui->listModels,SIGNAL(activated(QModelIndex)),this,SLOT(changeIndexListModels(QModelIndex)));
}


FormModels::~FormModels(){
    delete ui;
}

void FormModels::setDevice(QString name_device)
{
    mDevice = name_device;
}

int FormModels::id()
{
//    QStringListModel *model = static_cast<QStringListModel *>(ui->listModels->model());

    QString _name = ui->listModels->currentIndex().data().toString();

    int id = -1;

    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT id FROM models WHERE name=:name")
            ->bindValue(":name",_name)
            ->exec();

    if(dbLayer->isNext()){
        bool ok;
        id = dbLayer->value("id").toInt(&ok);
        if(!ok){
            id=-1;
        }
    }

    delete dbLayer;
    return id;

}

void FormModels::updateListModels(){
    // Test case
    QStringList models;

    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT name FROM models WHERE device=:dev")
            ->bindValue(":dev",mDevice)
            ->exec();
    while(dbLayer->isNext()){
        models.append( dbLayer->value("name").toString() );
    }


    QStringListModel *modelListModels = static_cast<QStringListModel *>(ui->listModels->model());

    modelListModels->setStringList( models );

    delete dbLayer;

    return;
}

void FormModels::applyFilter(QString name){

    QStringListModel *modelListModels = static_cast<QStringListModel *>(ui->listModels->model());
    QRegExp regExp( name+".*", Qt::CaseInsensitive );
    int index = modelListModels->stringList().indexOf( regExp );
    QModelIndex modelIndex = modelListModels->index(index);


    ui->listModels->setCurrentIndex( modelIndex );
}

void FormModels::changeIndexListModels(QModelIndex index){

    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblInfo->model());
    QString _name = index.data().toString();

    model->clear();

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT * FROM models WHERE name=:name")
            ->bindValue(":name",_name)
            ->exec();
    if(dbLayer->isNext()){

        model->appendRow( rowInfo( trUtf8("Название"),  dbLayer->value("name").toString() ));
        model->appendRow( rowInfo( trUtf8("Автор"), dbLayer->value("author").toString()) );
        model->appendRow( rowInfo( trUtf8("Создана"), dbLayer->value("created").toDate().toString("dd.MM.yyyy") ));
        model->appendRow( rowInfo( trUtf8("Изменено"), dbLayer->value("changed").toDate().toString("dd.MM.yyyy") ));

        bool user_defined;

        user_defined = dbLayer->value("user_defined").toBool();
        if(user_defined){
            model->appendRow( rowInfo( trUtf8("Внутренняя"),trUtf8("Нет") ) );
             model->appendRow( rowInfo( trUtf8("Путь"), dbLayer->value("path").toString()) );
        }else{
            model->appendRow( rowInfo( trUtf8("Внутренняя"),trUtf8("Да") ) );
        }

    }
    delete dbLayer;

}

void FormModels::clickAccept()
{
    int _id = id();

    if(_id != -1){
        emit acceptModel(_id);
    }

    close();
}

QList<QStandardItem *> FormModels::rowInfo(QString name, QString value)
{
    QList<QStandardItem *> row;

    row.append( new QStandardItem( name ) );
    row.append( new QStandardItem( value ) );

    return row;
}
