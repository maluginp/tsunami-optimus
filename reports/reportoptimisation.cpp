#include "reportoptimisation.h"

ReportOptimisation::ReportOptimisation(QString name) : TReport(name,0)
{
}

void ReportOptimisation::addMeasures(QList<TMeasure *> measures){

    if(!enable()){
        return;
    }

    int index_db = 1;
    append(QString("<h2><a href=\"#\" onclick=\"change('measures')\">%1:</a></h2>")
           .arg(trUtf8("Измерения")));
    append("<div id=\"measures\">");
    foreach( TMeasure *measure, measures){

        QList<MEASURE_DB> databases = measure->databases();
        int _database_count = databases.count();

        if(_database_count > 0){
            append( QString("<h3>Тип: %1</h3>").arg( measure->plotType() ) );
        }


        for(int id_db=0; id_db < _database_count; id_db++){
            MEASURE_DB _db = databases.at(id_db);
            if(_db.inc){
                int _row_count = _db.table.count();
                QStringList _constants;
                foreach(QString _const,_db.constants.keys()){
                    _constants << QString("%1=%2").arg(_const).arg( _db.constants.value(_const) );
                }
                append(QString("<a href=\"#\" onclick=\"change('%1')\"><b>%2:</b> %3</a><br/>")
                        .arg(QString("measure%1").arg(index_db)).arg(trUtf8("Константы"))
                        .arg(_constants.join(", ")) );

                QVector< QVector<double> > rows;

                for(int row=0; row < _row_count; row++){
                    MEASURE_ROW _row = _db.table.at(row);
                    if(_row.inc){
                        QVector <double> _row_table;
                        for( int col=0; col < _db.columns.count(); col++ ){
                            _row_table.append( _row.row.at( col ) );

                        }

                        rows.append( _row_table );
                    }
                }

                if(rows.count() > 0){
                    appendTable( _db.columns, rows, true, QString("measure%1").arg(index_db), true );
                    rows.clear();
                }else{
                    append( trUtf8("Список пуст") );
                }

                index_db++;

            }

        }
        //        delete measure;
    }
    append("</div>");

}

void ReportOptimisation::addIteration( int iteration, TParameterSet *paramSet,  QMap<QString,double> parameters, double func_error ){
    if(!enable()){
        return;
    }

    QStringList _text;

    if(iteration > 0){
        append(QString(" <h3> %1 #%2 </h3> ").arg( trUtf8("Итерация") ).arg( iteration ));


        _text << "<table><thead>";
        _text << QString("<th>%1</th><th>%2</th><th>%3</th>").arg( trUtf8("Параметр") )
                 .arg( trUtf8("До") ).arg( trUtf8("После") );
        _text << "</thead><tbody>";

        foreach(QString _param_name, parameters.keys()){

            if(mPrevParameters.contains(_param_name)){
                _text << QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>").arg(_param_name)
                         .arg( mPrevParameters.value( _param_name ) )
                         .arg( parameters.value( _param_name ) );

            }



        }
        _text << QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>").arg(trUtf8("Ошибка"))
                 .arg( mPrevFuncError )
                 .arg( func_error );

        _text << "</tbody></table>";
    }else{
        append(QString(" <h3>%1</h3> ").arg( trUtf8("Начальное значение") ));


        _text << "<table><thead>";
        _text << QString("<th>%1</th><th>%2</th><th>%3</th><th>%4</th><th>%5</th>").arg( trUtf8("Параметр") )
                 .arg( trUtf8("Значение") ).arg( trUtf8("Минимум") )
                 .arg( trUtf8("Максимум") ).arg( trUtf8("Константа") );
        _text << "</thead><tbody>";

        QString _fixed("");
        foreach(QString _param_name, parameters.keys()){
            if(paramSet->fixed(_param_name)){
                _fixed = trUtf8("Да");
            }else{
                _fixed = trUtf8("Нет");
            }

            _text << QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td></tr>").arg(_param_name)
                     .arg( parameters.value( _param_name ) )
                     .arg( paramSet->min(_param_name) )
                     .arg( paramSet->max(_param_name) )
                     .arg( _fixed );


        }
        _text << "</tbody></table>";
        _text << QString("<p><b>%1: </b>%2</p>").arg(trUtf8("Начальная ошибка"))
                 .arg( func_error );




    }

    if(_text.count() > 0){
        append(_text);
    }

    mPrevParameters = parameters;
    mPrevFuncError = func_error;
}

void ReportOptimisation::addImage(QString name, QPixmap *pixmap)
{
    if(!enable()){
        return;
    }
//    pixmap->save( dirReport() + )
}
