#ifndef __GTK_CORE_WINDOW_H_
#define __GTK_CORE_WINDOW_H_

#include <gtkmm.h>
#include <iostream>
#include "GtkDraw.h"

class GtkCoreWindow : public Gtk::ApplicationWindow {
 protected:
    //Child widgets:
    Gtk::HBox _box;
    GtkDraw _gtkDraw;

 public:
    GtkCoreWindow();

    //Glib::RefPtr<SimpleAction> add_action(const Glib::ustring& name, const ActivateSlot& slot) override;

    virtual ~GtkCoreWindow();
 protected:
    //Signal handlers:
    void on_menu_others();

    bool on_key_press_event(GdkEventKey* event);

};

#endif
