#ifndef __GTK_CORE_APPH_
#define __GTK_CORE_APPH_

	#include <gtkmm/application.h>
	#include <gtkmm/builder.h>
	#include <glibmm.h>


	class GtkCoreApp : public Gtk::Application {
		Glib::RefPtr<Gtk::Builder> _builder;

	public:
		static Glib::RefPtr<GtkCoreApp> create();

	protected:
		GtkCoreApp();

		//Overrides of default signal handlers:
		void on_startup() override;
		void on_activate() override;

	private:
		void create_window();

		void on_window_hide(Gtk::Window* window);
		void on_menu_file_new_generic();
		void on_menu_file_quit();
		void on_menu_help_about();

	};

#endif
