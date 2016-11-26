#include <linux/init.h>
#include <linux/module.h>

static int hello_init(void)
{
	printk("hello_init");
	return 0;
}

static int hello_exit(void)
{
	printk("hello_exit");
	return 0;
}

module_init(hello_init);
module_exit(hello_exit);
