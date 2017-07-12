#include "CircuitSimulator.h"

CircuitSimulator::CircuitSimulator(vector<Node*>& nodes, unsigned sourceNumber){
    _b = _m = _x = NULL;
    _simulation = NULL;

    _nodes = nodes;
    _sourceNumber = sourceNumber;
    _essentialNodesNumber = 0;
}

void CircuitSimulator::Start(){
    if(_nodes.size() < 2) return;

    bool ok = Grounding();
    if(!ok) { cout << "OPEN CIRCUIT!!" << endl; return;}

    int matrix_size = _nodes.size() + _sourceNumber;

    _m = new Matrix(matrix_size);
    _b = new Matrix(matrix_size, 1);

    int row = 1;
    int next_free_row = 2;
    int curr = _nodes.size();
    int i = 0;

    _m->set(0, 0, 1);
    cout << "Nodes: " << curr  << endl;
    cout << "SIZE: " << matrix_size << endl;
    for(auto n : _nodes){
        if((i++)){
        n->info->isReference = true;

        for(auto comp : n->getComponents()){
            comp->SetEquation(*_m, *_b, row, next_free_row, curr);
        }        

        row = next_free_row++;
        n->info->isReference = false;
        }
    }

    _m->print();
    _b->print();
    _x = new Matrix(matrix_size, 1);
    *_x = _m->luSolving(*_b);  
    
    _x->print();
    UpdateNodes();
}

void CircuitSimulator::End(){

}

void CircuitSimulator::Run(){

}

void CircuitSimulator::UpdateNodes(){
    for(auto n : _nodes){
        auto info = n->info;
        info->voltage = _x->get(info->number, 0);
    }
}

void CircuitSimulator::UpdateComponents(vector<Component*> components){
    for(auto c : components){
        c->UpdateProperties(*_x);
    }
}

bool CircuitSimulator::Grounding(){
    float greater_y = 0, y;
    int position = 0, i = 0;
    for(auto n : _nodes){
        if(i > 0) {
            y = n->dimension.getY();
            if(y > greater_y){
                greater_y = y;
                position = i; 
            }
        }
        i++;
    }
    cout << "ESSENTIAL NODES: " << i << " " << greater_y << endl;
    _nodes[0] = _nodes[position];
    _nodes.erase(_nodes.begin() + position);
    i = 0;
    for(auto n : _nodes){ 
        n->info->number = i++;
        if(!n->IsEstable()) return false;
    }
    return true;
}

CircuitSimulator::~CircuitSimulator(){
    delete _m;
    delete _b;
}
