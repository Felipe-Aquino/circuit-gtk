gtkmmdep = dependency('gtkmm-3.0')
gtkdep = dependency('gtk+-3.0')

lshape = shared_library(
    'shapes',
    'Circle.cpp',
    'Rectangle.cpp',
    link_with: luseful,
    dependencies: [gtkmmdep, gtkdep]
)