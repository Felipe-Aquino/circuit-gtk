#ifndef __EDITWINOW_H_
#define __EDITWINOW_H_

#include <gtkmm.h>

using Gtk::Window;

class EditWindow : public Gtk::Window {
    Glib::RefPtr<Gtk::Builder> _builder;
public:
    EditWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static EditWindow* create();
    ~EditWindow();
};

#endif