#ifndef FORMSETTING_H
#define FORMSETTING_H

#include <QDialog>
#include <QtCore>
namespace Ui {
class FormSetting;
}

class FormSetting : public QDialog
{
    Q_OBJECT
    
public:
    explicit FormSetting(QWidget *parent = 0);
    ~FormSetting();
private slots:
    void saveSetting();
    void openSetting();
private:
    Ui::FormSetting *ui;


};

#endif // FORMSETTING_H
