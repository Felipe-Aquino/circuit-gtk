#ifndef __SHAPE_H_
#define __SHAPE_H_

#include <gtkmm/drawingarea.h>
#include <iostream>
#include "../Useful/Color.h"

using namespace std;

namespace Shapes {
    enum class ShapeType {
        CIRCLE, RECTANGLE
    };

    class Shape {
    protected:
        float _x;
        float _y;

        Color _color;
        ShapeType _type;
    public:
        float getX() { return _x; }
        float getY() { return _y; }
        void  setX(float x) { _x = x; }
        void  setY(float y) { _y = y; }

        void color(string c) { Color aux(c); _color = aux; }

        Color color() { return _color; }
        ShapeType getID() { return _type; }

        virtual bool isInside(float x, float y) = 0;
        virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) = 0;
        virtual void print() = 0;

        virtual ~Shape(){}
    };
}

#endif
