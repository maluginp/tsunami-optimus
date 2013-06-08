#ifndef TSETTING_H
#define TSETTING_H

#include <QtCore>

class TSetting
{
public:
    TSetting();

    static QVariant value(QString group, QString name);
    static bool isEq( QString group, QString name, QString value );




};

#endif // TSETTING_H
