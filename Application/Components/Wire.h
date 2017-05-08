#ifndef __WIRE_H_
#define __WIRE_H_

    #include "../Component.h"
    #include "../../Useful/Math/Point.h"
    #include "../../Useful/Math/Vector.h"

    using namespace Math;

    class Wire  : public Component {
        Point p0, p1;
        bool _firstClick, _secondClick;
        double ang;
        int type;

        bool _delete;
        bool _drawMenu;
        bool _checked;
        int _current_col;
    public:
        Wire();
        void Draw(const Cairo::RefPtr<Cairo::Context>& cr);
        bool IsReady();
        void MouseOverEvent(int, int);
        void MouseClickEvent(int, int, int, int);
        void SetEquation(Matrix&, Matrix&, int, int&, int&);
        ~Wire();
    
    };

#endif
