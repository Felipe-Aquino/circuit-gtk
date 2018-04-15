gtkmmdep = dependency('gtkmm-3.0')
gtkdep = dependency('gtk+-3.0')

lgtk = shared_library(
    'gtk',
    'GtkCoreApp.cpp',
    'GtkCoreWindow.cpp',
    'GtkDraw.cpp',
    'EditDialog.cpp',
    link_with: [luseful, lapp],
    dependencies:[gtkmmdep, gtkdep]
)