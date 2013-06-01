#ifndef MINQUASINEWTON_H
#define MINQUASINEWTON_H

#include "core/extractor.h"
class CMatrix;
#define MAX_FAILED 3
class MinQuasiNewton : public Extractor
{
public:
    MinQuasiNewton(int id);
    virtual void minimisation();
private:
    double dif(QString _name, double h);
    CMatrix &solveGrad(CMatrix X,double h);
    QMap<QString,double> convertMatrixToMap( CMatrix &matrix );

    int numberParameter( QString name );
    QString nameParameter( int num  );
    QVector<double> makeDichotomy(CMatrix Xk, CMatrix Sk, double eps, double prec);
    QVector<double> methodGoldenSection(CMatrix Xk, CMatrix Sk);
    QVector<double> methodPowell(CMatrix Xk, CMatrix Sk);

    double funcMinimisation(CMatrix Xk,CMatrix Sk,QVector<double> cappa);


    QMap<QString,double> getParameters();
    CMatrix &getParametersMatrix();
    void setParameters(CMatrix matrixParameters);
    void setParameters(QVector<double> parameters);

    double _getPrecisionValue(double min, double max);

    double precision( int num ){
        return mPrecisions.at(num);
    }
    double precision( QString name){
        return mPrecisions.at( numberParameter(name) );
    }

    double mBaseFunction,
        mUltimateFunction;

    double mFailed;

    QVector<double> mPrecisions;
};





#endif // MINQUASINEWTON_H
