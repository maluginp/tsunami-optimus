#ifndef MANAGERPARAMETERSET_H
#define MANAGERPARAMETERSET_H

#include "core/tdevice.h"
#include "core/tparameterset.h"

class ManagerParameterSet
{
public:
    ManagerParameterSet(TDevice *device);

    QMap<QString,PARAMETER_SET> getTemplate(QString name);

    bool Create(QString name,QString tpl);
    bool CreateTemplate(QString name, QMap<QString,PARAMETER_SET> vars);

    void setID(int id){
        mID = id;
    }



    QString getCurrentName();

    QStringList listSets();
    QStringList listManagers();

private:
    TDevice *mDevice;

    int mID;

};

#endif // MANAGERPARAMETERSET_H
