#include <iostream>
#include <string>
#include <type_traits>

enum Type {
    NONE, INT, UINT, LONG, FLOAT, DOUBLE, STRING
};

template <typename T>
Type ToType() {
    if (std::is_same<T, int>::value) return INT;
    if (std::is_same<T, unsigned>::value) return UINT;
    if (std::is_same<T, long>::value) return LONG;
    if (std::is_same<T, float>::value) return FLOAT;
    if (std::is_same<T, double>::value) return DOUBLE;
    if (std::is_same<T, std::string>::value) return STRING;
    return NONE;
}

namespace Primitive {
    using namespace std;

    class Object {
    protected:
        void* value;
    public:
        Type type;
        Object(){ value = NULL; type = NONE; }

        virtual void load(unsigned& v){}
        virtual void load(int& v){}
        virtual void load(long& v){}
        virtual void load(float& v){}
        virtual void load(double& v){}
        virtual void load(string& v){}
        void* getValue(){ return value; }
        void setValue(void* value){ this->value = value; }

        virtual ~Object(){}
    };

    template<class T>
    class BaseObject : public Object{
    public:
        BaseObject(T v){ value = new T[1]{v}; type = ToType<T>(); }
        virtual void load(T& v){ v = *(T*)value; }
        virtual void set(T v){ *(T*)value = v; }
        T get(){ return *(T*)value; }
        virtual ~BaseObject(){ if(value) delete[] (T*)value; }
    };

    template<class T>
    class HardObject : public Object{
    public:
        HardObject(T v){ value = new T(v); type = ToType<T>(); }
        virtual void load(T& v){ v = *(T*)value; }
        virtual void set(T v){ *(T*)value = v; }
        T get(){ return *(T*)value; }
        virtual ~HardObject(){ if(value) delete (T*)value; }
    };

    typedef BaseObject<int> Int;
    typedef BaseObject<long> Long;
    typedef BaseObject<unsigned> Uint;
    typedef BaseObject<float> Float;
    typedef BaseObject<double> Double;
    typedef HardObject<string> String;
}
