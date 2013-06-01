#include "minhookejeeves.h"

MinHookeJeeves::MinHookeJeeves(int id)  : Extractor(id) {

     iteration_     = 0;
     maxIterations_ = 100;

}

MinHookeJeeves::~MinHookeJeeves(){

    masks_.clear();
    steps_.clear();
    precisions_.clear();

}

void MinHookeJeeves::minimisation(){



    countFailed_ = 0;
    qDebug() << "Start minimisation";
    foreach(QString name,parameterSet()->parameterNames()){
        if( parameterSet()->fixed(name) ){
            setStep(name,0.0);
            continue;
        }
        setStep(name,  (parameterSet()->max(name) - parameterSet()->min(name))/10 );
        setPrecision(name, (parameterSet()->min(name) + parameterSet()->max(name))/2000);
    }

    setFactor(0.5);

    baseFunction_ = computeFunctionError();

    prevFuncError_ = baseFunction_;
    //start
    qDebug() << QString("Start function error: %1").arg(baseFunction_);


    ultimateFunction_ = INFINITY;
    iteration_ = 0;
    stopped_ = false;
    while(!isStop()){
        if(baseFunction_ > ultimateFunction_){

            patternStep();
        }else{
            while(!bestNearby()){

                if(isStop()){
                    break;
                }
                if(!decreaseSteps()){
                    emit doneMinimisation();
                    return;
                }
            }
        }
    }
    emit doneMinimisation();
    return;
}

bool MinHookeJeeves::bestNearby()
{

    double objectiveFunction;
    ultimateFunction_ = baseFunction_;

    foreach(QString name,parameterSet()->parameterNames()){
        if(! parameterSet()->fixed(name) ){
            double CCV = paramValue(name);
            setParameter( name, CCV + Step(name) );
            objectiveFunction = computeFunctionError();
            if(objectiveFunction < ultimateFunction_){
                ultimateFunction_ = objectiveFunction;
                setMask(name,HJ_INC);
            }else{
                setParameter( name, CCV - Step(name) );
                objectiveFunction = computeFunctionError();
//                if(objectiveFunction == -1) return false;
                if(objectiveFunction < ultimateFunction_){
                    ultimateFunction_ = objectiveFunction;
                    setMask(name,HJ_DEC);
                }else{
                    setParameter(name,CCV);
                    setMask(name,HJ_HOLD);
                }
            }
        }
    }

    bool _res = (baseFunction_ > ultimateFunction_);
    if(_res){
        saveParameters();
    }


    return _res;
}

void MinHookeJeeves::patternStep(){
    baseFunction_ = ultimateFunction_;
    foreach(QString name,parameterSet()->parameterNames()){
        if(! parameterSet()->fixed(name) ){
            switch(getMask(name)){
            case HJ_INC:
                setParameter( name, paramValue(name) + Step(name) );
                break;
            case HJ_DEC:
                setParameter( name, paramValue(name) - Step(name) );
                break;
            case HJ_HOLD:
            default:
                // value = mModel->Parameter(name).value;
                break;
            }
        }
    }
    ultimateFunction_ = computeFunctionError();
}

bool MinHookeJeeves::decreaseSteps(){
    if(nextIteration()){
        foreach(QString name,parameterSet()->parameterNames()){
            if(parameterSet()->fixed(name)){
                continue;
            }
            if(Step(name)*factor() < Precision(name)){
                setStep(name,Precision(name));
            }else{
                setStep(name,Step(name)*factor());
            }
        }

        int _iter = iteration();

        double _eps = prevFuncError_ - ultimateFunction_;

        if(_eps < 0 ){
            return false;
        }


//        saveParameters();
        emit doneIteration( _iter ,ultimateFunction_ );

        if( _eps < 0.001 ){
            if(countFailed_ > MAX_FAILED){
              return false;
            }else{
                countFailed_++;
            }
        }else{
            countFailed_ = 0;
        }

        prevFuncError_ = ultimateFunction_;



    }else{
        return false;
    }


    return true;
}
