#ifndef __COMPONENT_SHAPE_
#define __COMPONENT_SHAPE_

#include <iostream>
#include <string>
#include "../../Useful/tinyxml/tinyxml.h"
#include "../../Shapes/Rectangle.h"
#include "../../Shapes/Circle.h"
#include <exception>
#include <vector>

using namespace std;

class ComponentShape {
    class Container;

    Container* _container;
    std::vector<Shapes::Rectangle*> rects;
    std::vector<Shapes::Circle*> circs;

public:
    ComponentShape();
    void draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool isInside(float x, float y);
    void setXY(float x, float y);
    Shapes::Shape* getContainerShape();
    void readFromSvg(std::string path);
    void readRectSVG(TiXmlElement* element, Shapes::Rectangle& rect);
    void readCircleSVG(TiXmlElement* element, Shapes::Circle& circ);
    ~ComponentShape();
    
private:
    const char* attr;
    string msg;
    const string& miss_msg(string attr, string tag);
    void readAttriute(TiXmlElement* element, const char* attrname, const char* type = "rect");
};

#endif