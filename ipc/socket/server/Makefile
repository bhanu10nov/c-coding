CROSS=gcc
PKGCFGLS=`pkg-config --cflags glib-2.0 gio-unix-2.0`
PKGLIBS=`pkg-config --libs glib-2.0`
all:
	$(CROSS) $(PKGCFGLS) $(PKGLIBS) server.c -o server
clean:
	rm -rf server
