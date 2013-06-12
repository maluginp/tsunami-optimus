#include "tmeasure.h"
#include "core/tdblayer.h"
#include "defines.h"
#include <QtXml>

TMeasure::TMeasure()
{
    id_ = -1;
    datasetId_ = -1;

}

TMeasure::TMeasure(int _id)
{
    id_ = _id;

    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT dataset_id FROM measures WHERE id=:id")
            ->bindValue(":id",id())
            ->exec();

    if(!dbLayer->isNext()){
        id_ = -1;
        datasetId_ = -1;
    }
    bool ok;
    datasetId_ = dbLayer->value("dataset_id").toInt(&ok);

    if(!ok){
        datasetId_ = -1;
    }

    delete dbLayer;
}

TMeasure::TMeasure(int dataset_id, QString name)
{
    datasetId_ = dataset_id;
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT id FROM measures WHERE dataset_id=:dataset_id AND name=:name")
            ->bindValue(":dataset_id",dataset_id)
            ->bindValue(":name",name)
            ->exec();
    if(!dbLayer->isNext()){
        id_ = -1;
        datasetId_ = -1;
    }
    bool ok;
    id_ = dbLayer->value("id").toInt(&ok);
    if(!ok){
        id_ = -1;
        datasetId_ = -1;
    }
    delete dbLayer;


}

TMeasure::~TMeasure()
{
    databases_.clear();
}

// #TODO: remake
bool TMeasure::Open(){

    QList<MEASURE_DB> _measures;

    TDBLayer *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT * FROM measures WHERE id=:id")
            ->bindValue(":id",id())
            ->exec();


    if(!dbLayer->isNext()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return false;
    }

    datasetId_ = dbLayer->value("dataset_id").toInt();
    name_      = dbLayer->value("name").toString();
    author_    = dbLayer->value("author").toString();
    created_   = dbLayer->value("created").toDate();
    changed_   = dbLayer->value("changed").toDate();
    plotType_  = dbLayer->value("plot_type").toString();
    setSetting( dbLayer->value("settings").toString());

    QString data = dbLayer->value("data").toString();


//    qDebug() << data;

    QDomDocument xml_doc;
    xml_doc.setContent( data );

    QDomElement xml_measure = xml_doc.firstChildElement();


    QDomNodeList _cols = xml_measure.firstChildElement( "columns" ).elementsByTagName("column");
    QStringList columns;
    for(int i=0; i < _cols.count(); i++){
        QDomElement column = _cols.at(i).toElement();
        columns.append( column.attribute( "name" ) );
    }

    databases_.clear();


    QDomNodeList xml_bases = xml_measure.elementsByTagName("db");
    for(int i=0; i < xml_bases.count(); i++){
        QDomElement xml_base = xml_bases.at(i).toElement();

        MEASURE_DB _db;

        _db.inc = static_cast<bool>(xml_base.attribute("inc","1").toInt());
        _db.columns = columns;

        // Add constants
        QDomNodeList constants = xml_bases.at(i).toElement().elementsByTagName("constant");
        for(int j=0;j < constants.count(); j++){
            QDomElement constant = constants.at(j).toElement();
            _db.constants.insert( constant.attribute("name"),constant.attribute("value").toDouble() );
        }



        QDomNodeList items = xml_base.elementsByTagName("items");

        for(int j=0;j < items.count(); j++){


            MEASURE_ROW _row;

            _row.inc = static_cast<bool>(items.at(j).toElement().attribute("inc","1").toInt());

            QDomNodeList _items = items.at(j).toElement().elementsByTagName("item");
            QList<double> row;
            for(int k=0; k < _items.count(); k++){
                QDomElement item = _items.at(k).toElement();
                row.append( item.attribute("value").toDouble() );
            }

            _row.row = row;

            _db.table.append( _row );

        }

        databases_.append( _db );
    }

    xml_doc.clear();

    delete dbLayer;
    return true;
}


