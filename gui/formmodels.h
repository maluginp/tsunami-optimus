#ifndef FORMMODELS_H
#define FORMMODELS_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

namespace Ui {
class FormModels;
}

class FormModels : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FormModels(QString device_type, QWidget *parent = 0);
    ~FormModels();


    void setDevice(QString name_device);
    int id();
private slots:
    void updateListModels();
    void applyFilter(QString name);
    void changeIndexListModels( QModelIndex index);
    void clickAccept();

signals:
    void acceptModel(int id);

private:
    Ui::FormModels *ui;
    QString mDevice;
    QList<QStandardItem *> rowInfo(QString name,QString value);
};

#endif // FORMMODELS_H
