INCLUDE=../lib/
LIBS=../lib/
all:
	gcc -I $(INCLUDE) -L$(LIBS) -Wl,-rpath=$(LIBS) -Wall -o app1 app1.c -lfoo
clean:
	rm app1
