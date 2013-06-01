#include "minquasinewton.h"
#include "cmatrix.h"


CMatrix &operator +(CMatrix &mat1,CMatrix &mat2){
    CMatrix *matrix = new CMatrix( mat1 );
    matrix->addMatrix( mat2 );
    return *matrix;
}
CMatrix &operator -(CMatrix &mat1,CMatrix &mat2){
    CMatrix *matrix = new CMatrix( mat1 );
    matrix->subMatrix( mat2 );
    return *matrix;
}
CMatrix &operator *(CMatrix &mat1,CMatrix &mat2){
    CMatrix *matrix = new CMatrix( mat1 );
    matrix->mulMatrix( mat2 );
    return *matrix;
}
CMatrix &operator /(CMatrix &mat1,CMatrix &mat2){
    CMatrix *matrix1 = new CMatrix( mat1 );
    CMatrix matrix2(mat2);
    matrix2.inversionMatrix();
    matrix1->mulMatrix( matrix2 );
    return *matrix1;
}
CMatrix &operator *(CMatrix &mat1,QVector<double> &vector){
    CMatrix *matrix = new CMatrix( mat1 );
    matrix->mulMatrix( vector );
    return *matrix;
}
CMatrix &operator *(QVector<double> &vector,CMatrix &mat1){
    CMatrix *matrix = new CMatrix( vector );
    matrix->mulMatrix( mat1 );
    return *matrix;
}
CMatrix &operator *(CMatrix &mat1,double scalar){
    CMatrix *matrix = new CMatrix( mat1 );
    matrix->mulScalar( scalar );
    return *matrix;
}
CMatrix &operator *(double scalar,CMatrix &mat1){
    CMatrix *matrix = new CMatrix( mat1 );
    matrix->mulScalar( scalar );
    return *matrix;
}


MinQuasiNewton::MinQuasiNewton(int id) : Extractor(id)
{
    iteration_ = 0;
    maxIterations_ = 100;
}

void MinQuasiNewton::minimisation(){

    qDebug() << "Start minimisation";

    //    QVector<double> vector_Xk;
    int N = parameterSet()->parameterNames().count();

    CMatrix Ak(N,N),Ak1(N,N),Ak2(N,N),Xk1(N,1),Xk(N,1),  // X[k-1]=Xk X[k]=Xk1
            S(N,1),Grad(N,1),LastGrad(N,1),dX(N,1),dGrad(N,1);


    int num=0;
    foreach(QString _name,parameterSet()->parameterNames()){
        Xk[num][0] = parameterSet()->initial( _name );
        mPrecisions.insert( num, _getPrecisionValue( parameterSet()->min(_name), parameterSet()->max(_name) ) );
        num++;
    }

    //#ifdef _DEBUG_
    //    qDebug() << trUtf8("Начальное значение");
    //    Xk.print_debug();
    //#endif

    Xk1 = Xk;
    QVector<double> cappa;

    Ak1.matrixE( N );

    double h= 1e-6;

    Grad = solveGrad( Xk1, h );

    mFailed = 0;
    iteration_=1;
    stopped_ = false;
    mBaseFunction = computeFunctionError();

    //    LastGrad = Grad;

    while(!isStop()){
        S = -Ak1*Grad;
        Xk = Xk1;


        //        cappa = makeDichotomy(Xk,S,1e-3,1e-5);
        cappa = methodGoldenSection( Xk, S );

        CMatrix _S(S);

        for(int i=0; i < _S.getRows();i++){
            _S[i][0] = S[i][0] * cappa[i];
        }

        Xk1 = Xk + _S;



        LastGrad = Grad;
        Grad = solveGrad( Xk1, h );
        dGrad = Grad - LastGrad;
        dX = Xk1-Xk;

        Ak = Ak1;

        Ak1 =  (Ak*dGrad*CMatrix::transpose(dGrad)*CMatrix::transpose(Ak))
                / (CMatrix::transpose(dGrad)*CMatrix::transpose(Ak)*dGrad);

        Ak1 = Ak - Ak1 + (dX*CMatrix::transpose(dX))/(CMatrix::transpose(dX)*dGrad);



        if(mUltimateFunction == INFINITY){
            qDebug() << "FUCKKKK";
            break;
        }

        if( mBaseFunction > mUltimateFunction ){
            mBaseFunction = mUltimateFunction;

            emit doneIteration( iteration_, mBaseFunction );

            mFailed = 0;
        }else{
            mFailed++;

#ifdef _DEBUG_
            qDebug() << "! FAILED";
            qDebug() << "Base function:" << mBaseFunction;
            qDebug() << "Ultimate function: " << mUltimateFunction;
#endif

            if(mFailed > MAX_FAILED){
                break;
            }

        }


        if(!nextIteration()){
            break;
        }
    }

    emit doneMinimisation();


}

