#ifndef DIALOGNEWPARAMETERSET_H
#define DIALOGNEWPARAMETERSET_H

#include <QDialog>
#include "managers/managerparameterset.h"

namespace Ui {
class DialogNewParameterSet;
}

class DialogNewParameterSet : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogNewParameterSet(ManagerParameterSet *manager,QWidget *parent = 0);
    ~DialogNewParameterSet();

    void setManager( ManagerParameterSet *manager ){
        managerParameterSet = manager;
    }
private slots:
    void clickAdd();
private:
    Ui::DialogNewParameterSet *ui;

    ManagerParameterSet *managerParameterSet;
};

#endif // DIALOGNEWPARAMETERSET_H
