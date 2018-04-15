#ifndef __EDITDIALOG_H_
#define __EDITDIALOG_H_

#include <gtkmm.h>
#include <vector>
#include "../Application/CompInfo.h"

using Gtk::Window;

class EditDialog : public Gtk::Dialog {
public:
    EditDialog(Gtk::Window& parent, CompInfo& ci);
    void save();
    void cancel();
    ~EditDialog();

private:
    CompInfo& info;
    vector<Gtk::Entry*> entries;
    Gtk::Grid* grid;

    void generate_layout();
};

#endif // __EDITDIALOG_H_
