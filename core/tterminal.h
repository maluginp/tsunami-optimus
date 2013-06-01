#ifndef TTERMINAL_H
#define TTERMINAL_H

#include <QtCore>

class TTerminal
{
public:
    enum TERMINAL_SOURCE{
        SOURCE_CURRENT,
        SOURCE_VOLTAGE,
        GND,
        SOURCE_UNDEF
    };

    enum TERMINAL_TYPE{
        VOLTAGE,
        CURRENT
    };

    TTerminal(QString name);
    ~TTerminal();
    QString getName(){
        return mName;
    }
    QString name(){
        return mName;
    }

    double getMeasure( TERMINAL_TYPE type );

    TERMINAL_SOURCE getSourceType();

    void setSource(  TERMINAL_SOURCE source, double value );
    void setMeasure( TERMINAL_TYPE type, double value     );
    void setGnd();
    bool isGnd();

    double getVoltage();
    double getCurrent();
    void setVoltage(double value);
    void setCurrent(double value);

private:



    QString mName;

    TERMINAL_SOURCE mType;

    double mCurrentSource;
    double mVoltageSource;

    double mCurrentMeasure;
    double mVoltageMeasure;



};

#endif // TTERMINAL_H
