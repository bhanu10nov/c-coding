INCLUDE=../lib/
LIBS=../lib/
all:
	gcc -I $(INCLUDE) -L$(LIBS) -Wl,-rpath=$(LIBS) -Wall -o app2 app2.c -lfoo
clean:
	rm app2
