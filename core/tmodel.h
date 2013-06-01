#ifndef TMODEL_H
#define TMODEL_H

#include "core/tdevice.h"

class TModel
{
public:
    TModel();
    virtual ~TModel();
    void setDevice( TDevice *device );
    virtual void init() = 0;
    virtual void simulate() = 0;

    TDevice *device();

protected:
    void setName(QString name);
    void setDeviceType( QString type);
    double param(QString name);

    void setParameter( QString name, double value );
    bool isSpecifed( QString name );
private:
    TDevice *device_;
    QString name_,
        typeDevice_;
};

#endif // TMODEL_H
