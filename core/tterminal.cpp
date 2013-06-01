#include "tterminal.h"

TTerminal::TTerminal(QString name)
{

    mName = name;

    mCurrentMeasure = 0.0;
    mCurrentSource  = 0.0;
    mVoltageMeasure = 0.0;
    mVoltageSource  = 0.0;

    mType = SOURCE_UNDEF;
}

TTerminal::~TTerminal()
{
    //
}

double TTerminal::getMeasure(TTerminal::TERMINAL_TYPE type)
{
    if(type == GND){
        return 0.0;
    }

    if(type == TTerminal::CURRENT){
        return mCurrentMeasure;
    }
    return mVoltageMeasure;
}

TTerminal::TERMINAL_SOURCE TTerminal::getSourceType()
{
    return mType;
}

void TTerminal::setSource(TTerminal::TERMINAL_SOURCE source, double value)
{
    if(source == TTerminal::SOURCE_CURRENT){
       setCurrent( value );
       setVoltage( 0.0 );
       mType = source;
    }else if(source == TTerminal::SOURCE_VOLTAGE){
        setVoltage( value );
        setCurrent( 0.0 );
        mType = source;
    }else{
        setVoltage( 0.0 );
        setCurrent( 0.0 );
        mType = GND;
    }

    return;
}

void TTerminal::setMeasure(TTerminal::TERMINAL_TYPE type, double value)
{
    if(type == TTerminal::CURRENT){
        mCurrentMeasure = value;
    }else if(type == TTerminal::VOLTAGE){
        mVoltageMeasure = value;
    }

    return;
}

void TTerminal::setGnd()
{
    mType = GND;
    setVoltage( 0.0 );
    setCurrent( 0.0 );
}

bool TTerminal::isGnd()
{
    return (mType == GND);
}


double TTerminal::getVoltage()
{
    if(mType == GND){
        return 0.0;
    }

    return mVoltageSource;
}

double TTerminal::getCurrent()
{
    if(mType == GND){
        return 0.0;
    }

    return mCurrentSource;
}

void TTerminal::setVoltage(double value)
{
    if(mType != GND){
        mVoltageSource = value;
    }
}

void TTerminal::setCurrent(double value)
{
    if(mType != GND){
        mCurrentSource = value;
    }
}
