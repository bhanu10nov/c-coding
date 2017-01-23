CROSS=gcc
PKGCFGLS=`pkg-config --cflags glib-2.0 gio-unix-2.0`
PKGLIBS=`pkg-config --libs glib-2.0`
all:	codegen
	$(CROSS) -I/usr/include/dbus-1.0 -I/usr/lib/i386-linux-gnu/dbus-1.0/include -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -ldbus-glib-1 -ldbus-1 -lgobject-2.0 -lglib-2.0 server.c calc-generated.c -o server
codegen:
	gdbus-codegen --generate-c-code	calc-generated ../server.xml
clean:
	rm -rf server *-generated.c *-generated.h
