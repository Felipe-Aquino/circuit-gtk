gtkmmdep = dependency('gtkmm-3.0')
gtkdep = dependency('gtk+-3.0')

luseful = shared_library(
    'useful',
    'Math/Point.cpp',
    'Math/Vector.cpp',
    'Math/Matrix.cpp',
    'tinyxml/tinystr.cpp',
    'tinyxml/tinyxml.cpp',
    'tinyxml/tinyxmlerror.cpp',
    'tinyxml/tinyxmlparser.cpp',
    'Color.cpp',
    'report.cpp',
    dependencies:[gtkmmdep, gtkdep]
)