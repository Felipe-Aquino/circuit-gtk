#include "GtkDraw.h"

class GtkDraw::GtkGarbageActions {
	App* _app;

public:
	GtkGarbageActions(App* a){
		_app = a;
	}

	void connect_actions(Gtk::ApplicationWindow* w){
		w->add_action("new_resistor", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::new_resistor));
		w->add_action("new_voltage", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::new_voltage));
		w->add_action("new_wire", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::new_wire));
		w->add_action("start", sigc::mem_fun(*this, &GtkDraw::GtkGarbageActions::start));
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
};

GtkDraw::GtkDraw(): _app() {
	set_size_request(500, 500);
	
	 _foolishActions = new GtkGarbageActions(&_app);
	
	/* Adding events */
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::POINTER_MOTION_MASK);
}

GtkDraw::~GtkDraw(){
	delete _foolishActions;
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
}

bool GtkDraw::on_motion_notify_event(GdkEventMotion* motion_event)  {
	Gtk::DrawingArea::on_motion_notify_event(motion_event);
	
	_app.mouseMove(motion_event->x, motion_event->y);
	force_redraw();
}

bool GtkDraw::key_press_event(GdkEventKey* event) {
	_app.keyPressed(event->keyval, 0, 0);
	force_redraw();
}

void GtkDraw::connect_actions(Gtk::ApplicationWindow* w){
	_foolishActions->connect_actions(w);
}
 