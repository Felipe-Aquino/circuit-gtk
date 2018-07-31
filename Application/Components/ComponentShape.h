#ifndef __COMPONENT_SHAPE_
#define __COMPONENT_SHAPE_

#include <iostream>
#include <string>
#include "../../Useful/tinyxml/tinyxml.h"
#include "../../Shapes/Rectangle.h"
#include "../../Shapes/Circle.h"
#include <vector>
#include "../Component.h"

using namespace std;

class ComponentShape {
    class Container;

    Shapes::Shape* _container;
    vector<Shapes::Shape*> shapes;
    vector<Node*> nodes;

public:
    ComponentShape();
    void draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool isInside(float x, float y);
    void setXY(float x, float y);
    float getX();
    float getY();
    Shapes::Shape* getContainerShape();
    vector<Node*> readFromSvg(string path);
    Shapes::Rectangle* readRectSVG(TiXmlElement* element);
    Shapes::Circle* readCircleSVG(TiXmlElement* element);
    ~ComponentShape();
};

#endif
