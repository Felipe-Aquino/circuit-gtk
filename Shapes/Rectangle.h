#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

    #include <string>
    #include "Shape.h"

    using namespace std;

    namespace Shapes {
        class Rectangle : public Shape {
            float _w;
            float _h;

        public:

            Rectangle();
            Rectangle(Rectangle &);
            Rectangle(float, float, float, float);
            void draw(const Cairo::RefPtr<Cairo::Context>& cr);

            void print();
            bool isInside(float x, float y);

            void setW(float);
            void setH(float);

            float getW();
            float getH();

            ~Rectangle();
        };
    }

#endif
