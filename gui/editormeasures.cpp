#include "editormeasures.h"
#include "ui_editormeasures.h"

#include <QtCore>
#include <QtGui>
#include "delegates/delegates.h"
#include <float.h>
#include "dialogs/dialogs.h"
#include "gui_func.h"

EditorMeasures::EditorMeasures(QString name,QString type, ManagerMeasures *manager,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorMeasures){

    ui->setupUi(this);

    setName(name);
    setType(type);
    setManager(manager);

    id_ = -1;
    initialize();

    // plots
    loadInfo();


}

EditorMeasures::EditorMeasures(int measure_id,ManagerMeasures *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorMeasures)
{
    ui->setupUi(this);
    setManager(manager);
    Open(measure_id);

    initialize();
    updateMeasures();
    loadInfo();



    qDebug() << managerMeasures->device()->columnTitles(plot_type());
    replotGraphics();
}

void EditorMeasures::setManager(ManagerMeasures* manager){
    managerMeasures = manager;
}

bool EditorMeasures::Open(int measure_id)
{
    id_ = measure_id;

    TMeasure *measure = managerMeasures->openMeasure(id_);
    setName( measure->name()     );
    setType( measure->plotType() );
    measures_ = measure->measures( managerMeasures->device()->columnTitles(plot_type()) );

    created_ = measure->created();
    changed_ = measure->changed();
    author  = measure->author();
    mSettingMap = measure->settingMap();

    isSelectedConstant_ = false;

    delete measure;
    return true;
}

void EditorMeasures::setName(QString name)
{
    name_ = name;

    setWindowTitle(name + trUtf8(" - ") + trUtf8("Редактор измерений"));
}

void EditorMeasures::setType(QString type)
{
    type_ = type;
}

EditorMeasures::~EditorMeasures()
{
    delete ui;
}

void EditorMeasures::clickAddColumn(){

    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblMeasures->model());

    QStringList _labels;
    for(int col=0; col < model->columnCount();col++){
        _labels << model->headerData(col,Qt::Horizontal).toString();
    }


    QStringList _items = managerMeasures->getColumnsName( _labels );

    bool ok;
    QString _column = QInputDialog::getItem(this,trUtf8("Добавить колонку"),trUtf8("Название"),_items,0,false,&ok);

    if(_column.isEmpty() || !ok){
        return;
    }


    int col = model->columnCount();
    QList<QStandardItem *> emp;
    for(int i=0; i < model->rowCount();i++){
        emp << new QStandardItem("");
    }

    model->appendColumn(emp);
    model->setHeaderData(col,Qt::Horizontal,_column);
    //    model->horizontalHeaderItem(col)->setData(_column);
}

void EditorMeasures::clickAddRow()
{
    if(!isSelectedConstant_){
        messageWarning("Выберите константу из левого списка");
        return;
    }
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblMeasures->model());

    QList<QStandardItem *> _row;
    _row << new QStandardItem("1");
    for(int i=1; i < model->columnCount(); i++){
        _row << new QStandardItem("");
    }

    model->appendRow(_row);
}

void EditorMeasures::changeDataMeasure(QModelIndex i1, QModelIndex i2){
    mMeasuresChanged = true;
    replotGraphics();

    return;

}

void EditorMeasures::changeDataConstant(QStandardItem *item)
{
    if(item->column() != 0){
        return;
    }
    QStandardItemModel * model = static_cast<QStandardItemModel *>(ui->tblConstants->model());

    int id = item->row();


    bool inc_db = false;

    if(model->item(id,0)->data(Qt::DisplayRole).toBool()){
        inc_db = true;
    }

    measures_[id].inc = inc_db;

    mMeasuresChanged = true;

    replotGraphics();
    return;
}



