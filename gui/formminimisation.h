#ifndef FORMMINIMISATION_H
#define FORMMINIMISATION_H

#include <QDialog>
#include "managers/managerextractor.h"
#include "reports/reportoptimisation.h"
#include "qcustomplot.h"

namespace Ui {
class FormMinimisation;
}

class FormMinimisation : public QDialog
{
    Q_OBJECT

public:
    enum TYPE_LOG{
        LOG_DEFAULT,
        LOG_PARAMETER,
        LOG_WARNING,
        LOG_ERROR,
        LOG_ITERATION
    };

    explicit FormMinimisation(int device_id,QWidget *parent = 0);
    ~FormMinimisation();
private slots:
    void startExtraction();
    void doneIteration(int iteration,double error);
    void stopMinimisation();
    void doneMinimisation();
    void replotGraphics(QMap<QString, double> parameters);
    void saveParameters();
    void saveGraphic();
    void timerTimeout();
    void copyToClipboard();
    void axisDoubleClick(QCPAxis* axis,QCPAxis::SelectablePart part,QMouseEvent* event);
    void parametersContextMenu(QPoint pos);
    void plottableClick(QCPAbstractPlottable *graph,QMouseEvent *e);

signals:
    void stopExtraction();
private:
    Ui::FormMinimisation *ui;
    ManagerExtractor *managerExtractor;


    QMap<QString,double> mInitialParameters,
                        mOptimizeParameters;

    int mCurrentIteration;

    bool mStarted;
    void Log(char *text);
    void Log(QString text);
    void Log(char *text , TYPE_LOG type);
    void Log(QString text, TYPE_LOG type);
    void LogParameters(int iteration, QMap<QString,double> parameters );
    void LogIteration(int iteration);
    QFuture <void> threadFunc;
     QMutex mutex;

    QStringList mInitRanges;
    QTimer *mTimerRunning;

};

#endif // FORMMINIMISATION_H
