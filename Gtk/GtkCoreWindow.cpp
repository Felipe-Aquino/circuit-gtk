#include "GtkCoreWindow.h"

GtkCoreWindow::GtkCoreWindow(): Gtk::ApplicationWindow(), _box(), _gtkDraw() {
    set_title("Circuit");
    set_default_size(300, 100);

    add_events(Gdk::KEY_PRESS_MASK);

    //Edit menu:
    add_action("copy", sigc::mem_fun(*this, &GtkCoreWindow::on_menu_others));
    add_action("paste", sigc::mem_fun(*this, &GtkCoreWindow::on_menu_others));

    _gtkDraw.connect_actions(this);

    //Help menu:
    add_action("about", sigc::mem_fun(*this, &GtkCoreWindow::on_menu_others));

    _box.pack_start(_gtkDraw, true, true, 3);
    add(_box);
}

/*Glib::RefPtr<SimpleAction> GtkCoreWindow::add_action(const Glib::ustring& name, const ActivateSlot& slot){
	Gtk::ApplicationWindow::add_action(name, slot);

}*/

GtkCoreWindow::~GtkCoreWindow(){
}

void GtkCoreWindow::on_menu_others(){
    std::cout << "A menu item was selected." << std::endl;
}

bool GtkCoreWindow::on_key_press_event(GdkEventKey* event) {
    Gtk::ApplicationWindow::on_key_press_event(event);
    _gtkDraw.key_press_event(event);
    return true;
}
