#ifndef __COMPLEX_H_
#define __COMPLEX_H_

#include <iostream>
#include <cmath>

using namespace std;

namespace Math {

    const float pi = 3.1415926;
    const float e  = 2.71828;

    class Complex{
            typedef enum {RECT, POLAR} Format;
            float r, i;
            Format format;
    public:
        Complex(float r = 0.0, float i = 0.0, Format format = RECT);
        Complex(const Complex &n);
        
        void toPolar();
        void toRect();
        
        Complex& operator=(const Complex &n);

        const Complex operator+(const Complex &n0);
        const Complex operator+(float n0);
        const Complex operator+=(const Complex &n0);
        const Complex operator+=(float n0);
        const Complex operator-(const Complex &n0);
        const Complex operator-(float n0);
        const Complex operator-=(const Complex &n0);
        const Complex operator-=(float n0);
        const Complex operator*(const Complex &n0);
        const Complex operator*(float n0);
        const Complex operator*=(const Complex &n0);
        const Complex operator*=(float n0);
        const Complex operator/(const Complex &n0);
        const Complex operator/(float &n0);
        const Complex operator/=(const Complex &n0);
        const Complex operator/=(float n0);
        const Complex operator^(float n0);
        const Complex operator^(Complex n0);  

        bool operator==(const Complex &n0) const;
        bool operator!=(const Complex &n) const;

        Complex toThePower(float n);
        Complex toThePower(Complex n);

        void print();
        ~Complex();
    };

    int sgn(float n);
}

#endif