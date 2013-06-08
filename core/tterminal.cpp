#include "tterminal.h"

TTerminal::TTerminal(QString name)
{

    name_ = name;

    measureCurrent_ = 0.0;
    sourceCurrent_  = 0.0;
    measureVoltage_ = 0.0;
    sourceVoltage_  = 0.0;

    type_ = SOURCE_UNDEF;
}

TTerminal::TTerminal(const TTerminal &terminal){

    name_ = terminal.name_;
    type_ = terminal.type_;
    sourceCurrent_ = terminal.sourceCurrent_;
    sourceVoltage_ = terminal.sourceVoltage_;
    measureCurrent_ = terminal.measureCurrent_;
    measureVoltage_ = terminal.measureVoltage_;

}

TTerminal &TTerminal::operator =(const TTerminal &terminal){
    name_ = terminal.name_;
    type_ = terminal.type_;
    sourceCurrent_ = terminal.sourceCurrent_;
    sourceVoltage_ = terminal.sourceVoltage_;
    measureCurrent_ = terminal.measureCurrent_;
    measureVoltage_ = terminal.measureVoltage_;
    return *this;
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
        return measureCurrent_;
    }
    return measureVoltage_;
}

TTerminal::TERMINAL_SOURCE TTerminal::getSourceType()
{
    return type_;
}

void TTerminal::setSource(TTerminal::TERMINAL_SOURCE source, double value)
{
    if(source == TTerminal::SOURCE_CURRENT){
        setCurrent( value );
        setVoltage( 0.0 );
        type_ = source;
    }else if(source == TTerminal::SOURCE_VOLTAGE){
        setVoltage( value );
        setCurrent( 0.0 );
        type_ = source;
    }else{
        setVoltage( 0.0 );
        setCurrent( 0.0 );
        type_ = GND;
    }

    return;
}

void TTerminal::setMeasure(TTerminal::TERMINAL_TYPE type, double value)
{
    if(type == TTerminal::CURRENT){
        measureCurrent_ = value;
    }else if(type == TTerminal::VOLTAGE){
        measureVoltage_ = value;
    }

    return;
}

void TTerminal::setGnd()
{
    type_ = GND;
    setVoltage( 0.0 );
    setCurrent( 0.0 );
}

bool TTerminal::isGnd()
{
    return (type_ == GND);
}


double TTerminal::getVoltage()
{
    if(type_ == GND){
        return 0.0;
    }

    return sourceVoltage_;
}

double TTerminal::getCurrent()
{
    if(type_ == GND){
        return 0.0;
    }

    return sourceCurrent_;
}

void TTerminal::setVoltage(double value)
{
    if(type_ != GND){
        sourceVoltage_ = value;
    }
}

void TTerminal::setCurrent(double value)
{
    if(type_ != GND){
        sourceCurrent_ = value;
    }
}
