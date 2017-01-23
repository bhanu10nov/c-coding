CROSS=gcc
PKGCFGLS=`pkg-config --cflags glib-2.0`
PKGLIBS=`pkg-config --libs glib-2.0`
all:
	$(CROSS) $(PKGCFGLS) $(PKGLIBS) client.c -o client
clean:
	rm -rf client
