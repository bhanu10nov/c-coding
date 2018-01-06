CROSS=gcc
CFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags --libs libnl-3.0)
all:
	gcc my_nl_monitor.c -o my-nl-monitor.out $(CFLAGS) -lnl-route-3
	gcc my_nl_get_ip_status.c -o my-nl-get-ip-status.out $(CFLAGS) -lnl-route-3
	gcc my_nl_route_modify.c -o my-nl-route-modify.out $(CFLAGS) -lnl-route-3
	
clean:
	rm -rf my-nl-monitor.out
	rm -rf my-nl-get-ip-status.out
	rm -rf my-nl-route-modify.out