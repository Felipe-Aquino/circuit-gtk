#include "App.h"

App::App(): canvas(){
    windowHeight = windowWidth = 500;
    _background = Shapes::Rectangle(0, 0, windowWidth, windowHeight);
    srand(time(NULL));
    newComponent = NULL;
    selectedComponent = NULL;
    simulation = NULL;
}

App::~App(){
    if(simulation) delete simulation;
}

void App::display(const Cairo::RefPtr<Cairo::Context>& cr){
    _background.draw(cr);
    canvas.Draw(cr);
}

void App::startSimulation(){
    if(simulation){ delete simulation; }
    
    simulation = new CircuitSimulator(canvas.createdNodes, canvas.GetSourcesAndWiresNumber());
    canvas.LinkCompSimulation(simulation);
    simulation->Start();

    for(int it = 0; it < 2; it++){
        simulation->Run();
    }
    
}

void App::mouseClick(int button, int state,int x, int y){
    canvas.MouseClickEvent(button, state, x,  y);

    if(newComponent && newComponent->IsReady()){
        canvas.Connect(newComponent);
        newComponent = NULL;
    }
}

void App::mouseMove(int x, int y){
    canvas.MouseOverEvent(x, y);
}

void App::keyPressed(unsigned char key, int x, int y){
    if(newComponent){
        if(key == (char)27) {
            canvas.RemoveComponent(newComponent);
            if(newComponent) delete newComponent;
            newComponent = NULL;
        }
        return;
    }

    switch(key){
    case 'w':
        newComponent = new Wire();
        canvas.AddComponent(newComponent);
        break;
    case 'c':
        newComponent = new Capacitor(x, y);
        canvas.AddComponent(newComponent);
        break;
    case 'r':
        newComponent = new Resistor(x, y);
        canvas.AddComponent(newComponent);
        break;
    case 'v':
        newComponent = new IndepVSource(x, y);
        canvas.AddComponent(newComponent);
        break;
    case 'g':
        canvas.ToggleGrid();
        break;
    default:
        cout << "The key " << (int)key << " was pressed. " << endl;
        return;
    }
}

bool App::selectComponentEvent(int x, int y){
    selectedComponent = canvas.FindComponent(x, y);
    cout << "Selected: " << selectedComponent <<endl; 
    return selectedComponent != NULL;
}
    
void App::removeSelectedComponentEvent(){
    canvas.RemoveComponent(selectedComponent);
}

void App::editSelectedComponentEvent(){

}

void App::deselectComponentEvent(){
    selectedComponent = NULL;
}