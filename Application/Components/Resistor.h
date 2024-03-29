#ifndef __RESISTOR_H_
#define __RESISTOR_H_

#include "../Component.h"
#include "ComponentShape.h"

using namespace std;
using namespace Math;

class Resistor : public Component {
    ComponentShape _shape;
    bool _ready;    
    bool _delete;
    bool _drawMenu;

    float _resistance;
public:
    Resistor();
    void Draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool IsReady();
    void MouseOverEvent(int, int);
    void MouseClickEvent(int, int, int, int);
    void SetEquation(Matrix&, Matrix&, int, int&, int&);
    ~Resistor();
};

#endif