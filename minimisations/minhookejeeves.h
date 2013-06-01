#ifndef MINHOOKEJEEVES_H
#define MINHOOKEJEEVES_H

#include "core/extractor.h"

#define MAX_FAILED 10
class MinHookeJeeves : public Extractor
{
public:
    enum MASK {
        HJ_ENABLED=0,
        HJ_INC,
        HJ_DEC,
        HJ_DISABLE,
        HJ_HOLD,
        HJ_UNDEF
    };

    MinHookeJeeves(int id);
    ~MinHookeJeeves();

    void minimisation();
private:
    double               baseFunction_,
                         ultimateFunction_;
    bool                 stopThread_;
    QMap<QString,MASK>   masks_;
    QMap<QString,double> steps_;
    QMap<QString,double> precisions_;
    double               factor_;
    int                  countFailed_;
    double               prevFuncError_;
    QMutex mutexMin;

    bool bestNearby();
    void patternStep();
    bool decreaseSteps();

    void setMask(QString name,MASK _mask){
        masks_.insert(name,_mask);
    }

    double Step(QString name){
        if(steps_.contains(name)){
            return steps_.value(name);
        }
        return 0.0;
    }
    void setStep(QString name,double value){
        steps_.insert( name, value );
    }

    double Precision(QString name){
        if(precisions_.contains(name)){
            return precisions_[name];
        }
        // #TODO: change
        return 11111111;
    }
    void setPrecision(QString name,double value){ precisions_.insert(name,value); }

    double factor(){ return factor_; }
    void setFactor(double factor){ factor_ = factor; }


    MASK getMask(QString name){
        if(masks_.contains(name)){
            return masks_[name];
        }
        return HJ_UNDEF;
    }


};

#endif // MINHOOKEJEEVES_H
