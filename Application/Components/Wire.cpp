#include "Wire.h"

Wire::Wire(): p0(), p1() {
    _firstClick = _secondClick = false;
    _id = CompID::WIRE;
    _delete = false;
    _drawMenu = false;
    _voltage = 0.0;
}

void Wire::Draw(const Cairo::RefPtr<Cairo::Context>& cr){
    if(_firstClick) {
        cr->set_line_width(2.0);
        Color::setColor(cr, TColor::BLACK);
        
        cr->move_to(p0.x, p0.y);
        cr->line_to(p1.x, p1.y);
        cr->stroke();
        
        for(auto n : _nodes){
            n->Draw(cr);
        }
    }

}

bool Wire::IsReady() { return _secondClick; }

void Wire::MouseOverEvent(int x, int y){
    if(_firstClick && !_secondClick){
        p1.x = x;
        p1.y = y;
        //cout << "\rA " << x << " " << y;
    }
}

void Wire::MouseClickEvent(int button, int state, int x, int y){
    if(button == 1 && state == GDK_BUTTON_PRESS){
        if(!_firstClick) {
            _firstClick = true;
            p0.x = p1.x = x;
            p0.y = p1.y = y;
            _nodes.push_back(new Node(x, y));
            _dimensions.setW(20);
        } else if(!_secondClick) {
            _secondClick = true;
            p1.x = x;
            p1.y = y;
            if(p0.y > p1.y){
                Point p(p0);
                p0 = p1;
                p1 = p;
            }

            ang = atan((p1.y -p0.y)/(p1.x -p0.x));
            ang = ang >= 0 ? ang : 3.1415926 + ang;
            type = ang >= 0 ? 1 : 0;

            _dimensions.setX(p0.x - 10*sin(ang));
            _dimensions.setY(p0.y + 10*cos(ang));
            _dimensions.setH(p0.distance(p1));
            _nodes.push_back(new Node(x, y));
        }
    }
    /*if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if(_secondClick){
            double ang2 = type*3.1415926/2 - ang;
            Point p(x,y);
            Vector v(p0, p);
            Vector axis(0,0,1);
            v.rotate(axis, ang2);
            if(_dimensions.isInside(p0.x+v.x, p0.y+v.y)){
                _drawMenu = true;
                _menu.SetXY(x, y);
                cout << x << " " << y <<endl;
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

void Wire::SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col){
    if(!_checked){
        _current_col = curr_col;
        m.set(row, curr_col++, 1);
        cout << "W N0: " << _nodes[0]->info->number << endl;
        cout << "W N1: " << _nodes[1]->info->number << endl;
        if(_nodes[1]->info->isReference){
            m.set(next_free_row, _nodes[1]->info->number, 1);
            m.set(next_free_row, _nodes[0]->info->number, -1);
            b.set(next_free_row, 0, _voltage);
        } else {
            m.set(next_free_row, _nodes[1]->info->number, -1);
            m.set(next_free_row, _nodes[0]->info->number, 1);
            b.set(next_free_row, 0, _voltage);
        }
        next_free_row++;
    } else {
        cout << "2W N0: " << _nodes[0]->info->number << endl;
        cout << "2W N1: " << _nodes[1]->info->number << endl;
        m.set(row, _current_col, -1);
    }
    
    _checked = true;
}

Wire::~Wire(){

}