double MinQuasiNewton::dif(QString name, double h){

    //    CMatrix _X = X;
    double tmp,dif;


    if(parameterSet()->fixed( name )){
        return 0.0;
    }
    // save
    double CCV = paramValue( name );

    //    _X[num][0] = X[num][0] + h;

    setParameter( name, CCV + h );
    tmp = computeFunctionError();
    setParameter( name, CCV - h );
    dif = computeFunctionError();

    // restore
    setParameter( name, CCV );

    dif = (tmp - dif)/(2*h);

    return dif;
}

CMatrix &MinQuasiNewton::solveGrad(CMatrix X, double h){

    double _dif,_mod;
    CMatrix *_grads = new CMatrix(X);


    QStringList _list = parameterSet()->parameterNames();

    int noParam = 0, N = _list.count();
    foreach( QString _name, _list ){

        _dif = dif( _name, h);
        _mod += _dif*_dif;

        if( _mod != _mod || _dif != _dif ){
            qDebug() << "NAN";
        }


        _grads->setValue(noParam,0,_dif);

        noParam++;
    }

    _mod = sqrt(_mod);

    for( int i=0; i < N; i++ ){
        _grads->setValue( i, 0, _grads->value(i,0) / _mod );
    }

    return *_grads;

}

QMap<QString, double> MinQuasiNewton::convertMatrixToMap(CMatrix &matrix)
{
    QMap<QString,double> v_qmap; v_qmap.clear();
    if(matrix.getCols() != 1){
        return v_qmap;
    }
    int N = matrix.getRows();
    int i=0;

    QStringList params;
    if(N != params.count()){
        qDebug();
        return v_qmap;
    }
    foreach( QString _param,  params){
        v_qmap.insert( _param, matrix[i][0]  );
        i++;
    }

    return v_qmap;
}

int MinQuasiNewton::numberParameter(QString name){
    QStringList _list = parameterSet()->parameterNames();

    if(!_list.contains( name )){
        return -1;;
    }

    int noParam = 0;

    foreach(QString _name, _list){
        if(_name.compare( name,Qt::CaseInsensitive ) == 0){
            return noParam;
        }

        noParam++;
    }

    return -1;

}

QString MinQuasiNewton::nameParameter(int num){
    QStringList _list = parameterSet()->parameterNames();
    QString _name("");

    if(num >= _list.count() ){
        return QString("");
    }

    return _list.at( num );
}

