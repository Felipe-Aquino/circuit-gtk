#include <iostream>
#include <string>

namespace Primitive{
    using namespace std;

    class Object {
    protected:
        void* value;
    public:
        Object(){ value = NULL; }

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

    namespace {
        template<class T>
            class BaseObject : public Object{
        public:
            BaseObject(T v){ value = new T[1]{v}; }
            virtual void load(T& v){ v = *(T*)value; }
            ~BaseObject(){ T* v = (T*)value; if(v) delete[] v; }
        };

        template<class T>
            class HardObject : public Object{
        public:
            HardObject(T v){ value = new T(v); }
            virtual void load(T& v){ v = *(T*)value; }
            ~HardObject(){ T* v = (T*)value; if(v) delete v; }
        };
    }

    typedef BaseObject<int> Int;
    typedef BaseObject<long> Long;
    typedef BaseObject<unsigned> Uint;
    typedef BaseObject<float> Float;
    typedef BaseObject<double> Double;
    typedef HardObject<string> String;
}
