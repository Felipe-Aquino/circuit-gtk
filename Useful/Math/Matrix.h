#ifndef __MATRIX_H_
#define __MATRIX_H_

#include <iostream>
#include <exception>
#include <cmath>

using namespace std;

namespace Math {
    class Matrix {
        float** _matrix;
        unsigned _columns, _rows; 
        bool _square;
    public:
        /*
        * Construct a square matrx.
        */
        Matrix(unsigned n);

        /*
        * Construct a matrix of size rows x cols.
        */
        Matrix(unsigned rows, unsigned cols);

        /*
        * Set the value of the element in position (row, col) of the matrix.
        */
        void set(unsigned row, unsigned col, float value);
        
        /*
        * Get value in the position (row, col).
        */
        float get(unsigned row, unsigned col);

        unsigned getRows() { return _rows; }
        unsigned getColumns() { return _columns; }

        /*
        * Retrieve the number of columns of the matrix.
        */
        unsigned getColsNumber();

        /*
        * Retrieve the number of rows of the matrix.
        */
        unsigned getRowsNumber();

        /*
        * Ask whether the matrix is square or not.
        */
        bool isSquare();

        /* Here comes some elementary operations! */

        /*
        * Multiply a row by a constant.
        */
        void multiplyRow(unsigned row, float value);

        /*
        * It places the firt row where is the second one, and vice-versa.
        */
        void swapRows(unsigned row1, unsigned row2);
        
        /*
        * Let M be a arbitrary matrix. This method will sum the row 'r1' and the row 'r2' of M, and put the result in the
        * row 'r1' of M.
        */
        void sumRows(unsigned r1, unsigned r2);

        /*
        * Sum the matrix, wich called this method, with the matrix in the parameter and saves the result in the first matrix. 
        */
        void sumWith(Matrix &m);

        /*
        * Subtract, from the matrix wich called this method, the matrix in the parameter and saves the result in the first matrix. 
        */
        void subWith(Matrix &m);

        /*
        * Trasform the matrix in the identity.
        */
        void identity();

        /*
        * Solving the Equation Ax = b, using the LU method. The matrix x is returned. 
        */
        Matrix luSolving(Matrix& b);

        /*
        * Print the Matrix.
        */
        void print();

        /* Overloading some operations. */

        Matrix& operator=(const Matrix &m);

        const Matrix operator+(const Matrix &m);
        const Matrix operator-(const Matrix &m);
        const Matrix operator*(const Matrix &m);

        bool operator==(const Matrix &m) const;
        bool operator!=(const Matrix &m) const;

        ~Matrix();

    private:
        /*
        * Is used in the method luSolving, and returns the row in which the old pivot must be placed.
        */
        unsigned findNewPivot(unsigned pivot_row);
    };
}

#endif