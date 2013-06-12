#ifndef BJT_H
#define BJT_H

#include "core/tdevice.h"

class BJT : public TDevice
{
public:

    enum COMMONS{
        COM_EMITTER,
        COM_BASE,
        COM_COLLECTOR,
        COM_UNDEF
    };

    BJT(int device_id);
    ~BJT() {}
    void init();
    QVector< QPointF >  simulate(QString _plot_type, QMap<QString,STEP_RANGE> ranges);
    QVector< QPointF >  getPlotData(QString _plot_type, QMap<QString,STEP_RANGE> ranges);
    QPointF computeValue(QString plot_name, QMap<QString, double> values);
    QString image();

    void setGround(QString ground);
    void setPolarity(QString polarity);

    QString groundName();
    QString polarityName();
    QStringList constantTitles(QString plot_type);
    QStringList columnTitles(QString plot_type);



private:
    COMMONS mCommon;

};

#endif // BJT_H
