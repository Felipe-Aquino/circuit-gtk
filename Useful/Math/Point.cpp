#include "Point.h" 

namespace Math {
    
    Point::Point(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point::Point(const Point& p){
        x = p.x;
        y = p.y;
        z = p.z;
    }

    Point& Point::operator=(const Point &p){
        if(this == &p)
			return *this;
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
    }

    const Point Point::operator+(const Point &p0){
        Point p;
        p.x = x + p0.x;
        p.y = y + p0.y;
        p.z = z + p0.z;
        return p; 
    }

    const Point Point::operator+=(const Point &p0){
        *this = *this + p0;
        return *this; 
    }

    const Point Point::operator-(const Point &p0){
        Point p;
        p.x = x - p0.x;
        p.y = y - p0.y;
        p.z = z - p0.z;
        return p;
    }

    const Point Point::operator-=(const Point &p0){
        *this = *this - p0;
        return *this; 
    }

    const Point Point::operator+(const Vector &v0){
        Point p;
        p.x = x + v0.x;
        p.y = y + v0.y;
        p.z = z + v0.z;
        return p; 
    }

    const Point Point::operator-(const Vector &v0){
        Point p;
        p.x = x - v0.x;
        p.y = y - v0.y;
        p.z = z - v0.z;
        return p; 
    }

    bool Point::operator==(const Point &p0) const{
        if(this == &p0) return true;

        return x == p0.x && y == p0.y && z == p0.z;
    }

    bool Point::operator!=(const Point &p) const{
        return !(*this == p);
    }
    
    float Point::distance(Point& p1){
        Point p = *this - p1;
        return sqrt(p.x*p.x + p.y*p.y);
    }

    Point::~Point(){

    }

    int checkPointInLine (Point p1, Point p2, Point pt) { // check if pt is in the line that contains p1 and p2 
        Point p = p1 - p2;                                // if yes then returns 0, if is above return a int < 0 else a int > 0 
        float m = p.y/p.x;
        float y = p1.y + m*(pt.x - p1.x);
        if(!p.x){
            return pt.x - p1.x;
        }

        return y - pt.y;  
    }
};