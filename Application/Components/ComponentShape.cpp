#include "ComponentShape.h"

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


class ComponentShape::Container {
public:
    Shapes::Shape* shape;
    Container(){ 
        shape = NULL; 
    }
    bool isInside(float x, float y){
        if(shape) return shape->isInside(x,y);
    }
    
    void draw(const Cairo::RefPtr<Cairo::Context>& cr){
        if(shape) shape->draw(cr);
    }

    void setXY(float x, float y){
        if(shape){
            shape->setX(x);
            shape->setY(y);
        }
    }

    float getX(){
        if(shape){
            return shape->getX();
        }
    }

    float getY(){
        if(shape){
            return shape->getY();
        }
    }

    ~Container(){ 
        if(shape) delete shape;
    }
};

ComponentShape::ComponentShape(){
    _container = new Container();
}

bool ComponentShape::isInside(float x, float y){
    _container->isInside(x, y);
}

void ComponentShape::draw(const Cairo::RefPtr<Cairo::Context>& cr){
    for(auto r : rects){
        r->draw(cr);
    }
    for(auto c : circs){
        c->draw(cr);
    }
}

void ComponentShape::setXY(float x, float y){
    float dx = x - _container->getX();
    float dy = y - _container->getY();

    for(auto r : rects){
        r->setX((int)(r->getX() + dx));
        r->setY((int)(r->getY() + dy));
    }
    for(auto c : circs){
        c->setX(c->getX() + dx);
        c->setY(c->getY() + dy);
    }
    _container->setXY(x, y);
}

Shapes::Shape* ComponentShape::getContainerShape(){
    return _container->shape;
}

void ComponentShape::readFromSvg(std::string path){
    if(path[0] == '~'){
        path.erase(0,1);
        string s(getenv("HOME"));
        path = s + path;
    }

    TiXmlDocument doc(path.c_str());

    if(!doc.LoadFile()){
        throw SvgReaderException(doc.ErrorDesc());
    }

    TiXmlElement *svg = doc.FirstChildElement("svg");
    if(svg == NULL){
        doc.Clear();
        throw SvgReaderException("Fail to load file: No SVG element!");
    }


    TiXmlElement* container = svg->FirstChildElement("rect");
    if(container){
        Shapes::Rectangle* r = new Shapes::Rectangle();
        _container->shape = r;
        readRectSVG(container, *r);
        r->print();
    } 
    else 
    {
        container = svg->FirstChildElement("circle");
        if(container){
            Shapes::Circle* c = new Shapes::Circle(); 
            _container->shape = c;
            readCircleSVG(container, *c);
        } else {
            throw SvgReaderException("Nor a rect or circle container was found!");
        }
    }

    for(TiXmlElement *elem = container->FirstChildElement(); elem!=NULL; elem = elem->NextSiblingElement()){
        string elemName = elem->Value();
        if(elemName == "circle"){
            Shapes::Circle* c = new Shapes::Circle();
            readCircleSVG(elem, *c);
            c->print();
            circs.push_back(c);
        }
        else if(elemName == "rect"){
            Shapes::Rectangle* r = new Shapes::Rectangle();
            readRectSVG(elem, *r);
            r->print();
            rects.push_back(r);
        }
    }

}

void ComponentShape::readRectSVG(TiXmlElement* element, Shapes::Rectangle& rect){
    readAttriute(element, "x", "rect");
    rect.setX(atof(attr));

    readAttriute(element, "y", "rect");
    rect.setY(atof(attr));

    readAttriute(element, "width", "rect");
    rect.setW(atof(attr));

    readAttriute(element, "height", "rect");
    rect.setH(atof(attr));

    readAttriute(element, "fill", "rect");
    string s(attr);
    rect.setColor(stringToTColor(s));
}

void ComponentShape::readCircleSVG(TiXmlElement* element, Shapes::Circle& circ){
    readAttriute(element, "cx", "circ");
    circ.setX(atof(attr));

    readAttriute(element, "cy", "circ");
    circ.setY(atof(attr));

    readAttriute(element, "r", "circ");
    circ.setRadius(atof(attr));

    readAttriute(element, "fill", "circ");
    string s(attr);
    circ.setColor(stringToTColor(s));
}

const string& ComponentShape::miss_msg(string attr, string tag){
    msg = "Missing the '" + attr + "' attribute in a " + tag + " from svg file.";
    return msg;
}

void ComponentShape::readAttriute(TiXmlElement* element, const char* attrname, const char* type){
    attr = element->Attribute(attrname);
    if(!attr){ 
        throw SvgReaderException(miss_msg(attrname, type)); 
    }
}

ComponentShape::~ComponentShape(){
    if(_container) delete _container;
}