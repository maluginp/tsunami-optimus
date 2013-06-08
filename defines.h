#ifndef DEFINES_H
#define DEFINES_H

#include <QtCore>
#include <limits>
#include <float.h>
#include <math.h>

#define count_of(arr) (sizeof(arr) / sizeof(arr[0]))
enum DEVICE_TYPE{DEVICE_DIODE,DEVICE_BJT,DEVICE_JFET,DEVICE_MOSFET,DEVICE_UNDEF};

typedef struct _PLOT_AXIS_RANGE_{
    double max;
    double min;
} PLOT_AXIS_RANGE;

typedef QMap<QString,double> TParameters;


#define PHYSIC_VT( T ) (8.6171e-5*((T)+273.15))
#define T_KELVIN( T ) ( (T)+273.15 )

#define EPSOX 3.453133e-11
#define EPSSI 1.03594e-10 //this is in meters --> 1.03594e-8 F/cm
#define PI 3.141592654
#define CHARGE_Q 1.60219e-19
#define MAX_EXP 5.834617425e14
#define MIN_EXP 1.713908431e-15

#define CALC_COX( Tox ) (3.453133e-11/(Tox))
#define EXP_THRESHOLD 34.0

#ifdef Q_OS_WIN
#define INFINITY (std::numeric_limits<double>::infinity())
#define NGSPICE_PATH "spice/bin/ngspice.exe"
#else
#define NGSPICE_PATH "ngspice"
#endif

typedef struct _STEP_RANGE_{
    double start;
    double end;
    double step;
} STEP_RANGE;


#define TSLog( STR ) (qDebug() << (STR));


inline int getLevel( const QString *level ){
    QMap<QString,int> models;
    models.insert( "BSIM3v3", 8 );
    models.insert( "LEVEL2" , 2 );
    models.insert( "LEVEL3" , 3 );
    models.insert( "GummelPoon", 1);
    models.insert( "VBIC", 4);

    int l = models.value(*level,0);

    return l;
}




#endif // DEFINES_H
