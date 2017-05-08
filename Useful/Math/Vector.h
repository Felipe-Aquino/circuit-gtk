#ifndef __VECTOR_H_
#define __VECTOR_H_

#include <iostream>
#include <cmath>
#include "Point.h"

using namespace std;

namespace Math {
    class Point;
    class Vector {
    public:
        float x, y, z;

        Vector(float x = 0.0, float y = 0.0, float z = 0.0);
        Vector(const Vector& v);
        Vector(Point p0,  Point p1);

        Vector& operator=(const Vector &v);

        const Vector operator+(const Vector &v0);
        const Vector operator+=(const Vector &v0);
        const Vector operator-(const Vector &v0);
        const Vector operator-=(const Vector &v0);
        float operator*(const Vector &v0);
        const Vector operator^(const Vector &v0); 

        bool operator==(const Vector &v0) const;
        bool operator!=(const Vector &v) const;
    
        float dotProduct(Vector v);
        Vector crossProduct(Vector v);
        float norm();
        void normalize();
        void scale(float n);
        void rotate(Vector axis, float angle);

        void print();
        ~Vector();
    };
}

#endif