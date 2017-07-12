#include "Matrix.h"
#include <sstream>
#include <string>

class MatrixOperationException : public exception {
    string message;
public:
    MatrixOperationException(const char* msg): message(msg){ };
    MatrixOperationException(string msg): message(msg){ };
    virtual const char* what() const throw(){
        return message.c_str();
    }
    ~MatrixOperationException(){};
};

namespace Math {
    Matrix::Matrix(unsigned n){
        _matrix = new float*[n];
        for(int i = 0; i < n; i++)
            _matrix[i] = new float[n];
        _rows = n;
        _columns = n;
        _square = true;

        for(int i = 0; i < _rows; i++){
            for(int j = 0; j < _columns; j++)
                _matrix[i][j] = 0.0;
        }
    }

    Matrix::Matrix(unsigned rows, unsigned cols){
        _matrix = new float*[rows];
        for(int i = 0; i < rows; i++)
            _matrix[i] = new float[cols];
        _rows = rows;
        _columns = cols;
        _square = false;
        if(rows == cols) _square = true;
        
        for(int i = 0; i < _rows; i++){
            for(int j = 0; j < _columns; j++)
                _matrix[i][j] = 0.0;
        }
    }

    void Matrix::set(unsigned row, unsigned col, float value){
        _matrix[row][col] = value;
    }

    float Matrix::get(unsigned row, unsigned col){
        return _matrix[row][col];
    }

    unsigned Matrix::getColsNumber() { return _columns; }
    unsigned Matrix::getRowsNumber() { return _rows; }
    bool Matrix::isSquare() { return _square; }

    void Matrix::multiplyRow(unsigned row, float value){
        if(row >= _rows){
            stringstream  msg;
            msg << "Trying access the row " << row << " in a matrix of size " << _rows << "x" <<_columns; 
            throw MatrixOperationException(msg.str());
        }

        for(int i = 0; i < _columns; i++)
            _matrix[row][i] *= value; 
    }
   
    void Matrix::swapRows(unsigned row1, unsigned row2){
        if(row1 >= _rows || row2 >= _rows){
            unsigned row = row1 >= _rows ? row1 : row2;  
            stringstream  msg;
            msg << "Trying access the row " << row << " in a matrix of size " << _rows << "x" <<_columns; 
            throw MatrixOperationException(msg.str());
        }

        for(int i = 0; i < _columns; i++) {
            float r = _matrix[row1][i];
            _matrix[row1][i] = _matrix[row2][i];
            _matrix[row2][i] = r;
        }

    }
    
    void Matrix::sumRows(unsigned row1, unsigned row2){
        if(row1 >= _rows || row2 >= _rows){
            unsigned row = row1 >= _rows ? row1 : row2;  
            stringstream  msg;
            msg << "Trying access the row " << row << " in a matrix of size " << _rows << "x" <<_columns; 
            throw MatrixOperationException(msg.str());
        }

        for(int i = 0; i < _columns; i++)
            _matrix[row1][i] += _matrix[row2][i];
    }

    void Matrix::sumWith(Matrix &m){
        if(_columns != m._columns || _rows != m._rows)
            throw MatrixOperationException("In the attempt of add Matrices: the sizes don't match!");
        
        
        for(int i = 0; i < _rows; i++)
            for(int j = 0; j < _columns; j++)
                _matrix[i][j] += m._matrix[i][j];
    }

    void Matrix::subWith(Matrix &m){
        if(_columns != m._columns || _rows != m._rows)
            throw MatrixOperationException("In the attempt of add Matrices: the sizes don't match!");
        
        
        for(int i = 0; i < _rows; i++)
            for(int j = 0; j < _columns; j++)
                _matrix[i][j] -= m._matrix[i][j];
    }

    void Matrix::identity(){
        if(!_square) return;

        for(int i = 0; i < _rows; i++)
            for(int j = 0; j < _columns; j++)
                _matrix[i][j] = (float)(i == j);
    }

