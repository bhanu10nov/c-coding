CROSS=gcc
PKGCONFIG=`pkg-config --cflags dbus-1 dbus-glib-1 glib-2.0 gio-unix-2.0 --libs glib-2.0 dbus-1 dbus-glib-1`
all:	codegen
	$(CROSS) $(PKGCONFIG) server.c calc-generated.c -lglib-2.0 -o server
codegen:
	gdbus-codegen --generate-c-code	calc-generated ../server.xml
clean:
	rm -rf server *-generated.c *-generated.h
