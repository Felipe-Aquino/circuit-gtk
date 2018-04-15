project('tutorial', 'cpp')

subdir('Useful')
subdir('Shapes')
subdir('Application')
subdir('Gtk')

gtkmmdep = dependency('gtkmm-3.0')
gtkdep = dependency('gtk+-3.0')
executable(
    'circuit', 
    'circuit.cpp', 
    gui_app: true,
    link_with: [lgtk, lapp, lshape, luseful],
    dependencies: [gtkmmdep, gtkdep],
)
