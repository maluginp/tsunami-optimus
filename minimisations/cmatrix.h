#ifndef CMATRIX_H
#define CMATRIX_H
#include <QtCore>



class CMatrix{
public:
    CMatrix(int rows,int cols );
    CMatrix(CMatrix &matrix);
    CMatrix(QVector<double> &vector);
    CMatrix();

    bool addMatrix(CMatrix mat );
    void mulScalar(const double scalar);
    void mulMatrix(QVector<double> &vector);
    void mulMatrix(CMatrix &mat);

//    static CMatrix mulMatrix(const CMatrix mat1,const CMatrix mat2){
//        if(mat1.getCols() != mat2.getRows()){
//            mError = QString("@mulMatrix: cols and rows no eq");
//            return CMatrix();
//        }
//        int M = mat1.getRows(), N = mat2.getCols(), R = mat1.getCols();
//        CMatrix matrix( M,N );


//        double c;
//        QVector<double> _vector;
//        for(int i=0; i < M; i++){
//            _vector.clear();
//            for(int j=0; j < N; j++){
//                c = 0.0;
//                for(int r=0; r<R;r++){
//                    c += mat1[i][r]*mat[r][j];
//                }

//                _vector.append( c  );
//            }

//            matrix.setRow( i, _vector );
//        }
//        return matrix;
//    }

    CMatrix &transpose( );
    void initMatrix(int rows,int cols);
    void setMatrix(CMatrix &matrix);

    static CMatrix &transpose(CMatrix &mat );
    void setValue( const int row, const int col, const double value );
    double value(const int row, const int col);
    void inversionMatrix();
    bool subMatrix(CMatrix &mat );
    void matrixE(int count);
    void setRow( int col, QVector<double> row );
    int getRows() { return mRows; }
    int getCols() { return mCols; }


    CMatrix &operator +=(CMatrix &mat){
        addMatrix( mat );
        return *this;
    }
    CMatrix &operator -(){
        CMatrix *matrix =new CMatrix( *this );
        matrix->mulScalar( -1.0 );
        return *matrix;
    }

    CMatrix &operator -=(CMatrix &mat){
        subMatrix( mat );
        return *this;
    }
    CMatrix &operator *=(const double scalar){
        mulScalar( scalar );
        return *this;
    }
    CMatrix &operator *=(CMatrix &mat){
        mulMatrix( mat );
        return *this;
    }
    CMatrix &operator=(CMatrix &mat){
        setMatrix(mat);
        return *this;
    }

    QVector<double> &operator[](int i){
        return Matrix[i];
    }

    void print_debug();

private:
    int mCols;
    int mRows;

    QMap<int, QVector<double> > Matrix;

    QString mError;

};




#endif // CMATRIX_H
