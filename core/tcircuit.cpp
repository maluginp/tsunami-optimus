#include "tcircuit.h"
#include "defines.h"

TCircuit::TCircuit(const char* name,
                   const char* filename,
                   const char* spicePath){
    setName(name);
    setFilename(filename);
    setSpicePath(spicePath);
}

void TCircuit::addNet(TNet *net){
    nets_.append( net );
}

void TCircuit::setName(const char *name){
    if(strlen(name) < 255){
        strncpy(name_,name,sizeof(name_));
    }
}
void TCircuit::setFilename(const char *filename){
    if(strlen(filename) < 255){
        strncpy(filename_,filename,sizeof(filename_));
    }
}

void TCircuit::setSpicePath(const char *spicePath){
    if(strlen(spicePath) < 255){
        strncpy(spicePath_, spicePath, sizeof(spicePath_) );
    }
}

void TCircuit::addModel(CIRCUIT_MODEL model){
    for(int i=0; i < models_.count(); i++){
        if( strcmp( models_.at(i).name, model.name) == 0 ){
            models_[i] = model;
            return;
        }
    }

    models_.append( model );
    return;

}

void TCircuit::setAnalyze(CIRCUIT_ANALYZE_DC analyze){
    if( fabs(analyze.start) == INFINITY  ||
            fabs(analyze.end) == INFINITY ||
            fabs(analyze.step) == INFINITY ){
        return;
    }
    if( strlen(analyze.name) > 0 &&
            fabs(analyze.start) < fabs(analyze.end) &&
            fabs( analyze.end - analyze.start ) > fabs(analyze.step)){
        analyzeDc_ = analyze;
    }

    return;
}

void TCircuit::addPrint(QString print){
    prints_.append( print );
}

void TCircuit::addPrint(QStringList prints){
    foreach(QString print,prints){
        prints_.append( print );
    }
}

void TCircuit::addPrint(int count,...){
    QStringList prints;
    va_list vlist;
    va_start(vlist,count);
    for(int i=0; i<count; ++i){
        char* print = va_arg(vlist,char *);
        if(strlen(print) > 0){
            prints << QString::fromAscii(print);
        }
    }

    addPrint(prints);

}

bool TCircuit::simulate(){

    if(nets_.count() == 0 ||
            fabs(analyzeDc_.start) == INFINITY  ||
            fabs(analyzeDc_.end) == INFINITY ||
            fabs(analyzeDc_.step) == INFINITY ){
        TSLog("Error to simulate: initialized");
        return false;
    }

    if(!QFile::exists( filename_ )){
        QFile::remove( filename_ );
    }
    if(!QFile::exists( spicePath_ )){
        TSLog("Could't find spice simulator");
        return false;
    }


    QFile file( filename_ );
    // Create circuit file
    if(!file.open( QIODevice::ReadWrite )){
        TSLog( "Couldn't create circuit file" );
        return false;
    }
    char buffer[1024];
    ::sprintf( buffer, "%s\n\n", name_ );
    file.write( buffer );

    foreach(TNet* net,nets_){
        ::sprintf( buffer, "%s\n", net->getString().toAscii().data());
        file.write( buffer );
    }

    ::sprintf( buffer, ".dc %s %f %f %f\n",
               analyzeDc_.name, analyzeDc_.start,
               analyzeDc_.end, analyzeDc_.step  );
    file.write( buffer );

    ::sprintf( buffer, ".print %s\n", prints_.join(" ").toAscii().data() );
    file.write( buffer );

    foreach(CIRCUIT_MODEL model,models_){
        ::sprintf( buffer, ".model %s %s\n", model.name,model.polarity );
        file.write(buffer);
        if(model.level != 0){
            ::sprintf( buffer, "+ LEVEL=%d", model.level );
            file.write(buffer);
        }

        foreach(QString key,model.parameters.keys()){

            ::sprintf( buffer, "+ %s=%f",key.toAscii().data(),model.parameters.value(key).toDouble());
            file.write(buffer);

        }
    }
    file.write( ".options noacct nopage\n" );
    file.flush();
    file.close();

    ::sprintf(buffer,"%s -b %s",spicePath_,filename_);
#ifdef Q_OS_WIN
    FILE* pipe = _popen( buffer, "rb" );
#else
    FILE* pipe = fopen("","rb");
#endif
    if(pipe == NULL){
        TSLog("Couldn't run simulate");
        return false;
    }

    int countValues = prints_.count();
    bool ok;

    result_.clear();

    while( !feof(pipe) ){
        if(fgets( buffer,1024, pipe )){
            QString buf = QString::fromAscii(buffer);
            QStringList values = buf.trimmed().split('\t');
            values.removeFirst();
            if(values.count() == countValues){
                QVector<double> convertValues;
                for( int i=0; i < countValues; i++ ){
                    double value = values.at(i).toDouble(&ok);
                    if(!ok){
                        value = INFINITY;
                    }
                    convertValues.append( value );
                }
                result_.append( convertValues );

            }

        }
    }
#ifdef Q_OS_WIN
    _pclose( pipe );
#else
    fclose( pipe );
#endif

    return true;

}
