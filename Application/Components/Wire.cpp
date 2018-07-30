#include "Wire.h"

Wire::Wire(): p0(), p1() {
    _firstClick = _secondClick = false;
    _id = Cid::WIRE;
    _delete = false;
    _drawMenu = false;
    _voltage = 0.0;
    _flow = 1.0;
}

void Wire::Draw(const Cairo::RefPtr<Cairo::Context>& cr){
    if(_firstClick) {
        cr->set_line_width(2.0);
        cr->set_source_rgb(0.0, 0.0, 0.0);

        cr->move_to(p0.x, p0.y);
        cr->line_to(p1.x, p1.y);
        cr->stroke();

        for(auto n : _nodes){
            n->Draw(cr);
        }
    }

}

bool Wire::IsReady() { return _secondClick; }

void Wire::UpdateProperties(Matrix& x){
    _current = _flow*x.get(_current_col, 0);  // _flow sets the right direction of the current
    cout << "W - " << "V: " << _voltage << " I: " << _current << endl;
    _checked = false;
}

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
}

void Wire::SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col) {
    if(!_checked) {
        _current_col = curr_col;
        m.set(row, curr_col++, 1);
        cout << "W N0: " << _nodes[0]->info->number << endl;
        cout << "W N1: " << _nodes[1]->info->number << endl;

        m.set(next_free_row, _nodes[1]->info->number, 1);
        m.set(next_free_row, _nodes[0]->info->number, -1);
        b.set(next_free_row, 0, _voltage);

        _flow = _nodes[1]->info->isReference ? -1.0 : 1.0;

        next_free_row++;
    } else {
        cout << "2W N0: " << _nodes[0]->info->number << endl;
        cout << "2W N1: " << _nodes[1]->info->number << endl;
        m.set(row, _current_col, -1);
    }

    _checked = true;
}

bool Wire::IsInside(int x, int y) {
    double ang2 = type*3.1415926/2 - ang;
    Point p(x,y);
    Vector v(p0, p);
    Vector axis(0,0,1);
    v.rotate(axis, ang2);
    return _dimensions.isInside(p0.x+v.x, p0.y+v.y);
}

Wire::~Wire() {

}
