#ifndef __APP_H_
#define __APP_H_

#include <iostream>
#include <cmath>
#include <cstring>
#include <time.h>
#include "../Shapes/Circle.h"
#include "../Shapes/Rectangle.h"
#include "../Useful/LinkedList.h"
#include "CircuitSimulator.h"
#include "Canvas.h"
#include "Components/Components.h"

using namespace std;

class App {
    Canvas canvas;

    Component* newComponent;

    CircuitSimulator* simulation;
    Shapes::Rectangle _background;
public:
    int windowHeight, windowWidth;

    App();
    ~App();
    void display(const Cairo::RefPtr<Cairo::Context>& cr);

    void keyPressed(unsigned char, int, int);

    void startSimulation();

    void mouseMove(int x, int y);
    void mouseClick(int button, int state, int x, int y);

};

#endif
