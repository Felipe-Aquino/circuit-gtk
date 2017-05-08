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
        thread *_simulation;
        vector<Node*> _nodes;

        unsigned _sourceNumber;
        unsigned _essentialNodesNumber;

    public:
        CircuitSimulator(vector<Node*>& nodes, unsigned sourceNumber);

        void Start();
        void End();
        ~CircuitSimulator();
    private:
        static void Run();

        /* 
        * Find lowest node and place it as the first on the vector _nodes
        */
        bool Grounding();
    };

#endif