void EditorMeasures::replotGraphics()
{
    QStandardItemModel *model = dynamic_cast<QStandardItemModel *>(ui->tblMeasures->model());
    QMap<QString,double> values;

    QStringList _labels;
    _labels = managerMeasures->device()->columnTitles( plot_type() );
    if(measures_.count() == 0 || _labels.count() == 0){
        return;
    }
    int _count_db = measures_.count();

    saveCurrentDB();

    for(int tab_index=0; tab_index < ui->tabGraphics->count(); tab_index++){
        QString _name = ui->tabGraphics->tabText( tab_index );
        QCustomPlot *plot = static_cast<QCustomPlot *>(ui->tabGraphics->widget(tab_index));
        plot->clearGraphs();

        QCPItemText *label = new QCPItemText( plot );
        plot->addItem( label );
        label->setPositionAlignment(Qt::AlignHCenter);
        label->position->setType(QCPItemPosition::ptAxisRectRatio);
        label->position->setCoords(0.5, 0); // place position at center/top of axis rect
        label->setText("");
        label->setFont(QFont(font().family(), 14));
        QVector<double> axisX,axisY;

        for(int _db_i=0; _db_i < _count_db;_db_i++){
            axisX.clear(); axisY.clear();
            MEASURE_DB _db = measures_.at(_db_i);

            if(!_db.inc){
                continue;
            }

            int _db_rows = _db.table.count();

            for(int _db_row=0; _db_row < _db_rows; _db_row++){
                MEASURE_ROW _row = _db.table.at(_db_row);
                if(_row.inc){
                    values.clear();
                    int _items = _row.row.count();


                    for(int _item=0; _item < _items; _item++ ){
                        values.insert( _labels.at(_item), _row.row.at(_item));
                    }

                    QPointF point = managerMeasures->device()->computeValue(_name, values);

                    axisX.append( point.x() );
                    axisY.append( point.y() );

                }

            }



            QCPGraph *_graphic = plot->addGraph();
            QStringList _constList;

            foreach(QString _const,_db.constants.keys()){
                _constList << QString("%1=%2").arg(_const).arg(_db.constants.value(_const));
            }
            _graphic->setProperty("const", _constList.join(",") );

            _graphic->addData(axisX,axisY);



        }
        plot->rescaleAxes();
        plot->yAxis->setRangeUpper(plot->yAxis->range().upper + plot->yAxis->range().upper/5.0);
        plot->replot();
    }


}

void EditorMeasures::clickAddConstValue()
{
    QStringList _constant_names = managerMeasures->device()->constantTitles(plot_type());
    QStandardItemModel *model = static_cast< QStandardItemModel *>(ui->tblConstants->model());


    if(_constant_names.count() == 1){

        bool ok;
        QString _value = QInputDialog::getText(this,trUtf8("Добавить константу"),_constant_names.at(0),QLineEdit::Normal,QString(""),&ok);

        if(!ok || _value.isEmpty()){
            return;
        }

        // replace m->1e-3, u->1e-6
        double value = _value.toDouble(&ok);
        if(!ok){
            QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Неправильно введено значение"));
            return;
        }



        MEASURE_DB db;
        db.inc = true;
        db.constants.insert( _constant_names.at(0),value );

        db.columns.append( managerMeasures->device()->columnTitles(plot_type()) );

        measures_.append( db );


        QList<QStandardItem *> _rowConstant;

        _rowConstant << new QStandardItem("1") << new QStandardItem(  QString("%1=%2").arg(_constant_names.at(0)).arg(value) );

        model->appendRow(_rowConstant);

        selectConstValue( model->index( model->rowCount()-1,1)  );

    }else if(_constant_names.count() == 2){
        // ----
        DialogAddConstant _addConstantDialog;

        _addConstantDialog.setLabels( _constant_names.at(0), _constant_names.at(1) );
        _addConstantDialog.setModal( true );

        if(_addConstantDialog.exec() == QDialog::Accepted){

            MEASURE_DB db;
            db.inc = true;

            db.constants.insert( _constant_names.at(0), _addConstantDialog.value( 1 )  );
            db.constants.insert( _constant_names.at(1), _addConstantDialog.value( 2 )  );



            db.columns.append( managerMeasures->device()->columnTitles(plot_type()) );

            measures_.append( db );


            QList<QStandardItem *> _rowConstant;

            _rowConstant << new QStandardItem("1")
                         << new QStandardItem(  QString("%1=%2,%3=%4").arg(_constant_names.at(0)).arg(_addConstantDialog.value( 1 ) )
                                                .arg(_constant_names.at(1)).arg(_addConstantDialog.value( 2 ) ));


            model->appendRow(_rowConstant);


            selectConstValue( model->index( model->rowCount()-1,1)  );


        }

        _addConstantDialog.close();

    }
}

