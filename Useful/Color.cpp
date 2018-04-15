#include "Color.h"
#define TEST(chr, min, max) (chr >= min && chr <= max)


Color::Color() {
    rgb[0] = 0.0;
    rgb[1] = 0.0;
    rgb[2] = 0.0;
    rgb[3] = 1.0;
}

Color::Color(float nr, float ng, float nb) {
    rgb[0] = nr;
    rgb[1] = ng;
    rgb[2] = nb;
    rgb[3] = 1.0;
}

Color::Color(Color& color) {
    rgb[0] = color.rgb[0];
    rgb[1] = color.rgb[1];
    rgb[2] = color.rgb[2];
    rgb[3] = 1.0;
}

float Color::r() { return rgb[0]; }
float Color::g() { return rgb[1]; }
float Color::b() { return rgb[2]; }

void Color::set(float nr, float ng, float nb) {
    rgb[0] = nr;
    rgb[1] = ng;
    rgb[2] = nb;
    rgb[3] = 1.0;
}

Color::Color(string color) {
    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
    rgb[3] = 1.0;
    if(color.size() == 7 && color[0] == '#') {
        color.erase(0, 1);
        for(char c : color){
            if(!TEST(c, '0', '9') && !TEST(c, 'A', 'F') && !TEST(c, 'a', 'f'))
                return;
        }

        unsigned x = 0;
        stringstream ss;
        for(int i = 0; i < 3; i++){
            ss << std::hex << color.substr(2*i, 2);
            ss >> x;
            ss.clear();
            rgb[i] = x/255.0;
        }
    }
}

Color::Color(const char* color) {
    string _color(color);

    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
    rgb[3] = 1.0;
    if(_color.size() == 7 && _color[0] == '#') {
        _color.erase(0, 1);
        for(char c : _color){
            if(!TEST(c, '0', '9') && !TEST(c, 'A', 'F') && !TEST(c, 'a', 'f'))
                return;
        }

        unsigned x = 0;
        stringstream ss;
        for(int i = 0; i < 3; i++){
            ss << std::hex << _color.substr(2*i, 2);
            ss >> x;
            ss.clear();
            rgb[i] = x/255.0;
        }
    }
}

ostream& operator<<(ostream& os, Color& color) {
    os << "{r= " << color.r() << ", g= " << color.g() << ", b= " << color.b() << "}";
    return os;
}
