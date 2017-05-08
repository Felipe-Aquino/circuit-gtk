#ifndef __POINT_H_
#define __POINT_H_

#include <iostream>
#include <cmath>
#include "Vector.h"

using namespace std;

namespace Math {
    class Vector;
    class Point {
    public:
        float x, y, z;

        Point(float x = 0.0, float y = 0.0, float z = 0.0);
        Point(const Point& p);

        Point& operator=(const Point &p);

        const Point operator+(const Point &p0);
        const Point operator+=(const Point &p0);
        const Point operator-(const Point &p0);
        const Point operator-=(const Point &p0);

        const Point operator+(const Vector &v0);
        const Point operator-(const Vector &v0);

        bool operator==(const Point &p0) const;
        bool operator!=(const Point &p) const;
    
        float distance(Point&);

        void print();
        ~Point();
    };
    int checkPointInLine (Point p1, Point p2, Point pt);
}

#endif