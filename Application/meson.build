gtkmmdep = dependency('gtkmm-3.0')
gtkdep = dependency('gtk+-3.0')

lapp = shared_library(
    'application',
    'Components/ComponentShape.cpp',
    'Components/Wire.cpp',
    'Components/Resistor.cpp',
    'Components/Capacitor.cpp',
    'Components/IVSource.cpp',
    'CircuitSimulator.cpp',
    'App.cpp',
    link_with: [luseful, lshape],
    dependencies:[gtkmmdep, gtkdep]
)