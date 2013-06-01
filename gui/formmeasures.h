#ifndef FORMMEASURES_H
#define FORMMEASURES_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "managers/managermeasures.h"
namespace Ui {
class FormMeasures;
}

class FormMeasures : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FormMeasures(QWidget *parent = 0);
    void setDevice(TDevice *device);
    ~FormMeasures();
private:
    Ui::FormMeasures *ui;
    ManagerMeasures *managerMeasures_;
    QString dataset_;
    QString measure_;

    void updateMeasureList(QString dataset);
    QList<QStandardItem *> rowInfo(QString name,QString value);

private slots:
    void showEditorMeasures();
    void updateDatasetList();

    void selectDataset(QModelIndex index);
    void selectMeasure(QModelIndex index);

    void clickAddSet();
    void clickAddMeasure();
    void clickEditMeasure();

    void updateMeasures();
    void clickAccept();

signals:
    void acceptDataset(int id);

};

#endif // FORMMEASURES_H
