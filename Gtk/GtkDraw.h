#ifndef __GTK_DRAW_H_
#define __GTK_DRAW_H_

    #include <gtkmm.h>
    #include <iostream>
    #include "../Application/App.h"

    using namespace std;

    class GtkDraw : public Gtk::DrawingArea {
        App _app;
        class GtkGarbageActions;
		GtkGarbageActions* _foolishActions;
    public:
        GtkDraw();
        virtual ~GtkDraw();

        bool key_press_event(GdkEventKey* event);

        void on_new_component();

        void force_redraw();

        void connect_actions(Gtk::ApplicationWindow* w);
    private:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
        bool on_button_press_event(GdkEventButton* button_event) override;
        bool on_motion_notify_event(GdkEventMotion* motion_event) override;
    };

#endif