QVector<double> MinQuasiNewton::makeDichotomy(CMatrix Xk, CMatrix Sk, double eps, double prec){
    //x(k+1) = x(k) + α(k)⋅s(k)
    //s(k) = -A(k)⋅∇ƒ(X(k))
    QVector<double> _vec, _vec_cappa1,_vec_cappa2,a,b;

    CMatrix Xk1 = Xk;
    double cappa_k1,cappa_k2,fa,fb,fc,fd;

    QMap<QString,double> _savedParameters;


    int N = parameterSet()->parameterNames().count();


    a.resize( parameterSet()->parameterNames().count() );
    b.resize( parameterSet()->parameterNames().count() );


    int _num=0;
    QVector<bool> _skips;
    int _skipped = 0;
    foreach( QString _name, parameterSet()->parameterNames() ){
        if(_num == 12){
            qDebug() << "ss";
        }
        if(!parameterSet()->fixed(_name)){
            a[_num] = parameterSet()->min( _name );
            b[_num] = parameterSet()->max( _name );

            qDebug() << _num << "; " << parameterSet()->min( _name ) << ":" << parameterSet()->max( _name );
            _skips.insert( _num, false );

            _vec_cappa1.insert(_num,0.0);
            _vec_cappa2.insert(_num,0.0);

        }else{
            a[_num] = parameterSet()->initial(_name);
            b[_num] = parameterSet()->initial(_name);
            _skips.insert( _num, true );
            _skipped++;
            _vec_cappa1.insert(_num,parameterSet()->initial(_name));
            _vec_cappa2.insert(_num,parameterSet()->initial(_name));
        }


        _num++;
    }


    _savedParameters = getParameters();

    QStringList _li;
    foreach( double _var, a){
        _li << QString::number(_var);
    }
    qDebug() << _li.join(", ");

    setParameters( a  );
    fa = computeFunctionError();

    setParameters(  b );
    fb = computeFunctionError();

    if(fa == fb){
        qDebug() << "ff";
    }



    //    while(_skipped != _skips.count()){
    for(int _c=0; _c <= 5; _c++){
        for(int i=0; i < N; i++){
            if(_skips.at(i)){
                //                _vec_cappa1[] i, 0.0 );
                continue;
            }
            QString _name = nameParameter(i);

            double _a = a.at(i),
                    _b = b.at(i),
                    _tmp = 0.0;

            if((_b - _a) < precision(i)){
                _skips[i] = true;
                _skipped++;

                _vec_cappa1[i] = (_a+_b)/2 ;
                continue;
            }
            _tmp = (_a+_b)/2-precision(i)/100;
            _vec_cappa1[i] = _tmp;

            _tmp = Xk[i][0]+Sk[i][0]*_tmp;

            setParameter( _name, _tmp );

        }

        fc = computeFunctionError();


        for(int i=0; i < N; i++){
            if(_skips.at(i)){
                //                _vec_cappa2.insert( i, 0.0 );
                continue;
            }
            QString _name = nameParameter(i);

            double _a = a.at(i),
                    _b = b.at(i),
                    _tmp = 0.0;

            if((_b - _a) < precision(i)){
                _skips[i] = true;
                _skipped++;
                continue;
            }
            _tmp = (_a+_b)/2+precision(i)/100;
            _vec_cappa2[i] = _tmp;

            _tmp = Xk[i][0]+Sk[i][0]*_tmp;

            setParameter( _name, _tmp );

        }

        fd = computeFunctionError();

        if(fc < fd){
            b = _vec_cappa2;
        }else{
            a = _vec_cappa1;
        }

    }

    for(int i=0; i < N; i++){
        _vec.insert( i, (a.at(i)+b.at(i))/2 );
    }
    //    for(int i=0; i < N; i++){
    //        QString _name = nameParameter(i);

    //        if(parameterSet()->fixed(_name)){
    //            continue;
    //        }



    //        while((_b -_a) > eps){
    //            cappa_k1 = (_a+_b)/2-prec;
    //            cappa_k2 = (_a+_b)/2+prec;


    //            Xk1[i][0] = Xk[i][0] + Sk[i][0]*cappa_k1;
    //            setParameter( _name , Xk1[i][0] );
    //            Xk1[i][0] = param(_name);

    //            fc = functionError();
    //            Xk1[i][0] = Xk[i][0] + Sk[i][0]*cappa_k2;
    //            setParameter( _name , Xk1[i][0] );
    //            Xk1[i][0] = param(_name);

    //            fd = functionError();


    //            if(fc < fd){
    //                _b = cappa_k2;
    //            }else{
    //                _a = cappa_k1;
    //            }

    //        }

    //        _vec.insert( i, (_a+_b)/2 );
    //    }


    parameterSet()->setValue( _savedParameters );

    return _vec;

}

QVector<double> MinQuasiNewton::methodGoldenSection(CMatrix Xk, CMatrix Sk){

    int N = parameterSet()->parameterNames().count();
    QMap<QString,double> _savedParameters;
    QVector<double> _vecA(N), _vecB(N), _vecCappa(N),_vecH(N),_vecG(N);
    double fu1,fu2;

    int num = 0;
    // intialize;

    foreach(QString _name, parameterSet()->parameterNames()){
        if(!parameterSet()->fixed(_name)){
            _vecA[num] = parameterSet()->min( _name );
            _vecB[num] = parameterSet()->max( _name );

            if(_vecB[num] - _vecA[num] < 0){
                qDebug() << "Error int B-A <0";
            }

        }else{
            _vecA[num] = parameterSet()->initial( _name );
            _vecB[num] = parameterSet()->initial( _name );
        }
        num++;
    }

    for(int i=0; i < N; i++ ){
        _vecG[i] = _vecA[i] + ((3-sqrt(double(5)))/2) * (_vecB[i] - _vecA[i]);
        _vecH[i] = _vecB[i] - ((sqrt(double(5))-1)/2) * (_vecB[i] - _vecA[i]);
    }

    _savedParameters = getParameters();

    for(int i=0; i < N; i++ ){
        setParameter(  nameParameter(i),  Xk[i][0] + Sk[i][0]*_vecG[i] );
    }
    fu1 = computeFunctionError();

    for(int i=0; i < N; i++ ){
        setParameter(  nameParameter(i),  Xk[i][0] + Sk[i][0]*_vecH[i] );
    }
    fu2 = computeFunctionError();
    int k=0;
    while(true){
        k++;
        if(fu1 <= fu2){
            _vecB = _vecH;
            _vecH = _vecG;
            fu2 = fu1;
            for(int i=0; i < N; i++ ){
                _vecG[i] = _vecA[i] + (_vecB[i] - _vecA[i])*((3-sqrt(double(5)))/2);
                setParameter( nameParameter(i), Xk[i][0] + Sk[i][0]*_vecG[i] );
            }

            //            setParameters( _vecG );
            fu1 = computeFunctionError();

        }else{
            _vecA = _vecG;
            _vecG = _vecH;
            fu1 = fu2;
            for(int i=0; i < N; i++ ){
                _vecH[i] = _vecB[i] - (_vecB[i] - _vecA[i])*((sqrt(double(5))-1)/2);
                setParameter( nameParameter(i), Xk[i][0] + Sk[i][0]*_vecH[i] );
            }
            //            setParameters( _vecH );
            fu2 = computeFunctionError();
        }

        // check out cycle
        int N_eps = 0;
        for(int i=0; i < N; i++ ){

            if(fabs(_vecB[i] -_vecA[i]) < precision(i) || _vecB[i] == _vecA[i] ){
                N_eps++;
            }
        }
        if(N_eps == N){
            break;
        }

    }

    QMap<QString,double> _parameters;

    for(int i=0; i < N; i++ ){
        _vecCappa[i] = (_vecA[i] + _vecB[i])/2.0;
        _parameters.insert( nameParameter(i), _vecCappa[i] );
    }


    lastParameters_ = _parameters;
    mUltimateFunction = (fu1-fu2)/2 +fu2;

    qDebug() << "Min:" << mUltimateFunction;
    qDebug() << "Golden section K=" << k;
    return _vecCappa;

}

