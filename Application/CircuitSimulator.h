#ifndef __CIRCUIT_SIMULATOR_
#define __CIRCUIT_SIMULATOR_

#include <iostream>
#include <thread>
#include <vector>
#include "Component.h"
#include "../Useful/Math/Matrix.h"


using namespace std;
using namespace Math;

class CircuitSimulator {
    Matrix *_m;
    Matrix *_b;
    Matrix *_x;
    thread *_simulation;
    vector<Node*>& _nodes;
    vector<Component*> _components;

    unsigned _sourceNumber;
    unsigned _essentialNodesNumber;

public:
    CircuitSimulator(vector<Node*>& nodes, unsigned sourceNumber);

    void Debug();
    void Start();
    void End();

    void UpdateComponents();
    void SetComponents(vector<Component*>& components);
    ~CircuitSimulator();
    void Run();
private:


    void UpdateNodes();
    /*
    * Find lowest node and place it as the first on the vector _nodes
    */
    bool Grounding();
};

#endif
