#ifndef TNET_H
#define TNET_H

#include <QVector>
#include <QVariant>
class TNet
{
public:
    TNet();
    ~TNet();

    void setName( const char* name );
    void setTerminals( QVector<int> terminals );
    void setTerminals( int count, ... );
    void addValue( QVariant value );
    void addValue( QVector<QVariant> values );
    void removeValue( QVariant value );

    static TNet* createNet( const char* name, const QVector<int>* terminals, const QVector<QVariant>* values );
    static TNet* createNet( const char* name, const QVector<int>* terminals);
    static TNet* createNet( const char* name);


    QString getString();
private:
    char name_[255];
    QVector<int> terminals_;
    QVector<QVariant> values_;
    QString cache_;



//    void computeCache();
};

#endif // TNET_H
