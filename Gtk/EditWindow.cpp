#include "EditWindow.h"
#include <iostream>
#include <exception>

EditWindow::EditWindow(BaseObjectType* cobject, 
    const Glib::RefPtr<Gtk::Builder>& refBuilder): Gtk::Window(cobject),
    _builder(refBuilder) {
    show_all_children();

}

EditWindow* EditWindow::create(){
    EditWindow* window = NULL;
    try{
        auto refBuilder = Gtk::Builder::create_from_file("Gtk/editwindow.glade");
        
        refBuilder->get_widget_derived("edit_window", window);
        if (!window)
            std::cerr << "Creating EditWindow \n"; 
    }catch(const Glib::Error& ex){
        std::cerr << "Creating EditWindow " << ex.what();
    }
    return window;
}

EditWindow::~EditWindow(){

}