#include "GtkDraw.h"
#include "EditWindow.h"

class GtkDraw::GtkGarbageActions {
	App* _app;
	GtkDraw* _draw;

public:
	GtkGarbageActions(App* a, GtkDraw* g){
		_app = a;
		_draw = g;
	}

	void connect_actions(Gtk::ApplicationWindow* w){
		w->add_action("new_resistor", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::new_resistor));
		w->add_action("new_voltage", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::new_voltage));
		w->add_action("new_wire", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::new_wire));
		w->add_action("start", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::start));
		w->add_action("edit_component", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::edit_component));
		w->add_action("remove_component", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::remove_component));
	}

	void new_resistor(){
		_app->keyPressed('r', 0, 0);
	}

	void new_voltage(){
		_app->keyPressed('v', 0, 0);
	}

	void new_wire(){
		_app->keyPressed('w', 0, 0);
	}

	void start(){
		_app->startSimulation();
	}

	void edit_component(){
		_app->editSelectedComponentEvent();
		EditWindow* w = EditWindow::create();
		if(w) w->show();
	}

	void remove_component(){
		_app->removeSelectedComponentEvent();
		_draw->force_redraw();
	}
};

GtkDraw::GtkDraw(): _app() {
	_mouseX = _mouseY = 0;
	set_size_request(500, 500);
	
	_foolishActions = new GtkGarbageActions(&_app, this);
	
	/* Adding events */
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::POINTER_MOTION_MASK);

	setup_popup_menu();
}

GtkDraw::~GtkDraw(){
	delete _foolishActions;
	delete _popupMenu;
}

void GtkDraw::force_redraw(){
	auto win = get_window();
	if (win) {
		Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
}

bool GtkDraw::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)  {
	
	_app.display(cr);

	return true;
}

void GtkDraw::on_new_component(){
	cout << "Selected: " << endl;
}

bool GtkDraw::on_button_press_event(GdkEventButton* button_event)  {
	Gtk::DrawingArea::on_button_press_event(button_event);

	_app.mouseClick(button_event->button, GDK_BUTTON_PRESS, button_event->x, button_event->y);
	force_redraw();

	if( (button_event->type == GDK_BUTTON_PRESS) && (button_event->button == 3) )
	{
		if(_app.selectComponentEvent(button_event->x, button_event->y)){
			if(!_popupMenu->get_attach_widget())	
				_popupMenu->attach_to_widget(*this);
		
			if(_popupMenu)
				_popupMenu->popup_at_pointer((GdkEvent*)button_event);
		}
	}
	else {
		_app.deselectComponentEvent();
	}

	return true;
}

bool GtkDraw::on_motion_notify_event(GdkEventMotion* motion_event)  {
	Gtk::DrawingArea::on_motion_notify_event(motion_event);
	
	_mouseX = motion_event->x;
	_mouseY = motion_event->y;
	_app.mouseMove(motion_event->x, motion_event->y);
	force_redraw();
}

bool GtkDraw::key_press_event(GdkEventKey* event) {
	_app.keyPressed(event->keyval, _mouseX, _mouseY);
	force_redraw();
}

void GtkDraw::connect_actions(Gtk::ApplicationWindow* w){
	_foolishActions->connect_actions(w);
}
 
 void GtkDraw::setup_popup_menu(){
	auto builder = Gtk::Builder::create();

	try
	{
		builder->add_from_file("Gtk/popup.ui.xml");
	}
	catch (const Glib::Error& ex)
	{
		std::cerr << "Building menus failed: " << ex.what();
	}	

	auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(
		 builder->get_object("component-popup")
	);

	_popupMenu = new Gtk::Menu(gmenu);
}