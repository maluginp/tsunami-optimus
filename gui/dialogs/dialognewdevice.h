#ifndef DIALOGNEWDEVICE_H
#define DIALOGNEWDEVICE_H

#include <QDialog>

namespace Ui {
class DialogNewDevice;
}

class DialogNewDevice : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogNewDevice(QWidget *parent = 0);
    ~DialogNewDevice();

    QString name();
    QString device();
    QString polarity();
private slots:
    void clickAdd();
    void on_boxType_currentIndexChanged(const QString &arg1);

private:
    Ui::DialogNewDevice *ui;
};

#endif // DIALOGNEWDEVICE_H