bool TMeasure::Save(){

    TDBLayer *dbLayer = TDBLayer::getInstance();

    QDate _changed = QDate::currentDate();

    // Create xml code
    QString data_xml;
    data_xml = "<measures><columns>";
    foreach(QString _column,  databases_.at(0).columns){
        data_xml += QString("<column name=\"%1\"/>").arg(_column);
    }
    data_xml += "</columns>";
    data_xml += stringDBs();
    data_xml += "</measures>";


    if(id() > 0){
        // Update
        bool res = dbLayer->bindQuery( "UPDATE measures SET dataset_id=:dset_id, name=:name, author=:author, "
                                       "changed=:changed, data=:data, settings=:settings WHERE id=:id" )
                ->bindValue( ":dset_id", datasetId_ )
                ->bindValue(":name",name_)
                ->bindValue(":author", author_)
                ->bindValue(":changed",_changed)
                ->bindValue(":data",data_xml)
                ->bindValue(":id",id())
                ->bindValue(":settings",setting())
                ->exec();
        if(!res){
            qDebug() << dbLayer->getError();
            delete dbLayer;
            return false;
        }
        delete dbLayer;
        return true;

    }else{

        bool res = dbLayer->bindQuery( "INSERT INTO measures(dataset_id,name,author,plot_type,created,changed,data,settings) "
                                       "VALUES(:dset_id,:name,:author, :plot_type ,:created,:changed,:data,:settings)")
                ->bindValue( ":dset_id", datasetId_ )
                ->bindValue(":name",name_)
                ->bindValue(":author", author_)
                ->bindValue(":created",QDate::currentDate())
                ->bindValue(":changed",QDate::currentDate())
                ->bindValue(":plot_type",plotType())
                ->bindValue(":data",data_xml)
                ->bindValue(":settings",setting())
                ->exec();
        if(!res){
            qDebug() << dbLayer->getError();
            delete dbLayer;
            return false;
        }

        id_ = dbLayer->getInsertID();
        delete dbLayer;
        return true;
    }
    delete dbLayer;
    return false;

}

bool TMeasure::Delete()
{
    TDBLayer *dbLayer = TDBLayer::getInstance();
    bool res = false;
    if(id() != -1){
        res = dbLayer->bindQuery("DELETE FROM measures WHERE id=:id")
                ->bindValue(":id",id())
                ->exec();
    }

    delete dbLayer;
    return res;
}

bool TMeasure::Delete(int id)
{
    TDBLayer *dbLayer = TDBLayer::getInstance();
    bool res = false;
    if(id != -1){
        res = dbLayer->bindQuery("DELETE FROM measures WHERE id=:id")
                ->bindValue(":id",id)
                ->exec();
    }

    delete dbLayer;
    return res;
}

QList<MEASURE_DB> TMeasure::measures(QStringList filterColumns)
{

    QList<MEASURE_DB> _new_dbs;


    foreach(MEASURE_DB _db, databases_){
        MEASURE_DB _new_db = _db;

        _new_db.table.clear();
        foreach( MEASURE_ROW _db_row, _db.table ){
            MEASURE_ROW _new_db_row = _db_row;
            _new_db_row.row.clear();
            foreach(QString _filter,filterColumns){
                int _index = _db.columns.indexOf(_filter);
                if(_index == -1){
                    _new_db_row.row.append(0.0);
                    continue;
                }
                _new_db_row.row.append( _db_row.row.at( _db.columns.indexOf(_filter) )  );
            }
            _new_db.table.append( _new_db_row );
        }
        _new_db.columns = filterColumns;

        _new_dbs.append( _new_db );
    }

    return _new_dbs;
}


void TMeasure::addMeasureDB(MEASURE_DB db)
{
    databases_.append( db );
}

void TMeasure::setMeasureDB(QList<MEASURE_DB> dbs)
{
    databases_ = dbs;
}

void TMeasure::addMeasureDB(QList<MEASURE_DB> dbs)
{
    databases_.append( dbs );
}

