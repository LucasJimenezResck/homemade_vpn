#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h> //register_chrdev
static int major_nr;



static int __init cdev_basic_init(void);
static void __exit cdev_basic_exit(void);
static ssize_t chrdev_read(struct file *f, char __user *u, size_t, loff_t *o);


static ssize_t chrdev_read(struct file *f, char __user *u, size_t, loff_t *o) {
	printk(KERN_INFO"Read for chrdev was called\n");
	return 0;
} 
//To confirm arguments for file_operations check out https://elixir.bootlin.com/linux/v6.18/source
//It is a browser for the source-files of many Linux-Kernel-Versions
static struct file_operations fops = {
	.read = chrdev_read,
};

static int __init cdev_basic_init(void) {
	//Register a major device number, 0 means find a free number
	//Add a label and assign to the file-operations structure
	major_nr = register_chrdev(0, "basic_cdev", &fops);
	if(major_nr < 0) {
		printk(KERN_ALERT"Error registering chrdev\n");
		return major_nr;
	}
	printk(KERN_INFO"Major number: %i\n", major_nr);
	return 0;
}

static void __exit cdev_basic_exit(void) {
	printk(KERN_INFO"Goodbye Viki! Removing module\n");
	unregister_chrdev(major_nr, "basic_cdev");
}


module_init(cdev_basic_init);
module_exit(cdev_basic_exit);

//Metadata can be accessed by calling $ modinfo <.ko-file>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lucas Jimenez Resck");
MODULE_DESCRIPTION("Registering a character device");
