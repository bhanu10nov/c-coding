CROSS=gcc
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags --libs libnl-3.0)
all:
	gcc my_nl_monitor.c -o my-nl-monitor $(CFLAGS) -lnl-route-3
	gcc my_nl_get_ip_status.c -o my-nl-get-ip-status $(CFLAGS) -lnl-route-3
	
clean:
	rm -rf my-nl-monitor
	rm -rf my_nl_get_ip_status