#include "IndepVSource.h"

IndepVSource::IndepVSource(){
    _id = CompID::INDEP_V_SOURCE;
    _ready = false;
    _delete = false;
    _drawMenu = false;
    _checked = false;
    _voltage = 5.0;
    _flow = 1.0;
    try{
        _shape.readFromSvg("./SVGs/independent_v_source.svg");
    } catch(exception& e){
        cout << "Exception: " << e.what() << endl;
        exit(1);
    }
}

void IndepVSource::Draw(const Cairo::RefPtr<Cairo::Context>& cr){
    _shape.draw(cr);

    for(auto n : _nodes) n->Draw(cr);

}

bool IndepVSource::IsReady(){
    return _ready;
}

void IndepVSource::UpdateProperties(Matrix& x){
    _current = _flow*x.get(_current_col, 0); // _flow sets the right direction of the current
    cout << "S - " << "V: " << _voltage << " I: " << _current << endl;
}

void IndepVSource::MouseOverEvent(int x, int y){
    if(_ready){
        //_menu.MouseOverEvent(x,y);
    }
    else {
        _shape.setXY(x, y);
    }
}

void IndepVSource::MouseClickEvent(int button, int state, int x, int y){
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

void IndepVSource::SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col){
    if(!_checked){
        _current_col = curr_col;
        m.set(row, curr_col++, 1);
        cout << "V N0: " << _nodes[0]->info->number << endl;
        cout << "V N1: " << _nodes[1]->info->number << endl;

        m.set(next_free_row, _nodes[1]->info->number, -1);
        m.set(next_free_row, _nodes[0]->info->number, 1);
        b.set(next_free_row, 0, _voltage);

        _flow = _nodes[1]->info->isReference ? 1.0 : -1.0;
        
        next_free_row++;
    } else {
        m.set(row, _current_col, -1);
        cout << "2V N0: " << _nodes[0]->info->number << endl;
        cout << "2V N1: " << _nodes[1]->info->number << endl;
    }
    
    _checked = true;
}

bool IndepVSource::IsInside(int x, int y){ return _shape.isInside(x, y); }

IndepVSource::~IndepVSource(){

}