#ifndef __INDEP_V_SOURCE_H_
#define __INDEP_V_SOURCE_H_

#include "../Component.h"
#include "ComponentShape.h"

using namespace std;
using namespace Math;

class IndepVSource : public Component {
    ComponentShape _shape;
    bool _ready;    
    bool _delete;
    bool _drawMenu;

    bool _checked;
    int _current_col;
    float _flow;
public:
    IndepVSource(int, int);
    void Draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool IsReady();
    void UpdateProperties(Matrix&);
    void MouseOverEvent(int, int);
    void MouseClickEvent(int, int, int, int);
    void SetEquation(Matrix&, Matrix&, int, int&, int&);
    bool IsInside(int, int);
    ~IndepVSource();
};

#endif