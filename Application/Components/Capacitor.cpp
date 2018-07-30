#include "Capacitor.h"
#include "../../Useful/report.h"

Capacitor::Capacitor(int x, int y):Component() {
    _id = Cid::CAPACITOR;
    _ready = false;
    _delete = false;
    _drawMenu = false;
    _capacitance = 0.001;
    try{
        _nodes = _shape.readFromSvg("./SVGs/resistor.svg");
        _shape.setXY(x, y);
    } catch(exception& e){
        report::exception(e.what());
        exit(1);
    }
    _voltage0 = 0;
    info.name = "Capacitor";
    Property* prop= new Property("capacitance", new Float(_capacitance));
    prop->onChange.connect_member(this, &Capacitor::PropertyChanged);
    info.properties.push_back(prop);
}

void Capacitor::Draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    _shape.draw(cr);
}

bool Capacitor::IsReady() {
    return _ready;
}

void Capacitor::UpdateProperties(Matrix& x) {
    _voltage = _nodes[0]->info->voltage - _nodes[1]->info->voltage;
    _current = _capacitance*(_voltage -_voltage0)/_dt;
}

void Capacitor::MouseOverEvent(int x, int y) {
    if(!_ready) {
        _shape.setXY(x, y);
    }
}

void Capacitor::MouseClickEvent(int button, int state, int x, int y) {
    if(button == 1 && state == GDK_BUTTON_PRESS) {
        if(!_ready) {
            _ready = true;
            _shape.setXY(x, y);
        }
    }
}

void Capacitor::SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col) {
    float v = m.get(row, _nodes[1]->info->number);
    float bvalue = b.get(row, 0);

    _voltage0 = _voltage;
    //float dv = (_dt*_current/_capacitance);

    if(_nodes[1]->info->isReference) {
        m.set(row, _nodes[1]->info->number, _capacitance/_dt + v);
        m.set(row, _nodes[0]->info->number, -_capacitance/_dt + v);
        b.set(row, 0, _current + bvalue);
    } else {
        m.set(row, _nodes[1]->info->number, -_capacitance/_dt + v);
        m.set(row, _nodes[0]->info->number, _capacitance/_dt + v);
        b.set(row, 0, -_current + bvalue);
    }
}

bool Capacitor::IsInside(int x, int y) { return _shape.isInside(x, y); }

void Capacitor::PropertyChanged(void) {
    cout << "Caoacitance changed from " << _capacitance;
    info.properties[0]->getValue()->load(_capacitance);
    cout << " to " << _capacitance << endl;
}

Capacitor::~Capacitor() {

}
