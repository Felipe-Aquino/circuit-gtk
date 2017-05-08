#include "Rectangle.h"

namespace Shapes {

    Rectangle::Rectangle() : _w(0), _h(0) {
        _color = BLACK;
        _x = 0;
        _y = 0;

        _type = ShapeType::RECTANGLE;
    }

    Rectangle::Rectangle(float x, float y, float w, float h) : _w(w), _h(h) {
        _color = BLACK;
        _x = x;  
        _y = y;

        _type = ShapeType::RECTANGLE;
    }

    Rectangle::Rectangle(Rectangle &r) {
        _x = r._x;
        _y = r._y;
        _w = r._w;
        _h = r._h;
        _color = r._color;
        _type = r._type;
    }

    void Rectangle::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
        Color::setColor(cr, _color);
        cr->rectangle(_x, _y, _w, _h);
        cr->fill();
    }

    void Rectangle::print() {
        cout << "X: " << _x << " Y: " << _y << " W: " << _w << "  H: " << _h << endl;
    }

    bool Rectangle::isInside(float x, float y) {
        if (x >= _x && x <= _x + _w)
            if (y >= _y && y <= _y + _h)
                return true;
        return false;
    }

    void Rectangle::setW(float w) { _w = w; }

    void Rectangle::setH(float h) { _h = h; }

    float Rectangle::getW() { return _w; }

    float Rectangle::getH() { return _h; }

    Rectangle::~Rectangle() {
    }

}