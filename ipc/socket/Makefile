subdir=client server
all:
	for dir in $(subdir); do \
		$(MAKE) -C $$dir; \
	done
clean:
	for dir in $(subdir); do \
		$(MAKE) clean -C $$dir; \
	done

