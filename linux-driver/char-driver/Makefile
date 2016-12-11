CONFIG_MODULE_SIG=n
obj-m += hello.o

KDIR=/lib/modules/4.4.0-45-generic/build
PWD=/home/bhanu/Bhanu/learning/c-coding/linux-driver/char-driver

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.0 *.ko *.mod.* *.symvers *.order
