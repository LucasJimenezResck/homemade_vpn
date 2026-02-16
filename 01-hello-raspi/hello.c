#include <linux/module.h>
#include <linux/init.h>

int hello_init(void) {
	printk(KERN_INFO"Hello Viki! Calling from Raspberry Pi Kernel!\n");
	return 0;
}

void hello_exit(void) {
	printk(KERN_INFO"Goodbye Viki! Removing module\n");
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple kernel Module for Raspberry Pi 4");
