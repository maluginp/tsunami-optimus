#ifndef MOSFET_H
#define MOSFET_H

#include "core/tdevice.h"

class MOSFET : public TDevice
{
public:
    MOSFET(int device_id);
    ~MOSFET(){}

    void init();
    QVector< QPointF >  simulate(     QString _plot_type, STEP_RANGE _range);
    QVector< QPointF >  getPlotData(  QString _plot_type, STEP_RANGE _range);
    QPointF             computeValue( QString plot_name, QMap<QString, double> values);
    QString image();

    QStringList constantTitles(QString plot_type);
    QStringList columnTitles(QString plot_type);

};

#endif // MOSFET_H
