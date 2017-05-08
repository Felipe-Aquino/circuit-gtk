#ifndef __COMPONENT_H_
#define __COMPONENT_H_

    #include "../Shapes/Rectangle.h"
    #include "../Shapes/Circle.h"
    #include "../Useful/Math/Matrix.h"
    #include "../Useful/RemoveTemplate.h"
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
        Shapes::Rectangle _dimensions;
        CompID _id;
        vector<Node*> _nodes;
        bool _delete;
        float _voltage, _current;

    public:
        Component(){
            _delete = false;
            _voltage = _current = 0.0;
        };
        Component(Component& c): _dimensions(c._dimensions){
            _id = c._id;
            _delete = false;
        }

        virtual void Draw(const Cairo::RefPtr<Cairo::Context>& cr) = 0;
        virtual bool IsReady() = 0;
        CompID GetID(){ return _id; }
        bool ToDelete() { return _delete; }
        void SetDelete(bool del) { _delete = del; }
        virtual void MouseOverEvent(int, int) = 0;
        virtual void MouseClickEvent(int, int, int, int) = 0;
        virtual ~Component(){};

        virtual void SetEquation(Matrix& m, Matrix& b, int row, int& next_free_row, int& curr_col) = 0;
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
            NodeInfo(): isReference(false), voltage(0.0), number(0){}
        };
        
        Circle dimension;
        int radius;
        NodeInfo* info;
        

        Node(int x = 0, int y = 0): radius(5), dimension(x,y,5){ info = new NodeInfo(); }
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
