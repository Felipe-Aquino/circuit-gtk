#ifndef __COMPONENT_H_
#define __COMPONENT_H_

#include "../Shapes/Rectangle.h"
#include "../Shapes/Circle.h"
#include "../Useful/Math/Matrix.h"
#include "../Useful/RemoveTemplate.h"
#include "CompInfo.h"
#include <vector>

using namespace std;
using namespace Shapes;
using namespace Math;

class Node;

typedef enum class compID {
    WIRE, RESISTOR, CAPACITOR, INDEP_V_SOURCE
} CompID;

class Component {
protected:
    CompID _id;
    vector<Node*> _nodes;
    bool _delete;
    float _voltage, _current;
    float _dt;

public:
    CompInfo info;

    /* Contructors */
    Component(){
        _delete = false;
        _voltage = _current = 0.0;
        _dt = 0.01;
    };

    Component(Component& c){
        _id = c._id;
        _delete = false;
    }

    /*
    * Draw method.
    */
    virtual void Draw(const Cairo::RefPtr<Cairo::Context>& cr) = 0;
    virtual bool IsReady() = 0;

    /*
    * Returns the id of the component.
    */
    CompID GetID(){ return _id; }
    bool ToDelete() { return _delete; }
    void SetDelete(bool del) { _delete = del; }

    virtual bool IsInside(int x, int y) = 0;

    /*
    * Update the properties (voltage, current e etc.) of the component.
    */
    virtual void UpdateProperties(Matrix&) = 0;

    /*
    * Method call when the mouse is over the component.
    */
    virtual void MouseOverEvent(int, int) = 0;

    /*
    * Method call when a mouse click occour.
    */
    virtual void MouseClickEvent(int, int, int, int) = 0;

    /* Destructor */
    virtual ~Component(){};

    /*
    * Given the matricial equation Mx = b. This method fill the values in the matrices M and b, where
    * 'row' is the current row to be filled, 'next_free_row' is the next row where a adicional equation, must be set
    * and 'curr_col' is the next column in  the row 'row' to be filled with a current attribute.
    */
    virtual void SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col) = 0;

    /*
    * Returns the array of nodes of the component.
    */
    vector<Node*> CheckNodes() { return _nodes; }
};

class Node {
    vector<Component*> _connectComps;

public:
    class NodeInfo {
    public:
        bool isReference;
        int number;
        float voltage;
        NodeInfo(): isReference(false), number(0), voltage(0.0) {}
    };

    Circle dimension;
    int radius;
    NodeInfo* info;


    Node(int x = 0, int y = 0): dimension(x,y,5), radius(5) { info = new NodeInfo(); }
    Node(Node* n): dimension(n->dimension){
        radius = n->radius;
        info = n->info;
        //_connectComps = n->_connectComps;
    };

    void Draw(const Cairo::RefPtr<Cairo::Context>& cr) { dimension.draw(cr); }
    void SetXY(int x, int y){ dimension.setX(x), dimension.setY(y); }
    vector<Component*> getComponents() { return _connectComps; }
    void ConnectComponent(Component *c){ _connectComps.push_back(c); }
    void DisconnectComponent(Component* c) { Remove(_connectComps, c); }

    bool HasComponent() { return _connectComps.size() > 0; }
    bool IsEstable()   { return _connectComps.size() > 1; }
    bool IsEssential() { return _connectComps.size() > 2; }

    ~Node(){}
};

#endif