void EditorMeasures::saveMeasure()
{
    //    manager
    QMap<QString,QVariant> _info;

    // #TODO
    _info.insert( "id", id_ );
    _info.insert("name",name());
    _info.insert("author", "Malyugin Platon");
    _info.insert("type", plot_type());

    QString _settings;

    if(managerMeasures->device()->type() == DEVICE_MOSFET){
        QStringList _list;
        bool ok;
        double _temp = info("channel_l").toDouble(&ok);
        if(!ok){
            qDebug() << "Error length channel value";
            return;
        }
        _list <<  QString("%1=%2").arg("L").arg(_temp);

        _temp = info("channel_w").toDouble(&ok);
        if(!ok){
            qDebug() << "Error length channel value";
            return;
        }
        _list <<  QString("%1=%2").arg("W").arg(_temp);

        _settings = _list.join(";");
    }

    _info.insert("settings",_settings);

    if(managerMeasures->saveMeasure( _info,measures() )){
        id_ = managerMeasures->measure_id();
    }

    mMeasuresChanged = false;
    emit changeMeasures();

    return;

}

void EditorMeasures::changePlotType(QString name)
{
    ui->tabGraphics->clear();
    QCustomPlot *plot = new QCustomPlot(ui->tabGraphics);
    plot->setAutoAddPlottableToLegend(true);
    plot->setAutoMargin(true);

    ui->tabGraphics->addTab(plot,name);
}

void EditorMeasures::selectConstValue(QModelIndex index)
{

    if(index.column() != 1){
        return;
    }

    QString _constant = index.data().toString();

    ui->tblMeasures->setCurrentIndex( index );

    saveCurrentDB();


    int id = findDB(_constant);

    if(id == -1){
        isSelectedConstant_ = false;
        return;
    }

    isSelectedConstant_ = true;

    ui->tblMeasures->setEnabled( true );

    mCurrentMeasure = id;

    MEASURE_DB _db = measures_.at(id);


    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblMeasures->model());

    int _column_count = model->columnCount();
    ui->tblMeasures->model()->removeRows(0,ui->tblMeasures->model()->rowCount());

    if(_db.table.count() > 0){
        int _row_count = _db.table.count();
        QList <QStandardItem *> _row_table;
        for(int row=0; row < _row_count; row++){

            if(_db.table[row].row.count()+1 != _column_count){
                qDebug() << "Column table and column measure diffrent";
                continue;
            }

            _row_table.clear();


            if(_db.table[row].inc){
                _row_table.append( new QStandardItem("1") );
            }else{
                _row_table.append( new QStandardItem("0") );
            }


            //            QStringList _columns = managerMeasures->device()->columnTitles( plot_type() );

            //            foreach(QString _column, _columns){

            //                int _index_column = _db.columns.indexOf( _column );
            //                if( _index_column == -1){
            //                    _row_table.append( new QStandardItem( "0.0" ));
            //                }else{
            //                    _row_table.append( new QStandardItem( QString::number(_db.table[row].row[_index_column] )) );
            //                }

            //            }

            for(int col=1; col < _column_count; col++){


                _row_table.append( new QStandardItem( QString::number(_db.table[row].row[col-1] )) );
            }


            model->appendRow( _row_table );
        }

    }

    return;

}

