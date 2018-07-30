#include "IVSource.h"

IVSource::IVSource(int x, int y) {
    _id = Cid::I_V_SOURCE;
    _ready = false;
    _delete = false;
    _drawMenu = false;
    _checked = false;
    _voltage = 5.0;
    _flow = 1.0;
    try {
        _nodes = _shape.readFromSvg("./SVGs/i_v_source.svg");
        _shape.setXY(x, y);
    } catch(exception& e){
        cout << "Exception: " << e.what() << endl;
        exit(1);
    }

    info.name = "Source";
    Property* property = new Property("voltage", new Float(_voltage));
    property->onChange.connect_member(this, &IVSource::PropertyChanged);
    info.properties.push_back(property);
}

void IVSource::Draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    _shape.draw(cr);
}

bool IVSource::IsReady() {
    return _ready;
}

void IVSource::UpdateProperties(Matrix& x) {
    _current = _flow*x.get(_current_col, 0); // _flow sets the right direction of the current
    cout << "S - " << "V: " << _voltage << " I: " << _current << endl;
    _checked = false;
}

void IVSource::MouseOverEvent(int x, int y) {
    if(!_ready){
        _shape.setXY(x, y);
    }
}

void IVSource::MouseClickEvent(int button, int state, int x, int y) {
    if(button == 1 && state == GDK_BUTTON_PRESS){
        if(!_ready){
            _ready = true;
            _shape.setXY(x, y);
        }
    }
}

void IVSource::SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col) {
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

bool IVSource::IsInside(int x, int y) { return _shape.isInside(x, y); }

void IVSource::PropertyChanged(void) {
    cout << "Voltage changed from " << _voltage;
    info.properties[0]->getValue()->load(_voltage);
    cout << " to " << _voltage << endl;
}

IVSource::~IVSource() {

}