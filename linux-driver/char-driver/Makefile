obj-m += hello.o

KDIR=/usr/src/linux-4.4

all:
	$(MAKE) -C $(KDIR) SUBDIR=$(PWD) modules

clean:
	rm -rf *.0 *.ko *.mod.* *.symvers *.order
