#include "managerparameterset.h"
#include <QtXml>
#include "core/tdblayer.h"

ManagerParameterSet::ManagerParameterSet(TDevice *device)
{
    mDevice = device;
}

QMap<QString, PARAMETER_SET> ManagerParameterSet::getTemplate(QString name)
{
    QMap<QString, PARAMETER_SET> parameters;

    TDBLayer  *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("SELECT template FROM parameter_set_templates WHERE name=:name")
            ->bindValue(":name",name)
            ->exec();


    QString _template;

    if(!dbLayer->isNext()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return parameters;
    }

    _template = dbLayer->value("template").toString();

    QDomDocument doc;
    QString error;
    int error_line,error_column;
    if(!doc.setContent( _template,false, &error,&error_line,&error_column)){
        qDebug() << _template;
        qDebug() << "error:"<< error << "line:" << error_line << "col:" << error_column;
    }
    QDomNodeList _parameters =  doc.firstChild().toElement().elementsByTagName("param");

    qDebug() << _parameters.count();

    for(int i=0; i < _parameters.count(); i++){

        QDomElement _parameter = _parameters.at(i).toElement();
        PARAMETER_SET _param;
        QString _name;

        _param.id = -1;
        _param.initial = _parameter.attribute( "initial" ).toDouble();
        _param.minimum = _parameter.attribute("minimum").toDouble();
        _param.maximum = _parameter.attribute("maximum").toDouble();
        _param.fixed = static_cast<bool>(_parameter.attribute("fixed").toInt());
        _name = _parameter.attribute("name");

        parameters.insert( _name, _param );
    }
    delete dbLayer;
    return parameters;
}

bool ManagerParameterSet::Create(QString name, QString tpl){
    QMap<QString, PARAMETER_SET> _parameters = getTemplate( tpl );

    TDBLayer  *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("INSERT INTO parameter_sets(device_id,name,created,changed) "
                       "VALUES(:dev_id,:name,:created,:changed)")
            ->bindValue(":dev_id",mDevice->id())
            ->bindValue(":name",name)
            ->bindValue(":created",QDate::currentDate())
            ->bindValue(":changed",QDate::currentDate())
            ->exec();

    if(!dbLayer->isRequested()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return false;
    }
    mID = dbLayer->getInsertID();

    foreach(QString _param, _parameters.keys() ){
        dbLayer->bindQuery("INSERT INTO parameters(parameter_set_id,name,initial,optimized,minimum,maximum,fixed,created,changed,include) "
                           "VALUES(:set_id,:name,:initial,:optimize,:min,:max,:fixed,:created,:changed,1)")
                ->bindValue(":set_id",mID)
                ->bindValue(":name",_param)
                ->bindValue(":initial",_parameters.value(_param).initial)
                ->bindValue(":optimize",0)
                ->bindValue(":min",_parameters.value(_param).minimum)
                ->bindValue(":max",_parameters.value(_param).maximum)
                ->bindValue(":fixed",_parameters.value(_param).fixed)
                ->bindValue(":created",QDate::currentDate())
                ->bindValue(":changed",QDate::currentDate())
                ->exec();
        if(!dbLayer->isRequested()){
            qDebug() << dbLayer->getError();
        }
    }
    delete dbLayer;
    return true;




}

bool ManagerParameterSet::CreateTemplate(QString name, QMap<QString, PARAMETER_SET> vars)
{
    // #TODO: проверку существования имени шаблона
    QString _template;
    QDomDocument doc;

    QDomElement params = doc.createElement( "params" );
    doc.appendChild( params );
    //<param name="IS" initial="10" minimum="1" maximum="100" fixed="false" />
    foreach(QString _name,vars.keys()){
        QDomElement param = doc.createElement( "param" );

        param.setAttribute( "name", _name );
        param.setAttribute("initial", vars.value(_name).initial);
        param.setAttribute("minimum", vars.value(_name).minimum);
        param.setAttribute("maximum", vars.value(_name).maximum);
        param.setAttribute("fixed", vars.value(_name).fixed);

        params.appendChild( param );
    }


    _template = doc.toString(0);
    doc.clear();

    TDBLayer  *dbLayer = TDBLayer::getInstance();

    dbLayer->bindQuery("INSERT INTO parameter_set_templates(name,template,created,changed) "
                       "VALUES(:name,:tpl,:created,:changed)")
            ->bindValue(":name",name)
            ->bindValue(":tpl",_template)
            ->bindValue(":created",QDate::currentDate())
            ->bindValue(":changed",QDate::currentDate())
            ->exec();
    if(!dbLayer->isRequested()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return false;
    }
    delete dbLayer;
    return true;
}

QString ManagerParameterSet::getCurrentName()
{
    if(mID < 1){
        return QString("");
    }
    TDBLayer  *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT name FROM parameter_sets WHERE id=:id")
            ->bindValue(":id",mID)
            ->exec();

    if(!dbLayer->isNext()){
        qDebug() << dbLayer->getError();
        delete dbLayer;
        return QString("");
    }

    QString _name = dbLayer->value("name").toString();

    delete dbLayer;
    return _name;
}

QStringList ManagerParameterSet::listSets()
{
    QStringList _sets;
    TDBLayer  *dbLayer = TDBLayer::getInstance();
    dbLayer->bindQuery("SELECT name FROM parameter_sets WHERE device_id=:id")
            ->bindValue(":id",mDevice->id())
            ->exec();

    while(dbLayer->isNext()){
        _sets.append( dbLayer->value("name").toString() );
    }

    delete dbLayer;
    return _sets;


}

QStringList ManagerParameterSet::listManagers(){
    QStringList _managers;

    TDBLayer  *dbLayer = TDBLayer::getInstance();
    dbLayer->query("SELECT name FROM parameter_set_templates");
    while(dbLayer->isNext()){
        _managers.append( dbLayer->value( "name" ).toString() );
    }
    delete dbLayer;
    return _managers;
}


