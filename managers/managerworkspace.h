#ifndef MANAGERWORKSPACE_H
#define MANAGERWORKSPACE_H

#include <QtCore>
#include <QtGui>

#include "core/tdblayer.h"
#include "core/tdevice.h"
#include "core/extractor.h"

class ManagerWorkspace  //: public QObject
{
//    Q_OBJECT
public:
    ManagerWorkspace();

    bool openDevice(int device_id);
    bool openDevice(QString name,QString device);

    TDevice *device();

    bool showPolarityForm();
    bool showGroundForm();
    bool showImageDevice();



    bool isDatabaseOpened();
    void connectDatabase();

    QMap<QString,QString> loadDataDevice();

    void setDataDevice(QString name, int data_id );
    bool setSetting( QString name, QVariant value );

    void setCurrentDevice( TDevice *device );


//signals:
//    void deviceOpened();

private:
    TDevice* deviceCurrent_;
    TDBLayer* layerDb_;

    void Log(QString log);

    DEVICE_TYPE getDeviceType(QString device_type);
    TDevice *createDeviceObject(int device_id, QString type);

};

#endif // MANAGERWORKSPACE_H
