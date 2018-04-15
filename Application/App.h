#ifndef __APP_H_
#define __APP_H_

#include <iostream>
#include <cmath>
#include <cstring>
#include <time.h>
#include "../Shapes/Circle.h"
#include "../Shapes/Rectangle.h"
#include "CircuitSimulator.h"
#include "Canvas.h"
#include "Components/Components.h"

using namespace std;

class App {
    Canvas canvas;

    Component* newComponent;
    Component* selectedComponent;

    CircuitSimulator* simulation;
    Shapes::Rectangle _background;
public:
    int windowHeight, windowWidth;

    App();
    ~App();

    /*
    * Draw all elements of the application
    */
    void display(const Cairo::RefPtr<Cairo::Context>& cr);

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
};

#endif
