#ifndef EDITORMEASURES_H
#define EDITORMEASURES_H

#include <QMainWindow>
#include "defines.h"
#include "managers/managermeasures.h"
#include "qcustomplot.h"



namespace Ui {
class EditorMeasures;
}


class EditorMeasures : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit EditorMeasures(QString name,QString type, ManagerMeasures *manager, QWidget *parent = 0);
    explicit EditorMeasures(int measure_id,ManagerMeasures *manager, QWidget *parent = 0);
    void setManager(ManagerMeasures *measure);

    bool Open(int measure_id);

    ~EditorMeasures();
    QString plot_type(){
        return mType;
    }
    QString name(){
        return mName;
    }

private slots:
    void clickAddColumn();
    void clickAddRow();
    void changeDataMeasure(QModelIndex i1,QModelIndex i2);
    void changeDataConstant(QStandardItem *item);
    void replotGraphics();
    void clickAddConstValue();
    void saveMeasure();
    void changePlotType(QString name);
    void selectConstValue(QModelIndex index);
    void importMeasures();

    void copyToClipboard();
    void clickPlotter(QMouseEvent *event);
    void plottableClick(QCPAbstractPlottable* plot,QMouseEvent* mouse);
signals:
    void changeMeasures();

private:
    Ui::EditorMeasures *ui;

    bool mMeasuresChanged;
    int mID;
    QString mName;
    QString mType;
    QString mAuthor;
    QString mCreated;
    QString mChanged;
    ManagerMeasures *managerMeasures;


    void loadInfo();

    QList< MEASURE_DB > mMeasures;

    void setName(QString name);
    void setType(QString type);
    double min(QVector<double> vect);
    double max(QVector<double> vect); 

    QList< MEASURE_DB > measures();

    int findDB(QString constant_string);

    int mCurrentMeasure;
    bool saveCurrentDB();
    void initialize();

    void setInfo(QString type,QVariant value);
    QVariant info( QString name );
    QMap<QString,QVariant> mSettingMap;

    void updateMeasures();

    QCPGraph *mLastClickGraph;

    QStandardItem *findItemCheckFromConstants( QString _constant );
    QModelIndex findItemFromConstants( QString _constant );


protected:
    void closeEvent(QCloseEvent *event);
    bool maybeSave();

};

#endif // EDITORMEASURES_H
