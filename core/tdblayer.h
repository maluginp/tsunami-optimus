#ifndef TDBLAYER_H
#define TDBLAYER_H

#include <QtCore>
#include <QtSql>

class TDBLayer
{
public:
    TDBLayer();
    TDBLayer(QString dbName);
    ~TDBLayer();



    bool open(QString dbName);
    bool openConnectionName();

    bool query(QString querySQL);
    TDBLayer *bindQuery(QString querySQL);
    TDBLayer *bindValue(QString key,QVariant value);
    bool exec();

    void finishQuery();

    QVariant value(QString key);
    QVariant value(QString key,QVariant &defaultValue);


    bool isRequested() { return gResQuery; }
    bool isOpened();
    bool isNext();

    bool hasError();
    void printError();
    int count();

    QString getError() { return gLastError; }
    void setError(QString error);
    int getInsertID();

    void close();

    static TDBLayer *getInstance();

signals:
    void error(QString error);

private:
     QSqlDatabase gDataBase;
     QString gLastError;
     int gLastErrorNumber;
     QString gLastQuery;

     bool gResQuery;

     bool mOpened;

     QSqlQuery *gQueryHandle;
     QSqlRecord gQueryRecord;
};

#endif // TDBLAYER_H
