#ifndef FORMPARAMETERS_H
#define FORMPARAMETERS_H

#include <QMainWindow>
#include "managers/managerparameterset.h"
#include "core/tparameterset.h"


namespace Ui {
class FormParameters;
}

class FormParameters : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FormParameters(QWidget *parent = 0);
    ~FormParameters();

    void setDevice( TDevice *device );
private slots:
    void changeParameterSets(QString parameterSet);
    void clickBtnAdd();
    void clickBtnRemove();
    void clickApply();
    void clickCancel();
    void clickAddSet();
    void clickSaveTemplate();

signals:
    void updateParameterSet(QString name,int id);
    void acceptParameters(int id);
private:
    Ui::FormParameters *ui;
    QString mCurrentParameterSet;
    TParameterSet *mParameterSet;
    ManagerParameterSet *managerParameterSet;

    TDevice *mDevice;

    void reloadListSets(QString selectName);

};

#endif // FORMPARAMETERS_H
