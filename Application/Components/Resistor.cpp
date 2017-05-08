#include "Resistor.h"

Resistor::Resistor(){
    _id = CompID::RESISTOR;
    _ready = false;
    _delete = false;
    _drawMenu = false;
    _resistance = 100.0; 
    try{
        _shape.readFromSvg("./SVGs/resistor.svg");
        _shape.setXY(150, 150);
    } catch(exception& e){
        cout << "Exception: " << e.what() << endl;
        exit(1);
    }
}

void Resistor::Draw(const Cairo::RefPtr<Cairo::Context>& cr){
    _shape.draw(cr);

    for(auto n : _nodes) n->Draw(cr);
}

bool Resistor::IsReady(){
    return _ready;
}

void Resistor::MouseOverEvent(int x, int y){
    if(_ready){
        //_menu.MouseOverEvent(x,y);
    }
    else {
        _shape.setXY(x, y);
    }
}

void Resistor::MouseClickEvent(int button, int state, int x, int y){
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
    /*if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if(_ready){
            if(_shape.isInside(x, y)){
                _drawMenu = true;
                _menu.SetXY(x, y);
            }
        }
    }

    if(state == GLUT_DOWN){
        if(!_menu.MouseOverMenu(x, y) && _drawMenu){
            _drawMenu = false;
        } 
    }
    if(_drawMenu) _menu.MouseClickEvent(button, state, x, y);*/
} 

void Resistor::SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col){
    float v = m.get(row, _nodes[1]->info->number);

    cout << "R N0: " << _nodes[0]->info->number << endl;
    cout << "R N1: " << _nodes[1]->info->number << endl;

    if(_nodes[1]->info->isReference){
        m.set(row, _nodes[1]->info->number, 1.0/_resistance + v);
        m.set(row, _nodes[0]->info->number, -1.0/_resistance + v);
    } else {
        m.set(row, _nodes[1]->info->number, -1.0/_resistance + v);
        m.set(row, _nodes[0]->info->number, 1.0/_resistance + v);
    }
}


Resistor::~Resistor(){

}