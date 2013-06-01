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
    void simulate(QString _plot_type);
    QVector< QMap<Axis, double> >  simulate(QString _plot_type, STEP_RANGE _range);
    QVector< QMap<Axis, double> >  getPlotData(QString _plot_type, STEP_RANGE _range);
    QString image();

    void setGround(QString ground);
    void setPolarity(QString polarity);

    QMap<Axis,double> computeValue(QString plot_name, QMap<QString, double> values);
    QString groundName();
    QString polarityName();
    QStringList constantTitles(QString plot_type);
    QStringList columnTitles(QString plot_type);



private:
    COMMONS mCommon;

    double baseCurrent     ( double Vbe, double Vbc );
    double collectorCurrent( double Vbe, double Vbc );

    double VT(double T);

    double q1s(double Vbe,double Vbc);
    double q2s(double Vbe,double Vbc);
    double NqB(double Vbe,double Vbc);
    double Ifrw_dif(double Vbe);
    double Irvr_dif(double Vbc);
    double Irec_emitter(double Vbe);
    double Irec_collector(double Vbc);
};

#endif // BJT_H
