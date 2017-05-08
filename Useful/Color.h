#ifndef __COLOR_H_
#define __COLOR_H_

#include <gtkmm/drawingarea.h>
#include <iostream>
#include <string>

using namespace std;

namespace Color{

    typedef enum {
        WHITE, BLACK, GREEN, RED, BLUE, GREY, SILVER, YELLOW, LIME, AQUA, CIAN,
        MARRON, BROWN, PURPLE, NAVY, FUCHSIA, PINK, OLIVE, TEAL
    } TColor;

    void setColor(const Cairo::RefPtr<Cairo::Context>& cr, TColor color);
    void toRGBArray(TColor color, float rgb[3]);
    void toRGBArrayLighter(TColor color, float rgb[3]);
    void toRGBArrayDarker(TColor color, float rgb[3]);
    TColor stringToTColor(string Color);
    string TColorToString(TColor Color);
};

#endif
