#ifndef DIALOGADDMEASURE_H
#define DIALOGADDMEASURE_H

#include <QDialog>

namespace Ui {
class DialogAddMeasure;
}

class DialogAddMeasure : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAddMeasure(QWidget *parent = 0);
    ~DialogAddMeasure();
    

    void setTypes(QMap<QString, QString> plots);
    QString name();
    QString type();
private:
    Ui::DialogAddMeasure *ui;


    QStringList mTypes;
};

#endif // DIALOGADDMEASURE_H