    /* 
    * Below are the steps to solve (but is missing the pivoting):
    * step 1: Ax = b   -> LUx = b 
    * step 2: LUx = b  -> Ux = y and Ly = b 
    * step 3: solve Ly = b, finding y 
    * step 4: solve Ux = y, finding x 
    */
    Matrix Matrix::luSolving(Matrix& b){
        if(_rows != b._rows)
            throw MatrixOperationException("In the attempt of luSolving: the sizes don't match!");

        Matrix L(_rows);
        Matrix U(_rows);
        U = *this;

        /* Finding the L and U matrices with pivoting */
        for(int pivot = 0; pivot < _rows-1; pivot++){
            unsigned p = U.findNewPivot(pivot);
            if(p != pivot){ 
                U.swapRows(p, pivot);
                L.swapRows(p, pivot);
                b.swapRows(p, pivot);
            }

            for(int i = pivot + 1; i < _rows; i++){
                float m = -U._matrix[i][pivot]/U._matrix[pivot][pivot];
                L._matrix[i][pivot] = -m;
                for(int j = 0; j < _columns; j++){
                    U._matrix[i][j] = U._matrix[i][j] + m*U._matrix[pivot][j];      
                }
            }
        }
        for(int i = 0; i < _rows; i++)
            L._matrix[i][i] = 1.0;

        Matrix x(b._rows, 1);
        Matrix y(b._rows, 1);
        float sum = 0;
        
        /* Solving Ly = b*/
        for(int i = 0; i < _rows; i++){
            sum = 0;
            for(int j = 0; j < i; j++){
                sum += y._matrix[j][0]*L._matrix[i][j];
            }
            y._matrix[i][0] = (b._matrix[i][0] - sum)/L._matrix[i][i];
        }

        /* Solving Ux = y*/
        for(int i = _rows-1; i >= 0; i--){
            sum = 0;
            for(int j = i+1; j < _rows; j++){
                sum += x._matrix[j][0]*U._matrix[i][j];
            }
            x._matrix[i][0] = (y._matrix[i][0] - sum)/U._matrix[i][i];
        }

        return x;
    }

    unsigned Matrix::findNewPivot(unsigned pivot_row){
        float max_pivot = 0;
        unsigned new_pivot = pivot_row;

        for(int i = pivot_row; i < _rows; i++){
            if(fabs(_matrix[i][pivot_row]) > max_pivot){
                new_pivot = i;
                max_pivot = abs(_matrix[i][pivot_row]);
            }
        }
        return new_pivot;
    }

    void Matrix::print(){
        for(int i = 0; i < _rows; i++){
            for(int j = 0; j < _columns; j++)
                cout << " " << _matrix[i][j];
            cout << endl;
        }
        cout << endl;
    }

    void Matrix::copy(Matrix& m){
        if(_columns != m._columns || _rows != m._rows)
            throw MatrixOperationException("The size of the matrices doesn't match!");

        for(int i = 0; i < _rows; i++)
            for(int j = 0; j < _columns; j++)
                _matrix[i][j] = m._matrix[i][j];
    }

    Matrix& Matrix::operator=(const Matrix &m){
        if(_columns != m._columns || _rows != m._rows)
            throw MatrixOperationException("The size of the matrices doesn't match!");

        for(int i = 0; i < _rows; i++)
            for(int j = 0; j < _columns; j++)
                _matrix[i][j] = m._matrix[i][j];
        
        return *this;
    }

    const Matrix Matrix::operator+(const Matrix &m) {
        if(_columns != m._columns || _rows != m._rows)
            throw MatrixOperationException("In the attempt of add Matrices: the sizes don't match!");
        
        Matrix m0(_rows, _columns);
        for(int i = 0; i < _rows; i++)
            for(int j = 0; j < _columns; j++)
                m0._matrix[i][j] = _matrix[i][j] + m._matrix[i][j];
        
        return m0;
    }

    const Matrix Matrix::operator-(const Matrix &m) {
        if(_columns != m._columns || _rows != m._rows)
            throw MatrixOperationException("In the attempt of subtract Matrices: the sizes don't match!");
        
        Matrix m0(_rows, _columns);
        for(int i = 0; i < _rows; i++)
            for(int j = 0; j < _columns; j++)
                m0._matrix[i][j] = _matrix[i][j] - m._matrix[i][j];
        
        return m0;
    }

    const Matrix Matrix::operator*(const Matrix &m) {
        if(_columns != m._rows)
            throw MatrixOperationException("In the attempt of multiply Matrices: the number of columns of the first must be equal to the number of rows of the Second one!");
        
        Matrix m0(_rows, m._columns);
        for(int i = 0; i < _rows; i++)
            for(int j = 0; j < m._columns; j++){
                m0._matrix[i][j] = 0.0;
                for(int k = 0; k < _columns; k++)
                    m0._matrix[i][j] += _matrix[i][k]*m._matrix[k][j]; 
            }
        return m0;
    }

    bool Matrix::operator==(const Matrix &m) const {
        if(this == &m)
			return true;

        if(_columns != m._columns || _rows != m._rows)
            throw MatrixOperationException("In the attempt of equality Matrices: the sizes don't match!");
        
        bool equal = true;
        for(int i = 0; i < _rows; i++)
            for(int j = 0; j < _columns; j++)
                equal &= _matrix[i][j] == m._matrix[i][j];
        
        return equal;
    }

    bool Matrix::operator!=(const Matrix &m) const {
        return !(*this == m);
    }

    Matrix::~Matrix(){
        for(int i = 0; i < _rows; i++)
            delete[] _matrix[i];
        delete[] _matrix;
    }
}