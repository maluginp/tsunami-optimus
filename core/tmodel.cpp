#include "tmodel.h"

TModel::TModel()
{
}

TModel::~TModel()
{
}

void TModel::setDevice(TDevice *device){
    device_ = device;
}

inline TDevice *TModel::device(){
    return device_;
}

void TModel::setName(QString name){
    name_ = name;
}

void TModel::setDeviceType(QString type)
{
    typeDevice_ = type;
}

double TModel::param(QString name){
    return 0.0;
}
