#include "App.h"
#include "CompInfo.h"
#include "../Useful/report.h"
#include "../Useful/fast_gui.h"

using namespace report;

App::App() {
    height = width = 500;
    _background = Shapes::Rectangle(0, 0, width, height);
    _background.color("#FFFFFF");
    newComponent = NULL;
    selectedComponent = NULL;
    simulation = NULL;

    _spacing = 10.0;
    _showGrid = false;

    _gridNodes = new Node**[50];
    for(int i = 0; i < width/_spacing; i++){
        _gridNodes[i] = new Node*[50];
        for(int j = 0;j < height/_spacing; j++)
            _gridNodes[i][j] = NULL;
    }
    createdNodes.push_back(NULL);
    // newComponent = new Resistor(100, 100);
    // AddComponent(newComponent);
    // mouseClick(1, 4, 100, 100);
    // newComponent = NULL;
}

App::~App() {
    /*File file("test.circ");
    for(auto* c: _components){
        if(c->GetID() == Cid::RESISTOR) {
            Resistor* r = dynamic_cast<Resistor*>(c);
            r->write(file);
        }
        else if(c->GetID() == Cid::INDEP_V_SOURCE) {
            IVSource* r = dynamic_cast<IVSource*>(c);
            r->write(file);
        }
        else if(c->GetID() == Cid::WIRE) {
            Wire* r = dynamic_cast<Wire*>(c);
            r->write(file);
        }
        }*/

    for(int i = 0; i < 50; i++) {
        for(int j = 0; j < 50; j++)
            if(_gridNodes[i][j]) delete _gridNodes[i][j];
        delete[] _gridNodes[i];
    }
    delete[] _gridNodes;

    if(simulation) delete simulation;
}

void App::display(CairoContext& cr) {
    Component* a = NULL;

    _background.draw(cr);
    DrawGrid(cr);

    fst::Text(report::format("count: %", _components.size()));
    for(auto c : _components) {
        c->Draw(cr);

        if(c->ToDelete())
            a = c;
    }
    if(a) RemoveComponent(a);

    if(simulation) {
        simulation->Debug();
    }
}

void App::startSimulation() {
    if(simulation) delete simulation;

    simulation = new CircuitSimulator(createdNodes, GetSourcesAndWiresNumber());
    simulation->SetComponents(_components);
    simulation->Start();

    //for(int it = 0; it < 2; it++){
        simulation->Run();
        //}
}

void App::mouseClick(int button, int state, int x, int y) {
    x = (int)_spacing*((int)(0.5 + x/_spacing));
    y = (int)_spacing*((int)(0.5 + y/_spacing));
    for(auto c : _components) {
        c->MouseClickEvent(button, state, x, y);
    }

    if(newComponent && newComponent->IsReady()) {
        Connect(newComponent);
        newComponent = NULL;
    }
}

void App::mouseMove(int x, int y) {
    x = (int)_spacing*((int)(0.5 + x/_spacing));
    y = (int)_spacing*((int)(0.5 + y/_spacing));
    for(auto c : _components) {
        c->MouseOverEvent(x, y);
    }
}

void App::keyPressed(unsigned char key, int x, int y) {
    if(newComponent) {
        if(key == (char)27) {
            RemoveComponent(newComponent);
            if(newComponent) delete newComponent;
            newComponent = NULL;
        }
        return;
    }

    switch(key) {
    case 'w':
        newComponent = new Wire();
        AddComponent(newComponent);
        break;
    case 'c':
        newComponent = new Capacitor(x, y);
        AddComponent(newComponent);
        break;
    case 'r':
        newComponent = new Resistor(x, y);
        AddComponent(newComponent);
        break;
    case 'v':
        newComponent = new IVSource(x, y);
        AddComponent(newComponent);
        break;
    case 'g':
        _showGrid = !_showGrid;
        break;
    default:
        report::report(format("The key % was pressed.", key));
        break;
    }
}

bool App::selectComponentEvent(int x, int y) {
    selectedComponent = FindComponent(x, y);
    return selectedComponent != NULL;
}

void App::removeSelectedComponentEvent() {
    RemoveComponent(selectedComponent);
}

CompInfo& App::editSelectedComponentEvent() {
    return selectedComponent->info;
}

void App::deselectComponentEvent() {
    selectedComponent = NULL;
}

void App::AddComponent(Component* c) {
    _components.push_back(c);
}

void App::RemoveComponent(Component* c) {
    Disconnect(c);
    Remove(_components, c);
}

Component* App::FindComponent(int x, int y){
    x = (int)_spacing*((int)(0.5 + x/_spacing));
    y = (int)_spacing*((int)(0.5 + y/_spacing));
    report::report(report::format("Where: %, %", x, y));
    for(auto c : _components){
        if(c->IsInside(x, y))
            return c;
    }
    return NULL;
}

int App::GetSourcesAndWiresNumber(){
    int n = 0;
    for(auto c : _components){
        Cid id = c->GetID();
        if(id == Cid::WIRE || id == Cid::I_V_SOURCE ) n++;
    }
    return n;
}

void App::DrawGrid(CairoContext& cr){
    fst::Toggle("Grid", _showGrid);

    cr->set_line_width(1.5);
    if(_showGrid) {
        for(int i = 0; i < 50; i++) {
            cr->set_source_rgb(0.6, 0.6, 0.6);
            cr->move_to(i*_spacing, 0);
            cr->line_to(i*_spacing, 500);

            cr->move_to(0, i*_spacing);
            cr->line_to(500, i*_spacing);
            cr->stroke();
        }
    }
}

void App::Connect(Component* c) {
    vector<Node*> comp_nodes = c->CheckNodes();
    for(auto node : comp_nodes) {
        int i = node->dimension.getX()/_spacing;
        int j = node->dimension.getY()/_spacing;
        if(!_gridNodes[i][j]) {
            _gridNodes[i][j] = new Node(node);
            createdNodes.push_back(_gridNodes[i][j]);
        } else {
            delete node->info;
            node->info = _gridNodes[i][j]->info;
        }
        _gridNodes[i][j]->ConnectComponent(c);
        report::report(format("Adding component in the node [%, %]", i, j));
    }
}

void App::Disconnect(Component* c) {
    vector<Node*> comp_nodes = c->CheckNodes();
    for(auto node : comp_nodes) {
        int i = node->dimension.getX()/_spacing;
        int j = node->dimension.getY()/_spacing;
        if(_gridNodes[i][j]) {
            _gridNodes[i][j]->DisconnectComponent(c);
            if(!_gridNodes[i][j]->HasComponent()) {
                Remove(createdNodes, _gridNodes[i][j]);
                delete _gridNodes[i][j];
                _gridNodes[i][j] = NULL;
                report::report("Removing node");
            }
        }
        report::report(format("Remove component in the node [%, %]", i, j));
        report::report(format("Created nodes number: %", createdNodes.size()));
    }
}
