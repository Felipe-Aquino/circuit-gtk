#ifndef __FAST_GUI_H_
#define __FAST_GUI_H_

#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <gtkmm/application.h>
#include <iostream>

namespace fst {
    void Text(std::string txt);
    bool Button(std::string txt);
    void Spin(float &v, float step);
    void Toggle(std::string txt, bool &v);
    void Slider(float &v, float min, float max);
    void TextEntry(std::string &text);
    void BeginExpander(std::string txt);
    void EndExpander(void);
    void SameLine(void);

    void init(const Cairo::RefPtr<Cairo::Context>& cr);
    void pre_init();
    void end();

    void render(const Cairo::RefPtr<Cairo::Context>& cr);

    void mouse_press(GdkEventButton* event);
    void mouse_release(GdkEventButton* event);
    void mouse_move(GdkEventMotion* event);
    bool key_event(GdkEventKey* event);
}

#endif // __FAST_GUI_H_
