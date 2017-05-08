#ifndef __CANVAS_H_
#define __CANVAS_H_

    #include <iostream>
    #include <vector>
    #include "Component.h"

    class Canvas {
        Shapes::Rectangle _dimensions;
        vector<Component*> _components;
        Node*** _canvasNodes;
        float _spacing;
        bool _showGrid;

    public:
        vector<Node*> createdNodes; 

        Canvas(int = 500, int = 500);
        void AddComponent(Component*);
        void RemoveComponent(Component*);
        void RemoveComponent(int);
        int GetComponentsNumber();
        int GetSourcesAndWiresNumber();
        void Draw(const Cairo::RefPtr<Cairo::Context>& cr);
        void MouseOverEvent(int, int);
        void MouseClickEvent(int, int, int, int);
        void ToggleGrid();
        
        void Connect(Component*);
        void Disconnect(Component*);
        ~Canvas();
    
    private:
        void DrawGrid(const Cairo::RefPtr<Cairo::Context>& cr);
    };
#endif