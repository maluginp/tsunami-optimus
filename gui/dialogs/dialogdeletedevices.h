#ifndef DIALOGDELETEDEVICES_H
#define DIALOGDELETEDEVICES_H

#include <QDialog>

namespace Ui {
class DialogDeleteDevices;
}

class DialogDeleteDevices : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDeleteDevices(QString filter,QWidget *parent = 0);
    ~DialogDeleteDevices();
    


private:
    Ui::DialogDeleteDevices *ui;
    void loadDeviceList(QString filter);

private slots:
    void appendToRemoveList();
    void removeFromRemoveList();

    void removeButtonClicked();
};

#endif // DIALOGDELETEDEVICES_H
