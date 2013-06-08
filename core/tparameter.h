#ifndef TPARAMETER_H
#define TPARAMETER_H

#include <QtCore>

class TParameter
{
public:
    enum TYPE_VALUE{
        PARAMETER_INT,
        PARAMETER_DOUBLE,
        PARAMETER_FLOAT,
        PARAMETER_STRING
    };

    TParameter( QString key, double value );
    TParameter( QString key, float value );
    TParameter( QString key, QString value );
    TParameter( QString key, int value );

    QString name();

    QVariant value(){
        return mValue;
    }

    void setValue(QString key, double value);
    void setValue(double value);
    double getDouble();
    float getFloat();
    int getInt();

    bool isNull(){
        return mValue.toBool();
    }

    bool isInclude();

    void setDescription(QString desc);

private:
    QString mKey;
    QVariant mValue;
    TYPE_VALUE mType;
    QString mDescription;
    bool mInclude;


};

#endif // TPARAMETER_H
