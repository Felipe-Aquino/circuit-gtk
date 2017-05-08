#include "Canvas.h"
#include "../Useful/RemoveTemplate.h"

Canvas::Canvas(int x, int y): _dimensions(0,0,x,y) {
    _dimensions.setColor(Color::WHITE);
    _spacing = 10.0;
    _showGrid = true;

    _canvasNodes = new Node**[50];
    for(int i = 0; i < x/_spacing; i++){
        _canvasNodes[i] = new Node*[50];
        for(int j = 0;j < y/_spacing; j++)
            _canvasNodes[i][j] = NULL;
    }
    createdNodes.push_back(NULL);
}

void Canvas::AddComponent(Component* c) {
    _components.push_back(c);
}

void Canvas::RemoveComponent(Component* c) {
    Disconnect(c);
    Remove(_components, c);
}

void Canvas::RemoveComponent(int i) {
    _components.erase(_components.begin() + i);
}

int Canvas::GetComponentsNumber(){
    return _components.size();
}

int Canvas::GetSourcesAndWiresNumber(){
    int n = 0;
    for(auto c : _components){
        CompID id = c->GetID(); 
        if(id == CompID::WIRE || id == CompID::INDEP_V_SOURCE ) n++;
    }
    return n;
}

void Canvas::Draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    Component* a = NULL;

    _dimensions.draw(cr);
    DrawGrid(cr);

    for(auto c : _components){
        c->Draw(cr);

        if(c->ToDelete())
            a = c;
    }
    if(a) RemoveComponent(a); 
}

void Canvas::DrawGrid(const Cairo::RefPtr<Cairo::Context>& cr){
    cr->set_line_width(1.5);
    if(_showGrid)
        for(int i = 0; i < 50; i++){

            Color::setColor(cr, TColor::SILVER);
            cr->move_to(i*_spacing, 0);
            cr->line_to(i*_spacing, 500);

            cr->move_to(0, i*_spacing);
            cr->line_to(500, i*_spacing);
            cr->stroke();
        }
}

void Canvas::MouseOverEvent(int x, int y) {
    x = (int)_spacing*((int)(0.5 + x/_spacing));
    y = (int)_spacing*((int)(0.5 + y/_spacing));
    for(auto c : _components){
        c->MouseOverEvent(x, y);
    }
}

void Canvas::MouseClickEvent(int button, int state, int x, int y) {
    x = (int)_spacing*((int)(0.5 + x/_spacing));
    y = (int)_spacing*((int)(0.5 + y/_spacing));
    for(auto c : _components){
        c->MouseClickEvent(button, state, x, y);
    }
}

void Canvas::ToggleGrid(){
    _showGrid = !_showGrid;
}

void Canvas::Connect(Component* c){
    vector<Node*> comp_nodes = c->CheckNodes();
    for(auto node : comp_nodes){
        int i = node->dimension.getX()/_spacing;
        int j = node->dimension.getY()/_spacing;
        if(!_canvasNodes[i][j]){
            _canvasNodes[i][j] = new Node(node);
            createdNodes.push_back(_canvasNodes[i][j]);
        } else {
            delete node->info;
            node->info = _canvasNodes[i][j]->info;
        }
        _canvasNodes[i][j]->ConnectComponent(c);
        cout << "Adding component in the node [" << i << "," << j << "]" <<endl; 
    } 
}

void Canvas::Disconnect(Component* c){
    vector<Node*> comp_nodes = c->CheckNodes();
    for(auto node : comp_nodes){
        int i = node->dimension.getX()/_spacing;
        int j = node->dimension.getY()/_spacing;
        if(_canvasNodes[i][j]){
            _canvasNodes[i][j]->DisconnectComponent(c);
            if(!_canvasNodes[i][j]->HasComponent()){
                Remove(createdNodes, _canvasNodes[i][j]);
                delete _canvasNodes[i][j]; 
                _canvasNodes[i][j] = NULL;
                cout << "Removing node" << endl;
            }
        } 
        cout << "Remove component in the node [" << i << "," << j << "]" <<endl;
        cout << "Created nodes number: " << createdNodes.size() <<endl;
    } 
}

Canvas::~Canvas() {
    for(int i = 0; i < 50; i++){
        for(int j = 0;j < 50; j++)
            if(_canvasNodes[i][j]) delete _canvasNodes[i][j];
        delete[] _canvasNodes[i];
    }
    delete[] _canvasNodes;
}