QString TMeasure::stringDB(int id)
{

    MEASURE_DB _db = databases_.at(id);

    QDomDocument xml_doc;

    // <measure> ...... </measure>
    QDomElement xml_db = xml_doc.createElement( "db" );
    if(_db.inc){
        xml_db.setAttribute("inc",1);
    }else{
        xml_db.setAttribute("inc",0);
    }

    xml_doc.appendChild( xml_db );

    // <constant name="aa" value="1">
    foreach( QString _const, _db.constants.keys() ){
        QDomElement xml_const = xml_doc.createElement("constant");
        xml_const.setAttribute( "name", _const );
        xml_const.setAttribute("value",_db.constants.value(_const));
        xml_db.appendChild( xml_const );
    }

//    foreach( QString _step, _db.steps.keys() ){
//        QDomElement xml_step = xml_doc.createElement("step");
//        xml_step.setAttribute( "name",  _step );
//        xml_step.setAttribute( "start", _db.steps.value(_step).start);
//        xml_step.setAttribute( "end",   _db.steps.value(_step).end);
////        xml_step.setAttribute( "step",  _db.steps.value(_step).step);

//        xml_db.appendChild( xml_step );
//    }


    // <items> <item value=""> </items>

    int row_count = _db.table.count();
    int column_count = _db.table.at(0).row.count();

    for(int row=0; row < row_count; row++){
        QDomElement xml_items = xml_doc.createElement( "items" );
        xml_db.appendChild( xml_items );

        if(_db.table.at(row).inc){
            xml_items.setAttribute( "inc", 1 );
        }else{
            xml_items.setAttribute( "inc", 0 );
        }

        for(int col=0; col < column_count; col++){
            QDomElement xml_item = xml_doc.createElement( "item" );
            xml_item.setAttribute( "value", _db.table.at(row).row.at(col) );
            xml_items.appendChild(  xml_item );
        }

    }

    QString xml = xml_doc.toString(0);
    xml_doc.clear();
    return xml;
}

QString TMeasure::stringDBs()
{
    int db_count = databases_.count();
    QString _xml("");

    for(int id=0; id < db_count; id++){
        _xml += stringDB( id );
    }

    return _xml;

}

bool TMeasure::import(QString path){

    QFile file(path);

    if(!file.open(QIODevice::ReadOnly)){
        return false;
    }

    QStringList _lines;
    QString _line;
    char buf[1024];
    while(!file.atEnd()){
        qint64 _lineLength = file.readLine(buf,sizeof(buf));
        if(_lineLength > 0){
            _line = QString::fromAscii(buf).trimmed();
            _line = _line.replace("\r","");
            _line = _line.replace("\n","");
            if(!_line.isEmpty()){
                _lines << _line;
            }
        }
    }

    qDebug() << "Read lines: " << _lines.count();
    file.close();



    QString _author = importReadInfo(_lines,"author");
    QString _date   = importReadInfo(_lines,"date");
    created_  = QDate::fromString(_date,"dd.MM.yyyy");
    setAuthor( _author );

    databases_ = importReadDatabases( _lines );




    // _set;
    return true;

}

bool TMeasure::exists(){
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery( "SELECT 1  FROM measures WHERE dataset_id=:dset_id AND name=:name" )
            ->bindValue( ":dset_id", datasetId_ )
            ->bindValue(":name",name_)
            ->exec();

    if(!dbLayer->isRequested()){
        qDebug() << dbLayer->getError();
        return false;
    }

    bool res = dbLayer->isNext();

    delete dbLayer;
    return res;
}

int TMeasure::create(int datasetId, QString name,QString plotType){
    TDBLayer *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery( "INSERT INTO measures(dataset_id,name,plot_type) VALUES(:dataset_id,:name,:type)" )
            ->bindValue(":name",name)
            ->bindValue(":type",plotType)
            ->bindValue(":dataset_id",datasetId)
            ->exec();
    return dbLayer->getInsertID();
}



QString TMeasure::importReadInfo(QStringList text, QString info){

    QString _searchWord = info.toUpper(),
            _result("");
    bool _start_db = false;
    foreach( QString _line, text ){
        if(_start_db){
            if(_line.toUpper().startsWith("DB_END")){
                _start_db = false;

            }
            continue;
        }

        if(_line.toUpper().startsWith("DB_BEGIN")){
            _start_db = true;
            continue;
        }

        if(_line.toUpper().startsWith( _searchWord )){
            _result = _line.mid( _searchWord.count() ).simplified();
            break;
        }


    }

    return _result;

}

QList<MEASURE_DB> TMeasure::importReadDatabases(QStringList text){

    QList<MEASURE_DB> _dbs;
    bool _isLast = false;
    int  _curPos=0;
    while(!_isLast){
        MEASURE_DB _db = importReadDatabase(text,_curPos,_isLast);
        _dbs.append( _db );
    }

    return _dbs;

}

