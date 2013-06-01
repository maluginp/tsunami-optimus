#include "treport.h"

TReport::TReport(QString name, QObject *parent) :
    QObject(parent)
{
    mName = name;
    QString _name = mName.replace( ".", "_" ).replace(" ","_").replace(",","_").replace("/","_");
    mFileName = QString("%1_%2.html").arg( QDate::currentDate().toString("dd_MM_yyyy")).arg(_name);

    start();
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    mFile = new QFile( mFileName );

    setEnable( true );
}

TReport::~TReport(){

    if(mFile->isOpen()){
        mFile->close();
    }

}

void TReport::setEnable(bool enable)
{
    mEnable = enable;
}

bool TReport::enable()
{
    return mEnable;
}

void TReport::setFormat(QString format)
{
    qDebug() << "Format report: " << format;

}

bool TReport::Save(){
    if(!enable()){
        return false;
    }
    end();
    QString _name = mName.replace( ".", "_" ).replace(" ","_").replace(",","_").replace("/","_");


    if(!mFile->open( QIODevice::ReadWrite | QIODevice::Truncate )){
        setError( mFile->errorString() );
        return false;
    }

    if(mFile->write( mData.toAscii()  ) == -1){
        setError( mFile->errorString() );
        mFile->flush();
        mFile->close();
        return false;
    }

    mFile->flush();
    mFile->close();
    return true;

}

QString TReport::dirReport()
{
    QFileInfo info(*mFile);

    return info.canonicalPath();
}



void TReport::start(){
    QStringList _start;

    _start << "<html><head>";
    _start << "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>";
    _start << QString("<title>%1 %2 - %3</title>").arg(trUtf8("Отчёт")).
              arg(mName).arg( QDate::currentDate().toString( "dd.MM.yyyy" ) ) ;
    _start << "<script>function change(idName) {"
      "if(document.getElementById(idName).style.display=='none') {document.getElementById(idName).style.display = '';} "
      "else {document.getElementById(idName).style.display = 'none';} return false; } </script>";


    _start << "</head><body>";

    append(_start);


}

void TReport::end(){
    append("</body></html>");
}

void TReport::append(QString text)
{
    mData.append( text +"\n" );
}

void TReport::append(QStringList text){

    foreach(QString _text,text){
        append(_text);
    }
}

void TReport::append(QString name, QString value){

    append( QString("<b>%1: </b>%2<br/>").arg(name).arg(value) );

}

void TReport::appendTable(QStringList columns, QVector<QVector<double> > rows, bool addNum,QString id,bool display)
{
    QStringList _text;
    int index = 1;
    _text << QString("<table id=\"%1\">").arg(id);
    _text << "<thead>";
    if(addNum){
        _text << "<th>#</th>";
    }
    foreach(QString _colname, columns){
        _text << QString("<th>%1</th>").arg( _colname );
    }
    _text << "</thead>";
    _text << "<tbody>";

    foreach( QVector<double> _rows, rows ){
        _text << "<tr>";
        if(addNum){
            _text << QString("<td>%1</td>").arg( index );
        }
        foreach(double _col, _rows){
            _text << QString("<td>%1</td>").arg( _col );
        }
        _text << "</tr>";
        index++;
    }

    _text << "</tbody>";
    _text << "</table>";

    append(_text);


}

void TReport::setError(QString error)
{
    mError = error;
}
