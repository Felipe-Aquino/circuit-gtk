#include "Gtk/GtkCoreApp.h"

int main(int argc, char* argv[]) {
    auto application = GtkCoreApp::create();

    int status = application->run(argc, argv);
    return status;
}
