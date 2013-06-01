#ifndef MOSFET_H
#define MOSFET_H

#include "core/tdevice.h"

class MOSFET : public TDevice
{
public:
    MOSFET(int device_id);
    ~MOSFET(){}

    void init();
    void simulate(QString _plot_type);
    QVector< QMap<Axis, double> >  simulate(QString _plot_type, STEP_RANGE _range);
    QVector< QMap<Axis, double> >  getPlotData(QString _plot_type, STEP_RANGE _range);
    QMap<Axis,double> computeValue(QString plot_name, QMap<QString, double> values);
    QString image();

    QStringList constantTitles(QString plot_type);
    QStringList columnTitles(QString plot_type);

};

#endif // MOSFET_H
