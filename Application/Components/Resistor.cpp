#include "Resistor.h"
#include <functional>
#include <string>
#include "../../Useful/report.h"
#include "../../Useful/fast_gui.h"

using namespace Primitive;

Resistor::Resistor(int x, int y) {
    _id = Cid::RESISTOR;
    _ready = false;
    _delete = false;
    _drawMenu = false;
    _resistance = 100.0;
    try {
        _nodes = _shape.readFromSvg("./SVGs/resistor.svg");
        _shape.setXY(x, y);
    } catch(exception& e){
        report::exception(e.what());
        exit(1);
    }

    info.name = "Resistor";
    Property* property = new Property("resistance", new Float(_resistance));
    property->onChange.connect_member(this, &Resistor::PropertyChanged);
    info.properties.push_back(property);
}

void Resistor::Draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    _shape.draw(cr);

    fst::BeginExpander("resistor");
    fst::Text("resitance: ");
    fst::SameLine();
    fst::Slider(_resistance, 50, 500);
    fst::Text(report::format("voltage: %", _voltage));
    fst::Text(report::format("current: %", _current));

    fst::BeginExpander("container");
    fst::Text(report::format("x: %", _shape.getX()));
    fst::Text(report::format("y: %", _shape.getY()));
    fst::EndExpander();

    fst::BeginExpander("nodes number");
    fst::Text(report::format("0: %", _nodes[0]->info->number));
    fst::Text(report::format("1: %", _nodes[1]->info->number));
    fst::EndExpander();

    fst::EndExpander();
}

bool Resistor::IsReady() {
    return _ready;
}

void Resistor::UpdateProperties(Matrix& x) {
    _voltage = _nodes[0]->info->voltage - _nodes[1]->info->voltage;
    _current = _voltage/_resistance;
}

void Resistor::MouseOverEvent(int x, int y) {
    if(!_ready){
        _shape.setXY(x, y);
    }
}

void Resistor::MouseClickEvent(int button, int state, int x, int y) {
    if(button == 1 && state == GDK_BUTTON_PRESS){
        if(!_ready){
            _ready = true;
            _shape.setXY(x, y);
        }
    }
}

void Resistor::SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col) {
    float v = m.get(row, _nodes[1]->info->number);

    if(_nodes[1]->info->isReference){
        m.set(row, _nodes[1]->info->number, 1.0/_resistance + v);
        m.set(row, _nodes[0]->info->number, -1.0/_resistance + v);
    } else {
        m.set(row, _nodes[1]->info->number, -1.0/_resistance + v);
        m.set(row, _nodes[0]->info->number, 1.0/_resistance + v);
    }
}

bool Resistor::IsInside(int x, int y) { return _shape.isInside(x, y); }

void Resistor::PropertyChanged(void) {
    info.properties[0]->getValue()->load(_resistance);
}

Resistor::~Resistor() {

}
