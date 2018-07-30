#ifndef __COMPONENT_INFO_H_
#define __COMPONENT_INFO_H_

#include <vector>
#include "../Useful/Signal.hpp"
#include "../Useful/Primitive.h"

using namespace std;
using namespace Primitive;

class Property {
    string _name;
    Object* _value;
public:
    Signal<> onChange;
    const string& name;

    Property(): name(_name) {
        _name = "";
        _value = NULL;
    }

    Property(string name, Object* value): name(_name) {
        this->_name = name;
        this->_value = value;
    }

    ~Property(){
        if(_value) delete _value;
    }

    void setName(string name) {
        _name = name;
    }

    void setValue(Object* value) {
        if(_value) delete _value;
        _value = value;
        onChange.emit();
    }

    Object* getValue() {
        return _value;
    }
};

class CompInfo{
public:
    string name;
    vector<Property*> properties;
    ~CompInfo(){
        for(auto p : properties){
            if(p) delete p;
        }
    }
};

#endif
