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
    TTerminal(const TTerminal &terminal);
    TTerminal &operator =(const TTerminal &terminal);

    ~TTerminal();
    QString getName(){
        return name_;
    }
    QString name(){
        return name_;
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

    QString name_;
    TERMINAL_SOURCE type_;
    double sourceCurrent_;
    double sourceVoltage_;

    double measureCurrent_;
    double measureVoltage_;



};

#endif // TTERMINAL_H