void EditorMeasures::importMeasures(){

    QString _file_path = QFileDialog::getOpenFileName(this,trUtf8("Импорт измерения"),QDir::currentPath(),trUtf8("Измерения (*.txt *.dat)"));

    if(QFile::exists(_file_path)){
        TMeasure *measure = new TMeasure();
        if(!measure->import(_file_path)){
            QMessageBox::warning(this,trUtf8("Achtung"),trUtf8("Achtung"));
            return;
        }

        measures_ = measure->measures( managerMeasures->device()->columnTitles(plot_type()));
        author = measure->author();
        created_ = measure->created();
        changed_ = measure->created();

        setInfo( "author", author );
        setInfo( "created", measure->createdDate() );


        delete measure;


        updateMeasures();
        replotGraphics();
    }

}

void EditorMeasures::closeEditor(){
    delete managerMeasures;
    measures_.clear();
    emit close();
}

void EditorMeasures::copyToClipboard()
{
    QString cbStr;
    QClipboard *cb = QApplication::clipboard();
    QModelIndexList list =   ui->tblMeasures->selectionModel()->selectedIndexes();
    int i, j, firstRow, lastRow, rowCount;

    if( list.isEmpty() ) return;

    firstRow = list.first().row();  lastRow = list.last().row();
    rowCount = lastRow - firstRow + 1;

    for(i = 0; i < rowCount; ++i, cbStr += '\n')
        for(j = i; j < list.count(); j += rowCount, cbStr += '\t')
            cbStr += ui->tblMeasures->model()->data(list[ j ], Qt::EditRole).toString();

    cb->setText(cbStr);
}

void EditorMeasures::clickPlotter(QMouseEvent *event)
{

    ViewerPlot plot(this);


    QCustomPlot *_plot = static_cast<QCustomPlot *>(ui->tabGraphics->widget( ui->tabGraphics->currentIndex() ));
    plot.setPlot( _plot );
    plot.exec();
    plot.close();

}

void EditorMeasures::plottableClick(QCPAbstractPlottable *plot, QMouseEvent *mouse){

    QCustomPlot *_plot = static_cast<QCustomPlot *>(ui->tabGraphics->widget( 0  ));

    QCPItemText *label = static_cast<QCPItemText *>(_plot->item(0));
    QCPGraph *_graph = static_cast<QCPGraph *>(plot);





    label->setText( _graph->property("const").toString());


    if(mouse->button() == Qt::RightButton){

//        qDebug() << ;


        QMenu *menu = new QMenu(_plot);

        (menu->addAction( trUtf8("Отключить") ))->setData( 0 );
        (menu->addAction( trUtf8("Открыть") ))->setData( 1 );
//        (menu->addAction( trUtf8("Удалить") ))->setData( 2 );


        QStandardItem *item;
        QModelIndex index;
        if( QAction *action = menu->exec( mouse->globalPos() )){

            switch(action->data().toInt()){
            case 0:
                item = findItemCheckFromConstants( _graph->property("const").toString() );
                item->setData( "0", Qt::DisplayRole );
                label->setText( "" );
                changeDataConstant( item );

                break;
            case 1:
                selectConstValue(findItemFromConstants( _graph->property("const").toString() ));
                break;
            case 2:
                break;

            }

        }


    }else if(mouse->button() == Qt::LeftButton){
        if(lastClickGraph_ == _graph){
            selectConstValue(findItemFromConstants( _graph->property("const").toString() ));

        }else{
            lastClickGraph_ = _graph;
        }


    }


}

double EditorMeasures::min(QVector<double> vect)
{

    double min = FLT_MAX;
    for(int i=0; i < vect.count();i++){
        if(min > vect[i]){
            min = vect[i];
        }
    }
    return min;
}

double EditorMeasures::max(QVector<double> vect)
{
    double max = -FLT_MAX;

    for(int i=0; i < vect.count();i++){
        if(max < vect[i]){
            max = vect[i];
        }
    }

    return max;
}

