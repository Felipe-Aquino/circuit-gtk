#include "ComponentShape.h"
#include "../../Useful/report.h"
#include <cstring>
#include <exception>

#define miss_msg(attr, tag)  \
    report::format("Missing the '%' attribute in a % from svg file.", attr, tag)

#define readAttribute(name, type)    \
    attr = element->Attribute(name); \
    if(!attr)                        \
        throw SvgReaderException(miss_msg(name, type));


class SvgReaderException : public exception {
    string message;
public:
    SvgReaderException(const char* msg): message(msg){ };
    SvgReaderException(string msg): message(msg){ };
    virtual const char* what() const throw(){
        return message.c_str();
    }
    ~SvgReaderException(){};
};

ComponentShape::ComponentShape() {
    _container = NULL;
}

bool ComponentShape::isInside(float x, float y) {
    return _container->isInside(x, y);
}

void ComponentShape::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    for(auto s : shapes)
        s->draw(cr);
    for(auto* n: nodes)
        n->dimension.draw(cr);
}

void ComponentShape::setXY(float x, float y) {
    float dx = x - _container->getX();
    float dy = y - _container->getY();

    for(auto s : shapes) {
        s->setX((int)(s->getX() + dx));
        s->setY((int)(s->getY() + dy));
    }
    for(auto* n: nodes) {
        n->SetXY((int)(n->dimension.getX() + dx),
                 (int)(n->dimension.getY() + dy));
    }

    _container->setX(x);
    _container->setY(y);
}

float ComponentShape::getX() {
    return _container->getX();
}

float ComponentShape::getY() {
    return _container->getY();
}

Shapes::Shape* ComponentShape::getContainerShape() {
    return _container;
}

vector<Node*> ComponentShape::readFromSvg(std::string path) {
    if(path[0] == '~'){
        path.erase(0,1);
        string s(getenv("HOME"));
        path = s + path;
    }

    TiXmlDocument doc(path.c_str());

    if(!doc.LoadFile())
        throw SvgReaderException(doc.ErrorDesc());

    TiXmlElement *svg = doc.FirstChildElement("svg");
    if(svg == NULL) {
        doc.Clear();
        throw SvgReaderException("Fail to load file: No SVG element!");
    }

    const char* attr;
    for(TiXmlElement *elem = svg->FirstChildElement("rect"); elem!=NULL; elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();
        attr = elem->Attribute("id");

        if(elemName == "circle") {
            auto* c = readCircleSVG(elem);

            if(attr && !strcmp(attr, "container")) _container = c;
            else if(attr && !strcmp(attr, "node")) {
                nodes.push_back(new Node(c->getX(), c->getY()));
            }
            else shapes.push_back(c);
        }
        else if(elemName == "rect"){
            auto* r = readRectSVG(elem);

            if(attr && !strcmp(attr, "container")) _container = r;
            else shapes.push_back(r);
        }
    }

    if(_container == NULL)
        throw SvgReaderException("Container not found!");

    return nodes;
}

Shapes::Rectangle* ComponentShape::readRectSVG(TiXmlElement* element) {
    Shapes::Rectangle* rect = new Shapes::Rectangle();
    const char* attr = NULL;

    readAttribute("x", "rect");
    rect->setX(atof(attr));

    readAttribute("y", "rect");
    rect->setY(atof(attr));

    readAttribute("width", "rect");
    rect->setW(atof(attr));

    readAttribute("height", "rect");
    rect->setH(atof(attr));

    readAttribute("fill", "rect");
    rect->color(attr);

    return rect;
}

Shapes::Circle* ComponentShape::readCircleSVG(TiXmlElement* element){
    Shapes::Circle* circ = new Shapes::Circle();
    const char* attr = NULL;

    readAttribute("cx", "circ");
    circ->setX(atof(attr));

    readAttribute("cy", "circ");
    circ->setY(atof(attr));

    readAttribute("r", "circ");
    circ->setRadius(atof(attr));

    readAttribute("fill", "circ");
    circ->color(attr);

    return circ;
}


ComponentShape::~ComponentShape() {
    if(_container) delete _container;
}
