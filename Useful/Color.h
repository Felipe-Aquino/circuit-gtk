#ifndef __COLOR_H_
#define __COLOR_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Color {
    float rgb[4];

    float r();
    float g();
    float b();

    void set(float r, float g, float b);

    Color();
    Color(float r, float g, float b);
    Color(Color& color);
    Color(string color);
    Color(const char* color);

    friend ostream& operator<<(ostream& os, Color& color);
};

#endif
