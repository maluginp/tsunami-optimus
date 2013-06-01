#ifndef FORMSTRATEGY_H
#define FORMSTRATEGY_H

#include <QMainWindow>
#include "managers/managerstrategy.h"

namespace Ui {
class FormStrategy;
}

class FormStrategy : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FormStrategy(QWidget *parent = 0);
    ~FormStrategy();
    void setDevice( TDevice *dev );
    int id() { return mId; }
    void Open(int id);

signals:
    void acceptStrategy(int id);

private slots:
    void newStrategy();
    void selectStrategy(QModelIndex index);
    void clickAccept();
    void setWeightsCoeff();
    void updateStrategyList();
    void selectMeasure(QModelIndex index);
private:
    Ui::FormStrategy *ui;
    int mId,
        measureId_;
    ManagerStrategy *strategyManager_;

    void setStrategy(int id);
    void setStrategy(QString name);
    QList<QStandardItem *> getRow(bool enable,QString name);
    void updateMeasureList();
    void saveStrategy();
};

#endif // FORMSTRATEGY_H
