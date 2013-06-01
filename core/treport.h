#ifndef TREPORT_H
#define TREPORT_H

#include <QObject>
#include <QtCore>

class TReport : public QObject
{
    Q_OBJECT
public:

    enum REPORT_TYPE{
        REPORT_HTML,
        REPORT_TEXT,
        REPORT_XML
    };

    explicit TReport(QString name,QObject *parent = 0);
    ~TReport();

    void setEnable(bool enable);
    bool enable();

    void setFormat( QString format );
signals:
    
public slots:
    virtual bool Save();

protected:

    QString dirReport();

    void start();
    void end();

    void append(QString text);
    void append(QStringList text);
    void append(QString name,QString value);
    void appendTable(QStringList columns, QVector< QVector<double> > rows, bool addNum,QString id,bool display);

    void setError(QString error);
private:
    QFile *mFile;
    QString mData,
            mName,
            mError,
            mFileName;

    bool mEnable;
};

#endif // TREPORT_H
