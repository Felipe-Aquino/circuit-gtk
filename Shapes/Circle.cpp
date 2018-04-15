#include "Circle.h"

namespace Shapes {
    Circle::Circle(): _r(0) {
        _x = 0;
        _y = 0;

        _type = ShapeType::CIRCLE;
    }

    Circle::Circle(float x, float y, float r) {
        _x = x;
        _y = y;
        _r = r;

        _color.set(0, 0, 1);
        _type = ShapeType::CIRCLE;
    }

    Circle::Circle(Circle &c) {
        _x = c._x;
        _y = c._y;
        _r = c._r;
        _color = c._color;
        _type = c._type;
    }

    void Circle::incCenter(float dx, float dy) {
        _x += dx;
        _y += dy;
    }

    float Circle::getRadius() { return _r; }

    void Circle::setRadius(float r) { _r = r; }

    bool Circle::isInside(float x, float y){
        float dx = x - _x;
        float dy = y - _y;
        return sqrt(dx*dx - dy*dy) <= _r;
    }

    void Circle::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
        const float two_pi = 2 * 3.1415926;

        cr->set_source_rgb(_color.r(), _color.g(), _color.b());
        cr->arc(_x, _y, _r, 0, two_pi);
        cr->fill();
    }

    void Circle::drawCircunference(const Cairo::RefPtr<Cairo::Context>& cr) {
        const float two_pi = 2 * 3.1415926;

        cr->set_source_rgb(_color.r(), _color.g(), _color.b());
        cr->arc(_x, _y, _r, 0, two_pi);
        cr->stroke();
    }

    void Circle::print() {
        cout << "x: " << _x << " y: " << _y << " r: " << _r << endl;
        cout << _color << endl;
    }

    Circle::~Circle() {
    }
};
