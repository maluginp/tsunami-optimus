#include "tsetting.h"

TSetting::TSetting()
{
}

QVariant TSetting::value(QString group, QString name){
QString _dir;
#ifdef Q_OS_WIN
    _dir = QDir::currentPath()+"/";
#else
    _dir = "/Developer/Projects/tsunami-optimus/";
#endif

    QSettings options(_dir+"setting.ini", QSettings::IniFormat);

    options.beginGroup( group );
    QVariant _val = options.value( name );

    options.endGroup();


    return _val;
}

bool TSetting::isEq(QString group, QString name, QString value)
{
    QVariant _value = TSetting::value( group,name );

    if(_value.toString().compare(value,Qt::CaseInsensitive) == 0){
        return true;
    }

    return false;
}


