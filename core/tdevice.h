#ifndef TDEVICE_H
#define TDEVICE_H

#include <QObject>
#include <QtCore>
#include <QtGui>

#include "core/tparameter.h"
#include "core/tterminal.h"
#include "defines.h"

struct DEVICE_PLOT{
    QString title;
    QString axis_x;
    QString axis_y;
};

struct MODEL_STRUCT{
    QString name;
    bool user_defined;
    QString author;
    QString path;
};

class TDevice : public QObject {
    Q_OBJECT
public:
    enum Polarity{POLARITY_N = 0,POLARITY_P,POLARITY_UNDEF};
    enum Axis{AXIS_X,AXIS_Y};
//    TDevice();
    explicit TDevice(int id){
        id_ = id;
    }

    explicit TDevice(QObject *parent = 0);
    virtual ~TDevice();

    virtual void init() = 0;
    virtual void simulate(QString _plot_type) = 0;
    virtual QVector< QMap<Axis, double> >  simulate(QString _plot_type, STEP_RANGE _range) = 0;
    virtual QVector< QMap<Axis, double> >  getPlotData(QString _plot_type, STEP_RANGE _range) = 0;
    virtual QMap<Axis,double> computeValue(QString plot_name,QMap<QString,double> values) = 0;
    virtual QString image() = 0;

    QString image(     QString name );

    QString name();

    TTerminal *terminal(  QString name );
    QList<TTerminal *> terminals();
    TParameter *parameter( QString name );

    QStringList polarities();
    bool hasPolarity();
    Polarity polarity();
    void setPolarity(Polarity _polarity );

    double param(QString name);


    bool Save();
    bool Open();
    bool Delete();

    int id(){ return id_; }

    void setModelID(int id){ modelId_  = id; }
    void setStrategyID(int id){strategyId_ = id;}
    void setParametersID(int id){parametersId_ = id;}
    void setDatasetID(int dataset_id){datasetId_ = dataset_id;}
    void setName(QString name);
    QString deviceType();

    QList<TParameter *> getParameters();



    virtual QString groundName();
    virtual QString polarityName();
    virtual void setGround(QString ground);
    virtual QStringList constantTitles(QString plot_type);
    virtual QStringList columnTitles(QString plot_type);
    virtual void setPolarity(QString polarity);

    int parameterSetId(){
        return parametersId_;
    }
    int datasetId(){
        return datasetId_;
    }
    int modelId(){  return modelId_; }
    int strategyId(){ return strategyId_; }

    void setMeasureTerminal( QString type, double value );
    void setMeasureTerminal( QMap<QString,double> values);
    QMap<QString,double> measureTerminals();
    void setSourceTerminal( QString type, double value );
    void setSourceTerminal( QMap<QString,double> values );
    QMap<QString,double> sourceTerminals();

    DEVICE_PLOT plot(QString name);
    QMap<QString,DEVICE_PLOT> plots(){
        return plots_;
    }
    QMap<QString,QString> plotTitles();

    bool setSettings( QString name, QVariant value );
    bool setSettings( QVariantMap values );
    bool saveSetting( QVariantMap values );

    static TDevice *createObject(int device_id, QString device_type);
    static TDevice *openDevice( int device_id );
    static QVariantMap parseMap(QString map);
    QString createMap(QVariantMap map);

    static bool Create(QString name, QString device, int &device_id);

    void setSetting( QString name, QVariant value ){
        settings_.insert( name, value );
    }

    QVariant setting( QString name ){
        QVariant var;
        if(settings_.contains(name)){
            var = settings_.value(name);
        }
        return var;
    }

    DEVICE_TYPE type(){
        return type_;
    }

    static int getIdByName(QString name);

protected:
    void addImage(QString name,QString path);
    void setModel(QString getModel);
    TParameter *addParameter( QString param, QString desc, TParameter::TYPE_VALUE type );
    TParameter *addParameter( QString param, QString desc, double value);
    void addTerminal(QString term_name );
    void setID(int id){ id_ = id; }
    void setPolarities( QStringList polarities );
    void setType(DEVICE_TYPE type){ type_ = type; }
    void addPlot(QString name, QString title,QString x, QString y){
        if(!plots_.contains(name)){
            DEVICE_PLOT _plot = {title,x,y};
            plots_.insert( name, _plot );
        }
    }
    MODEL_STRUCT  getModel();
    QMutex mutexSimulate;

//    bool checkRange(STEP_RANGE range);

private:
    int id_;
    int modelId_;
    int strategyId_;
    int parametersId_;
    int datasetId_;
    QDate created_;
    QDate changed_;
    QString name_;
    DEVICE_TYPE type_;
    QString model_;
    QStringList polarities_;
    bool hasPolarity_;
    Polarity polarity_;
    QMap<QString,DEVICE_PLOT> plots_;
    QList<TParameter *> parameters_;
    QList<TTerminal *>  terminals_;
    QMap<QString,QString> images_;
    QMap<QString,QVariant> settings_;

signals:
    void simulateError(QString desc);

};

#endif // TDEVICE_H
