#ifndef __CAPACITOR_H_
#define __CAPACITOR_H_

#include "../Component.h"
#include "ComponentShape.h"

using namespace std;
using namespace Math;

class Capacitor : public Component {
    ComponentShape _shape;
    bool _ready;
    bool _delete;
    bool _drawMenu;

    float _capacitance;
    float _voltage0;
public:
    Capacitor(int, int);
    void Draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool IsReady();
    void UpdateProperties(Matrix&);
    void MouseOverEvent(int, int);
    void MouseClickEvent(int, int, int, int);
    void SetEquation(Matrix&, Matrix&, int, int&, int&);
    void PropertyChanged(void);
    bool IsInside(int, int);
    ~Capacitor();
};

#endif