MEASURE_DB TMeasure::importReadDatabase(QStringList text, int &cur_pos,bool &last)
{
    last=false;

    MEASURE_DB _db;

    _db.inc = true;

    bool _start_db = false,
            ok;
    double _value;
    int _line_count = text.count();

    QMap< QString, QVector<double> > _step_values;

//    STEP_RANGE _step_range = {0.0,0.0,0.0};

    for(int _line_pos = cur_pos; _line_pos < _line_count; _line_pos++){
        QString _line = text.at(_line_pos);

        if(_start_db){
            if(_line.toUpper().startsWith("DB_END")){
                _start_db = false;
                cur_pos = _line_pos;
                if(_line_pos == _line_count-1){
                    last=true;
                }

//                foreach( QString _step_name, _step_values.keys()){

//                    if( _db.steps.contains(_step_name) ){

//                        _step_range =  _db.steps[_step_name];
//                        _step_range.start = min( _step_values[ _step_name ] );
//                        _step_range.end = max( _step_values[ _step_name ] );

//                        _db.steps[_step_name] = _step_range;
//                    }

//                }


//                _step_range.start =0.0;
//                _step_range.end = 0.0;
//                _step_range.step = 0.0;


//                _step_values.clear();

                return _db;
            }

            if(_line.toUpper().startsWith("CONSTANT")){
                QString _temp = _line.mid(QString("CONSTANT").count()).simplified();
                if(_temp.isEmpty()){
                    continue;
                }

                QStringList _tempVar = _temp.split("=");
                if(_tempVar.count() != 2){
                    continue;
                }

                _temp = _tempVar.at(0);
                _value = _tempVar.at(1).toDouble( &ok );
                if(!ok){
                    continue;
                }

                _db.constants.insert( _temp, _value );
                continue;
            }

//            if(_line.toUpper().startsWith("STEP")){
//                QString _temp = _line.mid(QString("STEP").count()).simplified();
//                if(_temp.isEmpty()){
//                    continue;
//                }

//                QStringList _tempVar = _temp.split("=");
//                if(_tempVar.count() != 2){
//                    continue;
//                }

//                _temp = _tempVar.at(0);
//                _value = _tempVar.at(1).toDouble( &ok );

//                if(!ok){
//                    continue;
//                }

//                _step_range.step = _value;
//                _db.steps.insert( _temp, _step_range );
//                QVector<double> _vec;
//                _step_values.insert( _temp, _vec );

//                continue;


//            }


            // columns
            if(_line.startsWith("#")){
                QStringList _columns = _line.mid(1).split("\t");
                if(_columns.count() < 2){
                    qDebug() << "Achtung!!";
                }

                _db.columns = _columns;
                continue;
            }

            // else measure
            QStringList _tempValues = _line.split("\t");
            QStringList _values;
            foreach(QString _temp, _tempValues){
                _temp = _temp.simplified();
                if(!_temp.isEmpty()){
                    _values << _temp;
                }
            }

            if(_db.columns.count() == 0 || _db.columns.count() != _values.count()){
                qDebug() << "FUCK";
                continue;
            }

            //good
            MEASURE_ROW _row;
            _row.inc = true;
            int i=0;
            foreach(QString _temp,_values){
                _value = _temp.toDouble(&ok);
                if(!ok){
                    _value = INFINITY;
                }

                if( _db.steps.keys().contains( _db.columns.at(i) ) ){

                    _step_values[_db.columns.at(0)].append( _value );

                }

                _row.row.append( _value );
                i++;
            }





            _db.table.append( _row );
        }


        if(!_start_db && _line.toUpper().startsWith("DB_BEGIN")){
            _start_db = true;

            continue;
        }


    }
    _step_values.clear();

    // error;
    qDebug() << "Parse error";
    return _db;
}

double TMeasure::min(QVector<double> vect)
{
    double min = FLT_MAX;
    for(int i=0; i < vect.count();i++){
        if(min > vect[i]){
            min = vect[i];
        }
    }
    return min;
}

double TMeasure::max(QVector<double> vect)
{    double max = -FLT_MAX;

     for(int i=0; i < vect.count();i++){
         if(max < vect[i]){
             max = vect[i];
         }
     }

     return max;
}
