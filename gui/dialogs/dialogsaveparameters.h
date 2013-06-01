#ifndef DIALOGSAVEPARAMETERS_H
#define DIALOGSAVEPARAMETERS_H

#include <QDialog>

namespace Ui {
class DialogSaveParameters;
}

class DialogSaveParameters : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogSaveParameters(QWidget *parent = 0);
    ~DialogSaveParameters();
    
    void setParameterSet(QString _param_set);
    bool isSaveAs();
    QString parameterSaveAs();
private:
    Ui::DialogSaveParameters *ui;
};

#endif // DIALOGSAVEPARAMETERS_H
