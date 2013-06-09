#include "tnet.h"
#include "defines.h"

TNet::TNet(){
    terminals_.clear();
    values_.clear();
}

void TNet::setName(const char *name){
    if(strlen( name ) < 255){
        strncpy(name_,name,sizeof(name_));
    }
}
void TNet::setTerminals(QVector<int> terminals){
    if(terminals.count() > 0){
        terminals_.clear();
        terminals_ = terminals;
    }
}

void TNet::setTerminals(int count, ...){
    QVector<int> terminals;
    va_list args;
    va_start(args,count);
    for(int i=0; i < count;++i){
        terminals << va_arg(args,int);
    }
    setTerminals( terminals );
}

void TNet::addValue(QVariant value){
    values_.append( value );
}
void TNet::addValue(QVector<QVariant> values){
    for( QVector<QVariant>::iterator it = values.begin();
         it != values.end(); it++){
        values_.append( *it );
    }
}

void TNet::removeValue(QVariant value){
    for( QVector<QVariant>::iterator it = values_.begin();
         it != values_.end(); it++){
        if(*it == value){
//            values_.remove(it.);
        }
    }
}

TNet* TNet::createNet(const char *name, const QVector<int> *terminals, const QVector<QVariant> *values){

    TNet* net = new TNet();
    net->setName( name  );
    net->setTerminals( *terminals );
    net->addValue( *values );
    return net;

}
TNet* TNet::createNet(const char *name, const QVector<int> *terminals){
    TNet* net = new TNet();
    net->setName( name  );
    net->setTerminals( *terminals );
    return net;
}
TNet* TNet::createNet(const char *name){
    TNet* net = new TNet();
    net->setName( name  );
    return net;
}

QString TNet::getString(){
    QString net;
    char temp[255];

    ::sprintf(temp,"%s ",name_);
    net.append( QString::fromAscii( temp ) );
    foreach( int terminal, terminals_ ){
        ::sprintf(temp,"%d ",terminal);
        net.append( QString::fromAscii(temp) );
    }
    foreach( QVariant value, values_ ){
        TSLog(value);
        ::sprintf(temp,"%s ",value.toString().toAscii().data());
        net.append( QString::fromAscii(temp) );
    }

    TSLog( net );

    return net;



}
