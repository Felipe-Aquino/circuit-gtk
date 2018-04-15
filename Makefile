all: config move run

config:
	@meson builddir

move:
	@cp Gtk/*.ui builddir/Gtk/
	@cp -R SVGs/ builddir/SVGs/

run:
	@cd builddir; ninja
	@cd builddir; ./circuit

clean:
	@rm -rf builddir
