#ifndef __APP_H_
#define __APP_H_

#include <iostream>
#include <cmath>
#include <cstring>
#include "../Shapes/Circle.h"
#include "../Shapes/Rectangle.h"
#include "CircuitSimulator.h"
#include "Components/Components.h"

typedef const Cairo::RefPtr<Cairo::Context> CairoContext;

using namespace std;

class App {
    Component* newComponent;
    Component* selectedComponent;

    CircuitSimulator* simulation;
    Shapes::Rectangle _background;

    vector<Component*> _components;
    Node*** _gridNodes;
    float _spacing;
    bool _showGrid;

    vector<Node*> createdNodes;
public:
    int height, width;

    App();
    ~App();

    /*
    * Draw all elements of the application
    */
    void display(CairoContext& cr);

    /*
    * Process the key pressed event
    */
    void keyPressed(unsigned char, int, int);

    /*
    * Start the simulation
    */
    void startSimulation();

    /*
    * Dealing with mouse events
    */
    void mouseMove(int x, int y);
    void mouseClick(int button, int state, int x, int y);

    bool selectComponentEvent(int x, int y);
    void removeSelectedComponentEvent();
    CompInfo& editSelectedComponentEvent();
    void deselectComponentEvent();

 private:
    void AddComponent(Component*);
    void RemoveComponent(Component*);
    Component* FindComponent(int, int);
    int GetSourcesAndWiresNumber();

    void Connect(Component*);
    void Disconnect(Component*);

    void DrawGrid(CairoContext& cr);
};

#endif
