#ifndef __SHAPE_H_
#define __SHAPE_H_

#include <iostream>
#include "../Useful/Color.h"

using namespace std;
using namespace Color;

namespace Shapes {
    typedef enum class shapeType {
        CIRCLE, RECTANGLE
    } ShapeType;

    class Shape {
    protected:
        float _x;
        float _y;
        
        TColor _color;
        ShapeType _type;
    public:
        float getX() { return _x; }
        float getY() { return _y; }
        void  setX(float x) { _x = x; }
        void  setY(float y) { _y = y; }

        void setColor(TColor color) { _color = color; }
        TColor getColor()  { return _color; }
        ShapeType getID() { return _type; }

        virtual bool isInside(float x, float y) = 0;
        virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) = 0;
        virtual void print() = 0;

        virtual ~Shape(){}
    };

}

#endif