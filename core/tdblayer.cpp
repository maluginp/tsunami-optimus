#include "tdblayer.h"


extern TDBLayer *DBLayer;

TDBLayer::TDBLayer(){
    gQueryHandle = NULL;

}

TDBLayer::TDBLayer(QString dbName){
    open(dbName);
    gQueryHandle = NULL;
}

TDBLayer::~TDBLayer(){
    if(gDataBase.isOpen()){
        finishQuery();
//        gDataBase.close();
//        if(gDataBase.lastError().type() == QSqlError::ConnectionError){
//            gLastError = gDataBase.lastError().text();
//        }
    }
}

bool TDBLayer::open(QString dbName){
    if(QSqlDatabase::contains("tsunami_connection")){
        gDataBase = QSqlDatabase::database("tsunami_connection",true);
    }else{
        gDataBase = QSqlDatabase::addDatabase("QSQLITE","tsunami_connection");
    }
    if(!gDataBase.databaseName().isEmpty()){
        if(gDataBase.databaseName() == dbName && gDataBase.isOpen()) return true;
    }

    gDataBase.setDatabaseName(dbName);

    if(!gDataBase.open()){
        gLastError = gDataBase.lastError().text();
        mOpened = false;
        return false;

    }


    mOpened = true;

    return true;

}

bool TDBLayer::openConnectionName(){
        gDataBase = QSqlDatabase::database("tsunami_connection",true);
        if(!gDataBase.databaseName().isEmpty()){
            mOpened = true;
            return true;
        }
        mOpened = false;
        return false;
}

bool TDBLayer::query(QString querySQL)
{
    //    gQueryHandle =new QSqlQuery(gDataBase);
    gQueryHandle = new QSqlQuery(gDataBase);

    bool ack;
    ack =   gQueryHandle->exec(querySQL);

    gLastQuery =  gQueryHandle->lastQuery();
    if(!ack){
        gLastError = gQueryHandle->lastError().text();
        gLastErrorNumber = gQueryHandle->lastError().number();
    }else{
        gLastError = "";
        gQueryRecord = gQueryHandle->record();
    }

    gResQuery = ack;

    return ack;

}

TDBLayer *TDBLayer::bindQuery(QString querySQL)
{
    gQueryHandle = new QSqlQuery(gDataBase);

    gQueryHandle->prepare(querySQL);

    gLastQuery = gQueryHandle->lastQuery();
    return this;

}

TDBLayer *TDBLayer::bindValue(QString key, QVariant value)
{
    gQueryHandle->bindValue(key,value);

    return this;
}

bool TDBLayer::exec()
{
    bool ack;
    gLastQuery =  gQueryHandle->lastQuery();

    ack =   gQueryHandle->exec();

    gResQuery = ack;

    if(!ack){
        setError( gQueryHandle->lastError().text() );
    }else{
        gLastError = "";
        gQueryRecord = gQueryHandle->record();
    }


    return ack;
}

void TDBLayer::finishQuery()
{
    if(gQueryHandle != NULL){
        gQueryHandle->finish();
        gQueryHandle->clear();
        delete gQueryHandle;
    }
    gQueryRecord.clear();

    return;
}

QVariant TDBLayer::value(QString key)
{
    return gQueryHandle->value(gQueryRecord.indexOf(key));
}

QVariant TDBLayer::value(QString key, QVariant &defaultValue)
{
    if(gQueryRecord.indexOf(key) == -1){
        return defaultValue;
    }

    return value(key);
}

bool TDBLayer:: isOpened()
{
    return mOpened;
//    bool ack = gDataBase.isOpen();
//    if(!ack){
//        setError( gDataBase.lastError().text() );
//    }

//    return ack;
}

bool TDBLayer::isNext()
{
    return gQueryHandle->next();
}

int TDBLayer::count()
{
    if(gQueryHandle != NULL)
        return gQueryHandle->numRowsAffected();

    return 0;
}

void TDBLayer::setError(QString error){
    gLastError = error;
}

int TDBLayer::getInsertID()
{
    bool ok;
    int id = gQueryHandle->lastInsertId().toInt(&ok);

    if(!ok) return -1;

    return id;
}

void TDBLayer::close()
{
    finishQuery();

    gDataBase.close();

}

TDBLayer *TDBLayer::getInstance()
{
    TDBLayer *dbLayer = new TDBLayer();
    if(!dbLayer->openConnectionName()){
        qDebug() << "cannot open connection";
    }
    return dbLayer;
}
