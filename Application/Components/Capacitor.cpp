#include "Capacitor.h"

Capacitor::Capacitor():Component(){
    _id = CompID::CAPACITOR;
    _ready = false;
    _delete = false;
    _drawMenu = false;
    _capacitance = 0.001; 
    try{
        _shape.readFromSvg("./SVGs/capacitor.svg");
        _shape.setXY(150, 150);
    } catch(exception& e){
        cout << "Exception: " << e.what() << endl;
        exit(1);
    }
    _voltage0 = 0;
}

void Capacitor::Draw(const Cairo::RefPtr<Cairo::Context>& cr){
    _shape.draw(cr);

    for(auto n : _nodes) n->Draw(cr);
}

bool Capacitor::IsReady(){
    return _ready;
}

void Capacitor::UpdateProperties(Matrix& x){
    _voltage = _nodes[0]->info->voltage - _nodes[1]->info->voltage; 
    _current = _capacitance*(_voltage -_voltage0)/_dt;
}

void Capacitor::MouseOverEvent(int x, int y){
    if(_ready){
        //_menu.MouseOverEvent(x,y);
    }
    else {
        _shape.setXY(x, y);
    }
}

void Capacitor::MouseClickEvent(int button, int state, int x, int y){
    if(button == 1 && state == GDK_BUTTON_PRESS){
        if(!_ready){
            _ready = true;
            _shape.setXY(x, y);
            
            Shapes::Rectangle* r = dynamic_cast<Shapes::Rectangle*>(_shape.getContainerShape());
            int x = (int)(1.0*r->getX() + 0.5*r->getW() );
            int y = r->getY();
            cout <<  x << " " << y << endl;
            _nodes.push_back(new Node(x,y));

            y = r->getY() + r->getH();
            _nodes.push_back(new Node(x,y));
        }
    }
} 

void Capacitor::SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col){
    float v = m.get(row, _nodes[1]->info->number);
    float bvalue = b.get(row, 0);

    _voltage0 = _voltage;
    float dv = (_dt*_current/_capacitance) + _voltage0;

    if(_nodes[1]->info->isReference){
        m.set(row, _nodes[1]->info->number, 1.0 + v);
        m.set(row, _nodes[0]->info->number, -1.0 + v);
        b.set(row, 0, dv + bvalue);
    } else {
        m.set(row, _nodes[1]->info->number, -1.0 + v);
        m.set(row, _nodes[0]->info->number, 1.0 + v);
        b.set(row, 0, -dv + bvalue);
    }
}

bool Capacitor::IsInside(int x, int y){ return _shape.isInside(x, y); }

Capacitor::~Capacitor(){

}