QVector<double> MinQuasiNewton::methodPowell(CMatrix Xk, CMatrix Sk){

    int N = parameterSet()->parameterNames().count();

    QVector<double> _steps(N),X1(N),X2(N),X3(N),Xmin(N);
    for(int i=0; i < N; i++){


        if(parameterSet()->fixed( nameParameter(i) )){
            _steps[i] = 0.0;
        }else{
            _steps[i] = precision(i);
        }

        X1[i] = Xk[i][0];
        X2[i] = X1[i] + _steps[i];
    }

    double f1=0.0,f2=0.0,f3=0.0,Fmin=0.0;

    f1 = funcMinimisation( Xk, Sk, X1 );
    f2 = funcMinimisation( Xk, Sk, X2 );

    for(int i=0; i < N; i++){
        if(f1 > f2){
            X3[i] = X1[i]+2*_steps[i];
        }else{
            X3[i] = X1[i]-_steps[i];
        }
    }

    f3 = funcMinimisation( Xk,Sk, X3 );

    Fmin = f1;
    Xmin = X1;

//    if(f1)

    return Xmin;
}

double MinQuasiNewton::funcMinimisation(CMatrix Xk, CMatrix Sk, QVector<double> cappa){
    QMap<QString,double> _savedParameters = getParameters();

    int N = _savedParameters.count();

    double _tmp =0.0, _func = 0.0;

    for(int i=0; i < N; i++){
        _tmp = Xk[i][0] + Sk[i][0]*cappa[i];
        setParameter( nameParameter(i), _tmp );
    }

    _func = computeFunctionError();

    parameterSet()->setValue( _savedParameters );

    return _func;
}

QMap<QString, double> MinQuasiNewton::getParameters(){

    QMap<QString,double> _params;

    QStringList _list = parameterSet()->parameterNames();
    foreach(QString _name,_list){
        _params.insert( _name, paramValue( _name ) );
    }

    return _params;
}

CMatrix &MinQuasiNewton::getParametersMatrix(){

    QStringList _list = parameterSet()->parameterNames();
    int N = _list.count();

    CMatrix *_matrix = new CMatrix(N,1);
    int i=0;
    foreach( QString _name, _list ){
        _matrix->setValue(i,0,paramValue(_name));
    }

    return *_matrix;

}

void MinQuasiNewton::setParameters(CMatrix matrixParameters){

    int N = matrixParameters.getRows();

    for(int i=0; i < N;i++){
        setParameter( nameParameter( i ), matrixParameters[i][0]  );
    }

    return;

}

void MinQuasiNewton::setParameters(QVector<double> parameters){
    int N = parameters.count();

    for(int i=0; i < N;i++){
        setParameter( nameParameter( i ), parameters.at(i) );
    }

}

double MinQuasiNewton::_getPrecisionValue(double min, double max){
    double _prec = 0.1;
    double _val = (min+max)/2;
    _prec = _val/1000;
    return _prec;
}




