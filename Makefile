all: config move run

config:
	@meson builddir

move:
	@cp Gtk/*.ui builddir/Gtk/
	@cp -R SVGs/ builddir/SVGs/

run:
	@cd builddir; ninja
	@cd builddir; ./circuit

find:
	@grep -rnw ./ -e $(info)

etags:
	@ctags -e --c-types=+l -R

clean:
	@rm -rf builddir
