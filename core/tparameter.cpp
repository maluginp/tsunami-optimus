#include "tparameter.h"

TParameter::TParameter(QString key, double value){
    mKey = key;
    mValue = QVariant::fromValue(value);
    mType = PARAMETER_DOUBLE;

    mInclude = false;
}

TParameter::TParameter(QString key, int value){
    mKey = key;
    mValue = QVariant::fromValue( value );
    mType = PARAMETER_INT;
    mInclude = false;
}

QString TParameter::name()
{
    return mKey;
}

void TParameter::setValue(QString key, double value)
{
    mKey = key;
    mValue = QVariant::fromValue(value);
    mType = PARAMETER_DOUBLE;
    mInclude = true;
}

void TParameter::setValue(double value)
{
    mValue = QVariant::fromValue(value);
    mInclude =true;
}

double TParameter::getDouble(){
    if(mType == PARAMETER_DOUBLE){
        return mValue.toDouble();
    }

    return -1;

}

float TParameter::getFloat()
{
    if(mType == PARAMETER_FLOAT){
        return mValue.toFloat();
    }

    return -1.0;
}

int TParameter::getInt()
{
    if(mType == PARAMETER_INT){
        return mValue.toInt();
    }
    return -1.0;
}

bool TParameter::isInclude(){
    return mInclude;
}

void TParameter::setDescription(QString desc)
{
    mDescription = desc;
}

TParameter::TParameter(QString key, float value){
    mKey   = key;
    mValue = QVariant::fromValue( value );
    mType  = PARAMETER_FLOAT;
    mInclude = false;
}

TParameter::TParameter(QString key, QString value){
    mKey   = key;
    mValue = QVariant::fromValue( value );
    mType  = PARAMETER_STRING;
    mInclude = false;
}
