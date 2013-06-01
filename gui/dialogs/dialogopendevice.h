#ifndef DIALOGOPENDEVICE_H
#define DIALOGOPENDEVICE_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
namespace Ui {
class DialogOpenDevice;
}

class DialogOpenDevice : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogOpenDevice(QWidget *parent = 0);
    ~DialogOpenDevice();

    QString device();
    QString name();
    int id();
private slots:
    void setDevice(QModelIndex index);
    void newDevice();
private:
    Ui::DialogOpenDevice *ui;

    int id_;
    QString name_;
    QString type_;

    void updateDeviceList();
    QList<QStandardItem *> rowInfo(QString name,QString value);
};

#endif // DIALOGOPENDEVICE_H
