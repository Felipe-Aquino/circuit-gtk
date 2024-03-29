all: generateobj compile
	@echo "Done."

GTKFLAGS:= `pkg-config gtkmm-3.0 --cflags --libs`
generateobj:
	g++ -std=c++11 -c Application/*.cpp $(GTKFLAGS)
	g++ -std=c++11 -c Gtk/*.cpp $(GTKFLAGS)

APPOBJS:= App.o Canvas.o  Resistor.o Wire.o ComponentShape.o IndepVSource.o CircuitSimulator.o
USEFULOBJS:= LinkedList.o Color.o Vector.o Point.o Matrix.o tinyxml.o tinystr.o tinyxmlerror.o tinyxmlparser.o 
SHAPESOBJS:= Circle.o Rectangle.o 
GTKOBJS:= GtkCoreApp.o GtkCoreWindow.o GtkDraw.o 
PROJNAME:=circuit
compile:
	g++ -std=c++11 -o $(PROJNAME) $(PROJNAME).cpp $(TINYOBJS) $(APPOBJS) $(USEFULOBJS) $(SHAPESOBJS) $(GTKOBJS) $(GTKFLAGS)

clean:
	@rm -f *.o
