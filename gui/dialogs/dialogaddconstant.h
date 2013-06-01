#ifndef DIALOGADDCONSTANT_H
#define DIALOGADDCONSTANT_H

#include <QDialog>

namespace Ui {
class DialogAddConstant;
}

class DialogAddConstant : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAddConstant(QWidget *parent = 0);
    ~DialogAddConstant();

    void setLabels(QString const1,QString const2);
    double value( int constNo );
    
private:
    Ui::DialogAddConstant *ui;
};

#endif // DIALOGADDCONSTANT_H
