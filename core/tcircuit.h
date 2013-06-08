#ifndef TCIRCUIT_H
#define TCIRCUIT_H

#include <QMap>
#include <QVector>
#include <QVariant>
#include <QStringList>
#include "tnet.h"

struct CIRCUIT_ANALYZE_DC{
    char* name;
    double start;
    double end;
    double step;
};

struct CIRCUIT_MODEL{
    char name[255];
    char polarity[255];
    int level;
    QMap<QString,QVariant> parameters;
};

class TCircuit
{
public:
    TCircuit(const char* name,const char* filename, const char* spicePath);
    void addNet( TNet* net );
    void setName(const char* name);
    void setFilename(const char *filename);
    void setSpicePath(const char* spicePath);
    void addModel( CIRCUIT_MODEL model );
    void setAnalyze( CIRCUIT_ANALYZE_DC analyze );
    void addPrint(QString print);
    void addPrint(QStringList prints);
    void addPrint(int count, ...);
    bool simulate();
    inline QVector< QVector<double> > getResult() { return result_; }


private:
    char name_[255];
    char filename_[255];
    char spicePath_[255];
    QVector<CIRCUIT_MODEL> models_;
    QVector<TNet* > nets_;
    CIRCUIT_ANALYZE_DC analyzeDc_;
    QStringList prints_;
    QVector< QVector<double> > result_;

    bool simulated_;

};

#endif // TCIRCUIT_H