QList<MEASURE_DB> EditorMeasures::measures()
{
    return measures_;
}

int EditorMeasures::findDB(QString constantString ) {
    int count_db = measures_.count();
    int countConstant = constantString.split(",").count();
    QMap<QString,double> constants;

    foreach(QString temp, constantString.split(",")){
        bool ok;
        QString name = temp.split("=").at(0);
        double value = temp.split("=").at(1).toDouble(&ok);
        if(ok){
            constants.insert(name,value);
        }

    }

    for(int i=0; i<count_db;i++){
        int countFound = 0;
        MEASURE_DB _db = measures_.at( i );
        foreach(QString _const, _db.constants.keys()){
            if(constants.value(_const) !=  _db.constants.value(_const)){
                break;
            }
            countFound++;
        }
        if( countFound == countConstant ){
            return i;
        }


    }

    return -1;

}

bool EditorMeasures::saveCurrentDB()
{


    if(mCurrentMeasure == -1){
        return true;
    }


    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblMeasures->model());

    int _row_count = model->rowCount(),
            _column_count = model->columnCount();

    MEASURE_DB _db = measures_.at(mCurrentMeasure);

    _db.table.clear();

    for(int row=0; row < _row_count;row++){
        QList<QStandardItem *> _rowItems;

        for(int col=0; col < _column_count; col++){
            _rowItems << model->item(row,col);
        }
        MEASURE_ROW _row;

        if(_rowItems.count() < 2){
            continue;
        }

        if(_rowItems[0]->data( Qt::DisplayRole ).toBool()){
            _row.inc = true;
        }else{
            _row.inc = false;
        }

        bool ok;
        double value;
        for(int col=1; col < _column_count; col++){
            value = _rowItems[col]->data(  Qt::DisplayRole ).toDouble(&ok);
            if(!ok){
                // #TODO set NaN
                value = 0.0;
            }
            _row.row.append( value );

        }

        _db.table.append( _row );


    }

    measures_[mCurrentMeasure] = _db;


    return true;
}

