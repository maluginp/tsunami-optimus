#ifndef JFET_H
#define JFET_H

#include "core/tdevice.h"

class JFET : public TDevice
{
public:
    JFET(int device_id);
    ~JFET() {}
    void init();
    void simulate(QString _plot_type);
    QVector< QPointF >  simulate(QString _plot_type, STEP_RANGE _range);
    QVector< QPointF >  getPlotData(QString _plot_type, STEP_RANGE _range);
    QPointF computeValue(QString plot_name, QMap<QString, double> values);
    QString image();


    QStringList constantTitles(QString plot_type);
    QStringList columnTitles(QString plot_type);



};

#endif // JFET_H
