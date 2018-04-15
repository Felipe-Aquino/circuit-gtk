#include "EditDialog.h"
#include <iostream>
#include <string>

#define DCAST(type, obj) dynamic_cast<type*>(obj)

EditDialog::EditDialog(Gtk::Window& parent, CompInfo& ci):
    Gtk::Dialog("Edit: " + ci.name, parent, true), info(ci) {

    set_default_size(300, 200);

    add_button("Calcel", 0);
    auto* ok = add_button("OK", 1);
    ok->signal_clicked().connect(sigc::mem_fun(*this, &EditDialog::save));

    generate_layout();
    show_all();
}

void EditDialog::generate_layout() {
    grid = new Gtk::Grid();
    grid->set_column_spacing(3);
    grid->set_margin_start(6);
    int i = 0;

    for(auto* p: info.properties) {
        Gtk::Label* name = new Gtk::Label(p->name);
        Gtk::Entry* value = new Gtk::Entry();
        grid->attach(*name , 0, i, 1, 1);
        grid->attach(*value, 1, i++, 2, 1);

        Primitive::Object* o = p->getValue();
        if(p->type == INT) {
            int v = 0;
            o->load(v);
            value->set_text(to_string(v));
        }
        else if(p->type == FLOAT) {
            float v = 0.0;
            o->load(v);
            value->set_text(to_string(v));
        }
        else if(p->type == STRING) {
            string v;
            o->load(v);
            value->set_text(v);
        }
        entries.push_back(value);
    }
    auto* box = get_content_area();
    box->pack_start(*grid, false, false, 3);
}

void EditDialog::save(){
    int i = 0;
    Primitive::Object* o = NULL;

    for(auto* p: info.properties) {
        auto* value = entries[i++];

        switch(p->type) {
        case INT:
            o = new Int(atof(value->get_text().c_str()));
            break;
        case FLOAT:
            o = new Float(atof(value->get_text().c_str()));
            break;
        case STRING:
            o = new String(value->get_text());
            break;
        default:
            break;
        }
        p->setValue(o);
    }
}

void EditDialog::cancel(){
}

EditDialog::~EditDialog(){
    for(auto* c: grid->get_children())
        if(c) delete c;

    if(grid) delete grid;
}
