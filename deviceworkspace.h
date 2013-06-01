#ifndef DEVICEWORKSPACE_H
#define DEVICEWORKSPACE_H

#include <QMainWindow>
#include "managers/managerworkspace.h"


namespace Ui {
class DeviceWorkspace;
}

class DeviceWorkspace : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DeviceWorkspace(QWidget *parent = 0);
    ~DeviceWorkspace();

    TDevice *device();
    
private:
    bool isDeviceOpened_;
    Ui::DeviceWorkspace *ui;
    ManagerWorkspace *workspaceManager_;
    bool isDeviceOpened(){ return isDeviceOpened_; }

private slots:
    void showDialogOpenDevice();
    void showDialogNewDevice();
    void showDialogRemoveDevice();
    void closeDevice();

    void showFormModels();
    void showFormGraphics();
    void showFormParameters();
    void showFormMeasures();
    void showFormStrategy();

    void showFormSetting();
    void runExtraction();

    void reloadWorkspace();

    void slotSetModelID(int id);
    void slotSetStrategyID(int id);
    void slotSetParameterSetID(int id);
    void slotSetDataset(int id);

signals:
    void reload();


};

#endif // DEVICEWORKSPACE_H
