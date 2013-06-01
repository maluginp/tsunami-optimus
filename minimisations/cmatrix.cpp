#include "cmatrix.h"

CMatrix::CMatrix(){
    mRows = 0;
    mCols = 0;
}

CMatrix::CMatrix(int rows, int cols){
    mRows = rows;
    mCols = cols;
    initMatrix( rows,cols );

}
CMatrix::CMatrix(CMatrix &matrix){
    setMatrix(matrix);
}
CMatrix::CMatrix(QVector<double> &vector){
    mRows = 1;
    mCols = vector.count();

    initMatrix( mRows, mCols );

    for(int j=0; j < mCols; j++){
        Matrix[0][j] = vector[j];
    }
}

bool CMatrix::addMatrix(CMatrix mat){
    // check condition
    if( getRows() != mat.getRows()  ){
        mError = QString("No eq rows");
        return false;
    }
    if( getCols() != mat.getCols() ){
        mError = QString("No eq cols");
        return false;
    }


    for(int m=0; m < mRows; m++){
        for(int n=0;n< mCols;n++){
            Matrix[m][n] = Matrix[m][n]+mat[m][n];
        }
    }

    return true;
}
void CMatrix::mulScalar(const double scalar){
    for(int m=0; m < mRows; m++){
        for(int n=0;n< mCols;n++){
            Matrix[m][n] = Matrix[m][n]*scalar;
        }
    }
    return;
}
void CMatrix::mulMatrix(QVector<double> &vector){
    CMatrix vectMatrix(vector);
    mulMatrix( vectMatrix );
}
void CMatrix::mulMatrix(CMatrix &mat){
    if(mat.getCols() == 1 && mat.getRows() == 1){
        mulScalar( mat[0][0] );

        return;
    }
    if(getCols() == 1 && getRows() == 1){
        double scalar = Matrix[0][0];
        setMatrix(mat);

        mulScalar( scalar );
        return;

    }

    if(getCols() != mat.getRows()){
        mError = QString("@mulMatrix: cols and rows no eq");
        return;
    }
    int M = getRows(), N = mat.getCols(), R = mat.getRows();
    CMatrix matrix( M,N );


    double c;
    QVector<double> _vector;
    for(int i=0; i < M; i++){
        _vector.clear();
        for(int j=0; j < N; j++){
            c = 0.0;
            for(int r=0; r<R;r++){
                c += Matrix[i][r]*mat[r].at(j);
            }

            _vector.append( c  );
        }

        matrix.setRow( i, _vector );
    }
    setMatrix(matrix);
}
CMatrix &CMatrix::transpose(){
    int M = getRows(), N = getCols();
    CMatrix matrix(N,M);

    for( int i=0; i < M;i++ ){
        for(int j=0; j < N; j++){
            matrix.setValue(j,i, Matrix[i][j]);
        }
    }

    setMatrix(matrix);
    return *this;
}
void CMatrix::initMatrix(int rows, int cols){
    Matrix.clear();
    QVector<double> _vector;
    for(int i=0; i < rows;i++){
        _vector.clear();
        for(int j=0; j < cols; j++){
            _vector.append(0.0);
        }
        Matrix.insert(i,_vector);
    }
}
void CMatrix::setMatrix(CMatrix &matrix){
    int M = matrix.getRows(), N = matrix.getCols();

    initMatrix( M,N );
    for( int i=0; i < M;i++ ){
        for(int j=0; j < N; j++){
            setValue( i,j, matrix[i][j] );
        }
    }

    mRows = M;
    mCols = N;
}
CMatrix &CMatrix::transpose(CMatrix &mat){
    int M = mat.getRows(), N = mat.getCols();

    CMatrix *matrix = new CMatrix(N,M);

    for( int i=0; i < M;i++ ){
        for(int j=0; j < N; j++){
            matrix->setValue(j,i, mat[i][j]);
        }
    }

    return *matrix;
}
void CMatrix::setValue(const int row, const int col, const double value){
    Matrix[row][col] = value;
    return;
}

double CMatrix::value(const int row, const int col)
{
    return Matrix[row][col];
}
void CMatrix::inversionMatrix(){
    double temp;
    if(getRows() != getCols()){
        return;
    }
    int N = getRows();
    CMatrix E;
    E.matrixE(N);
    for (int k = 0; k < N; k++){
        temp = Matrix[k][k];
        for (int j = 0; j < N; j++){
            Matrix[k][j] /= temp;
            E[k][j] /= temp;
        }
        for (int i = k + 1; i < N; i++){
            temp = Matrix[i][k];
            for (int j = 0; j < N; j++){
                Matrix[i][j] -= Matrix[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = N - 1; k > 0; k--){
        for (int i = k - 1; i >= 0; i--){
            temp = Matrix[i][k];

            for (int j = 0; j < N; j++){
                Matrix[i][j] -= Matrix[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            Matrix[i][j] = E[i][j];
        }
    }

    return;
}
bool CMatrix::subMatrix(CMatrix &mat){
    CMatrix _mat(mat);
    _mat.mulScalar(-1.0);
    return addMatrix( _mat  );
}
void CMatrix::matrixE(int count){
    CMatrix matrix(count,count);
    QVector<double> _mat;
    for(int i=0; i < count;i++){
        _mat.clear();
        for(int j=0; j < count;j++){
            if(i==j){
                _mat.append( 1.0 );
            }else{
                _mat.append( 0.0 );
            }

        }
        matrix.setRow( i, _mat );
    }

    setMatrix(matrix);
}

void CMatrix::setRow(int col, QVector<double> row){
    if(Matrix.contains(col)){
        Matrix[col] = row;
    }else{
        Matrix.insert( col, row );
    }
}

void CMatrix::print_debug(){
    qDebug() << "Print matrix:";
    int M = mRows, N = mCols;
    QString row;
    for(int i=0; i < M;i++){
        row = "";
        for(int j=0; j < N; j++){
            row += QString::number(Matrix[i][j])+QString("\t");
        }
        qDebug() << QString("[%1] %2").arg(i).arg(row);
    }
}

