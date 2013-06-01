#ifndef TMEASURE_H
#define TMEASURE_H

#include <QtGui>
#include "defines.h"
typedef QMap<QString,QVariant> TInfoMeasure;

typedef struct _MEASURE_ROW_{
    bool inc;
    QList<double> row;
} MEASURE_ROW;

typedef struct _MEASURE_DB_{
    bool inc;
    QStringList columns;
    QMap<QString,double> constants;
    QMap<QString,STEP_RANGE> steps;
    QList< MEASURE_ROW > table;

} MEASURE_DB;


class TMeasure
{
public:
    TMeasure();
    TMeasure(int _id);
    TMeasure(int dataset_id,QString name);

    ~TMeasure();
    void setID(int measure_id){
        id_ = measure_id;
    }

    int count();
    int id(){
        return id_;
    }

    bool Open();
    bool Save();
    bool Delete();
    static bool Delete(int id);
    QList<MEASURE_DB> databases(){
        return databases_;
    }


    void setDatasetID( int dataset_id ){
        datasetId_ = dataset_id;
    }

    int datasetID(){
        return datasetId_;
    }

    QString name(){
        return name_;
    }
    QString author(){
        return author_;
    }
    QString plotType(){
        return plotType_;
    }
    QString created(){
        return created_.toString("dd.MM.yyyy");
    }
    QDate createdDate(){
        return created_;
    }

    QString changed(){
        return changed_.toString("dd.MM.yyyy");
    }

    void setPlotType(QString type){
        plotType_ = type;
    }

    void setName(QString name){
        name_ = name;
    }
    void setAuthor(QString author){
        author_ = author;
    }

    QList<MEASURE_DB> measures(){
        return databases_;
    }
    QList<MEASURE_DB> measures(QStringList filterColumns);


    void addMeasureDB( MEASURE_DB db );
    void setMeasureDB( QList<MEASURE_DB> dbs);
    void addMeasureDB( QList<MEASURE_DB> dbs);


    QString stringDB( int id );
    QString stringDBs();

    bool import(QString path);

    bool exists();
    void setSetting(QString setting){
        settings_.clear();

        QStringList _list_values = setting.split(";");
        foreach(QString value,_list_values){
            QStringList _val = value.split("=");
            if(_val.count() != 2){
                continue;
            }
            settings_.insert( _val.at(0), _val.at(1) );
        }

//        mSetting = setting;
    }
    QString setting(){
        QStringList _settings;
        foreach(QString name, settings_.keys()){
            _settings << QString("%1=%2").arg(name).arg(settings_.value(name).toString());
        }

        return _settings.join(";");
    }
    QVariant setting(QString name){
        QVariant var;
        if(settings_.contains(name)){
            var = settings_.value( name );
        }
        return var;
    }
    QMap<QString,QVariant> settingMap(){
        return settings_;
    }


    static int create( int datasetId, QString name,QString plotType );

private:
    bool hasConsts_;
    int id_;
    int datasetId_;
    QString name_;
    QString author_;
    QString plotType_;
    QMap<QString,QVariant> settings_;
    QDate created_,changed_;
    QList<MEASURE_DB> databases_;

    QString importReadInfo(QStringList text, QString info);
    QList<MEASURE_DB> importReadDatabases(QStringList text);
    MEASURE_DB importReadDatabase(QStringList text, int &cur_pos,bool &last);

    double min(QVector<double> vect);
    double max(QVector<double> vect);
};

#endif // TMEASURE_H
