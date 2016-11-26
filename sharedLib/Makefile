subdir= lib app1 app2
all:
	for dir in $(subdir); do \
		$(MAKE) -C $$dir; \
	done
clean:
	for dir in $(subdir); do \
		$(MAKE) clean -C $$dir; \
	done


