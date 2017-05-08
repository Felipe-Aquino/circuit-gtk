#include "GtkCoreApp.h"
#include "GtkCoreWindow.h"
#include <iostream>

GtkCoreApp::GtkCoreApp(): Gtk::Application("circuit.gtk.core.app") {
	Glib::set_application_name("Circuit");
}

Glib::RefPtr<GtkCoreApp> GtkCoreApp::create() {
	return Glib::RefPtr<GtkCoreApp>(new GtkCoreApp());
}

void GtkCoreApp::on_startup() {
	//Call the base class's implementation:
	Gtk::Application::on_startup();

	//Create actions for menus and toolbars.
	//We can use add_action() because Gtk::Application derives from Gio::ActionMap.

	//File|New sub menu:
	add_action("newstandard",
	sigc::mem_fun(*this, &GtkCoreApp::on_menu_file_new_generic));

	add_action("newfoo",
	sigc::mem_fun(*this, &GtkCoreApp::on_menu_file_new_generic));

	add_action("newgoo",
	sigc::mem_fun(*this, &GtkCoreApp::on_menu_file_new_generic));

	//File menu:
	add_action("quit", sigc::mem_fun(*this, &GtkCoreApp::on_menu_file_quit));

	//Help menu:
	add_action("about", sigc::mem_fun(*this, &GtkCoreApp::on_menu_help_about));

	_builder = Gtk::Builder::create();

	try
	{
		_builder->add_from_file("Gtk/menu.ui.xml");
	}
	catch (const Glib::Error& ex)
	{
		std::cerr << "Building menus failed: " << ex.what();
	}

	//Get the menubar and the app menu, and add them to the application:
	auto object = _builder->get_object("menu-example");
	auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);

	if (!(gmenu)) {
		g_warning("GMenu or AppMenu not found");
	}
	else {
		set_menubar(gmenu);
	}
}

void GtkCoreApp::on_activate() {
	create_window();
}

void GtkCoreApp::create_window() {
	auto win = new GtkCoreWindow();

	//Make sure that the application runs for as long this window is still open:
	add_window(*win);

	//Delete the window when it is hidden.
	//That's enough for this simple example.
	win->signal_hide().connect(sigc::bind<Gtk::Window*>(
	sigc::mem_fun(*this, &GtkCoreApp::on_window_hide), win));

	win->show_all();
}

void GtkCoreApp::on_window_hide(Gtk::Window* window){
	delete window;
}

void GtkCoreApp::on_menu_file_new_generic() {
	std::cout << "A File|New menu item was selected." << std::endl;
}

void GtkCoreApp::on_menu_file_quit() {
	std::cout << G_STRFUNC << std::endl;
	quit(); 

	std::vector<Gtk::Window*> windows = get_windows();
	if (windows.size() > 0)
		windows[0]->hide(); // In this simple case, we know there is only one window.
}

void GtkCoreApp::on_menu_help_about() {
	std::cout << "App|Help|About was selected." << std::endl;
}