void EditorMeasures::initialize()
{
    isSelectedConstant_ = false;
    mCurrentMeasure = -1;

    QStandardItemModel *modelMeasures = new QStandardItemModel(ui->tblMeasures),
            *modelInfo = new QStandardItemModel(ui->tblInfo),
            *modelConstants = new QStandardItemModel(ui->tblConstants);

    ui->tblMeasures->setModel( modelMeasures );
    ui->tblInfo->setModel( modelInfo );
    ui->tblConstants->setModel( modelConstants );
    ui->tblConstants->setEditTriggers( QAbstractItemView::NoEditTriggers );

    //TEST CASE
    QStringList labelsMeasures,labelsInfo,labelsConstant;
    labelsConstant << "#" << trUtf8("Значение");

    modelConstants->setHorizontalHeaderLabels( labelsConstant );


    labelsMeasures << "#";
    labelsMeasures.append( managerMeasures->device()->columnTitles(plot_type()) );

    labelsInfo << trUtf8("Название") << trUtf8("Значение");
    ui->tblInfo->setItemDelegateForColumn(0, new DelegateReadOnly(ui->tblInfo) );

    modelMeasures->setHorizontalHeaderLabels( labelsMeasures );
    modelInfo->setHorizontalHeaderLabels( labelsInfo );


    mMeasuresChanged = false;

    ui->tblInfo->setItemDelegateForRow( 2, new DelegateInfoCheckBox(ui->tblInfo) );
    ui->tblInfo->setItemDelegateForRow( 1, new DelegateInfoDate(ui->tblInfo) );

    ui->tblMeasures->setItemDelegateForColumn(0, new DelegateCheckBox(ui->tblMeasures) );
    ui->tblConstants->setItemDelegateForColumn(0, new DelegateCheckBox(ui->tblConstants));
    ui->tblMeasures->setColumnWidth(0,30);
    ui->tblConstants->setColumnWidth(0,30);


    ui->tabGraphics->clear();

    QCustomPlot *_plotter = new QCustomPlot(ui->tabGraphics);
    _plotter->xAxis->setLabel( managerMeasures->device()->plot(plot_type()).axis_x );
    _plotter->yAxis->setLabel( managerMeasures->device()->plot(plot_type()).axis_y );

    _plotter->xAxis->setRange(0,5);
    _plotter->yAxis->setRange(0,5);

    _plotter->replot();

    _plotter->setInteraction( QCustomPlot::iSelectPlottables );
    connect(_plotter,SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)),this,SLOT(plottableClick(QCPAbstractPlottable*,QMouseEvent*)));


    ui->tabGraphics->addTab( _plotter, plot_type() );
    //    connect(_plotter,SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(clickPlotter(QMouseEvent*)));




    connect(ui->btnRefresh,SIGNAL(clicked()),this,SLOT(replotGraphics()));


    //    connect(ui->actionAddColumn,SIGNAL(triggered()),this,SLOT(clickAddColumn()));
    //    connect(ui->btnAddColumn,SIGNAL(clicked()),this,SLOT(clickAddColumn()));
    connect(ui->btnAddRow,SIGNAL(clicked()),this,SLOT(clickAddRow()));
    connect(ui->actionAddRow,SIGNAL(triggered()),this,SLOT(clickAddRow()));

    connect(ui->tblMeasures->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(changeDataMeasure(QModelIndex,QModelIndex)));
    //    connect(ui->boxPlot,SIGNAL(currentIndexChanged(QString)),this,SLOT(changePlotType(QString)));
    connect(ui->btnAddConst,SIGNAL(clicked()),this,SLOT(clickAddConstValue()));

    connect(ui->tblConstants,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(selectConstValue(QModelIndex)));
    connect(modelConstants,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(changeDataConstant(QStandardItem*)));
    connect(ui->btnSave,SIGNAL(clicked()),this,SLOT(saveMeasure()));
    connect(ui->btnClose,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->actionImport,SIGNAL(triggered()),this,SLOT(importMeasures()));

    connect(ui->actionCopyToClipboard,SIGNAL(triggered()),this,SLOT(copyToClipboard()));

}

void EditorMeasures::setInfo(QString type, QVariant value){
    type = type.toLower();
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblInfo->model());

    int rows = model->rowCount();
    for(int row =0; row < rows; row++){
        if(model->data( model->index(row,0), Qt::UserRole ).toString().compare( type ) == 0){
            model->setItem( row,1,new QStandardItem(value.toString()) );
            break;
        }

    }



//    if(type == "author"){
//        model->setItem( 0,1,new QStandardItem(value.toString()) );
//    }else if(type == "created"){
//        QStandardItem *item = new QStandardItem();
//        item->setData( value, Qt::DisplayRole );
//        model->setItem( 1,1, item );
//        qDebug() << value.toDate().toString("dd.MM.yyyy");
//        ui->tblInfo->repaint();
    //    }
}

QVariant EditorMeasures::info(QString name){
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblInfo->model());
    QVariant var;
    int rows = model->rowCount();
    for(int row =0; row < rows; row++){
//        qDebug() << model->data( model->index(row,0), Qt::UserRole ).toString();
        if(model->data( model->index(row,0), Qt::UserRole ).toString().compare( name, Qt::CaseInsensitive ) == 0){

            var = model->data( model->index(row,1), Qt::DisplayRole);
            break;
        }

    }
    return var;
}

