#include <linux/module.h>
#include <linux/init.h>

//Keyword static limits the functions' visibility and linkage.
//They cannot be accessed outside this module
//Macros __init and __exit increase the modules' readability, in case a file is very large, by searching for these keyowrds,
//the init and exit functions can be easily found 
static int __init hello_init(void);
static void __exit hello_exit(void);


static int __init hello_init(void) {
	//Testing with all different log-levels just because
	//Emergency was commented out because it spawns into every open terminal, which can be annoying
	//printk(KERN_EMERG"Hello Viki! Calling from Raspberry Pi Kernel!\n");
	printk(KERN_ALERT"Hello Viki! Calling from Raspberry Pi Kernel!\n");
	printk(KERN_CRIT"Hello Viki! Calling from Raspberry Pi Kernel!\n");
	printk(KERN_ERR"Hello Viki! Calling from Raspberry Pi Kernel!\n");
	printk(KERN_WARNING"Hello Viki! Calling from Raspberry Pi Kernel!\n");
	printk(KERN_NOTICE"Hello Viki! Calling from Raspberry Pi Kernel!\n");
	printk(KERN_INFO"Hello Viki! Calling from Raspberry Pi Kernel!\n");
	printk(KERN_DEBUG"Hello Viki! Calling from Raspberry Pi Kernel!\n");
	return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO"Goodbye Viki! Removing module\n");
}


module_init(hello_init);
module_exit(hello_exit);

//Metadata can be accessed by calling $ modinfo <.ko-file>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lucas Jimenez Resck");
MODULE_DESCRIPTION("Simple kernel Module for Raspberry Pi 4B");
