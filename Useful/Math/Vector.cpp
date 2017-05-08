#include "Vector.h" 

namespace Math {
    
    Vector::Vector(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector::Vector(const Vector& v){
        x = v.x;
        y = v.y;
        z = v.z;
    }

    Vector::Vector(Point p0,  Point p1){
        Point p = p1 - p0;
        x = p.x;
        y = p.y;
        z = p.z;
    }

    Vector& Vector::operator=(const Vector &v){
        if(this == &v)
			return *this;
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
    }

    const Vector Vector::operator+(const Vector &v0){
        Vector v;
        v.x = x + v0.x;
        v.y = y + v0.y;
        v.z = z + v0.z;
        return v; 
    }

    const Vector Vector::operator+=(const Vector &v0){
        *this = *this + v0;
        return *this; 
    }

    const Vector Vector::operator-(const Vector &v0){
        Vector v;
        v.x = x - v0.x;
        v.y = y - v0.y;
        v.z = z - v0.z;
        return v;
    }

    const Vector Vector::operator-=(const Vector &v0){
        *this = *this - v0;
        return *this; 
    }

    float Vector::operator*(const Vector &v0){
        return dotProduct(v0);
    }
    
    const Vector Vector::operator^(const Vector &v0){
        return crossProduct(v0);
    }

    bool Vector::operator==(const Vector &v0) const{
        if(this == &v0) return true;

        return x == v0.x && y == v0.y && z == v0.z;
    }

    bool Vector::operator!=(const Vector &v) const{
        return !(*this == v);
    }

    float Vector::dotProduct(Vector v){
        return x*v.x + y*v.y + z*v.z;
    }

    Vector Vector::crossProduct(Vector v){
        Vector v1;
        v1.x = y*v.z - v.y*z;
        v1.y = v.x*z - x*v.z;
        v1.z = x*v.y - v.x*y;
        return v1; 
    }

    float Vector::norm(){
        return sqrt(x*x + y*y + z*z);
    }

    void Vector::normalize(){
        float n = norm();
        x /= n;
        y /= n;
        z /= n;
    }

    void Vector::scale(float n){
        x *= n;
        y *= n;
        z *= n;
    }

    void Vector::rotate(Vector axis, float angle){
        axis.normalize();
        float c = cos(angle), s = sin(angle);
        float p = (axis.x*x + axis.y*y + axis.z*z)*(1 - c);
        Vector n = *this ^ axis;
        n.scale(-1);

        x = axis.x*p + x*c + n.x*s;
        y = axis.y*p + y*c + n.y*s;
        z = axis.z*p + z*c + n.z*s;  
    }

    void Vector::print(){
        cout << "(" << x << "," << y << "," << z << ")";
    }
    
    Vector::~Vector(){

    }
}