void EditorMeasures::updateMeasures()
{
    //Refresh list constants;


    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblConstants->model());
    model->removeRows(0,model->rowCount());
    int _constant_count = measures_.count();
    QStringList _values;
    for(int i=0; i < _constant_count;i++){
        MEASURE_DB _db  = measures_.at(i);
        _values.clear();
        foreach(QString _const,_db.constants.keys()){
            _values << QString("%1=%2").arg(_const).arg(_db.constants.value(_const));
        }

        QList<QStandardItem *> row;
        if(_db.inc){
            row << new QStandardItem("1");
        }else{
            row << new QStandardItem("0");
        }

        row << new QStandardItem(_values.join(","));

        model->appendRow( row );


    }

    model = static_cast<QStandardItemModel *>(ui->tblMeasures->model());
    model->removeRows(0,model->rowCount());

    ui->tblMeasures->setEnabled(false);
    mCurrentMeasure = -1;
    mMeasuresChanged = true;

}

QStandardItem *EditorMeasures::findItemCheckFromConstants(QString _constant){
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblConstants->model());

    int count_row = model->rowCount();
    QModelIndex index;
    for(int row=0; row < count_row; row++){
        index =  model->index( row, 1 );
        if(model->data( index ).toString().compare( _constant, Qt::CaseInsensitive ) == 0)
        {
            break;
        }
    }

    return model->item( index.row(), 0 );
}

QModelIndex EditorMeasures::findItemFromConstants(QString _constant)
{
    QStandardItemModel *model = static_cast<QStandardItemModel *>(ui->tblConstants->model());

    int count_row = model->rowCount();
    QModelIndex index;
    for(int row=0; row < count_row; row++){
        index =  model->index( row, 1 );
        if(model->data( index ).toString().compare( _constant, Qt::CaseInsensitive ) == 0)
        {
            return index;
        }
    }

    return model->index(-1,-1);
}

//void EditorMeasures::closeEvent(QCloseEvent *event)
//{
//    if(event->type() == QEvent::Close){
//        saveMeasure();
//    }
////    if(mMeasuresChanged){
////        if(maybeSave()){
////            saveMeasure();
////        }
////    }
//}

bool EditorMeasures::maybeSave(){
    if(QMessageBox::warning(this,trUtf8("Сохранение"),trUtf8("Сохранить перед закрытием"),QMessageBox::Ok, QMessageBox::Cancel  ) == QMessageBox::Ok){
        return true;
    }
    return false;
}





void EditorMeasures::loadInfo(){
    QStandardItemModel *modelInfo = static_cast<QStandardItemModel *>(ui->tblInfo->model());
    modelInfo->insertRows(0,3);
    modelInfo->setItem(0,0, new QStandardItem(trUtf8("Автор")));
    modelInfo->setItem(0,1, new QStandardItem( author ));
    modelInfo->setData( modelInfo->index( 0,0 ), "author", Qt::UserRole );

    modelInfo->setItem(1,0, new QStandardItem(trUtf8("Дата")));
    modelInfo->setItem(1,1, new QStandardItem( created_ )  );
     modelInfo->setData( modelInfo->index( 1,0 ), "date", Qt::UserRole );

    modelInfo->setItem(2,0, new QStandardItem(trUtf8("Сомнительное")));




    if(managerMeasures->device()->type() == DEVICE_MOSFET){

        int _index_row = modelInfo->rowCount();

        QList<QStandardItem *> _items;
        _items << new QStandardItem("L") << new QStandardItem("");
        modelInfo->appendRow(_items);
        modelInfo->setData( modelInfo->index( _index_row,0 ), "channel_l", Qt::UserRole );
        if(id_ != -1){
            modelInfo->setData( modelInfo->index( _index_row,1), mSettingMap.value("L","0.0") , Qt::DisplayRole );
        }
        _index_row++;

        _items.clear();
        _items << new QStandardItem("W") << new QStandardItem("");
        modelInfo->appendRow(_items);
        modelInfo->setData( modelInfo->index( _index_row,0 ), "channel_w", Qt::UserRole );
        if(id_ != -1){
            modelInfo->setData( modelInfo->index( _index_row,1), mSettingMap.value("W","0.0") , Qt::DisplayRole );
        }


    }

}
