#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h> //register_chrdev
static int major_nr;



static int __init cdev_basic_init(void);
static void __exit cdev_basic_exit(void);
static int chrdev_open(struct inode *inode, struct file *filp);
static ssize_t chrdev_read(struct file *f, char __user *u, size_t, loff_t *o);
static int chrdev_release(struct inode *inode, struct file *filp);


static int chrdev_open(struct inode *inode, struct file *filp) {
	printk(KERN_INFO"Major number: %i - Minor number: %i\n", imajor(inode), iminor(inode));
	//struct file represents an open file, its life-cycle lasts as long as the file remains open
	//Contains important information about the file
	printk(KERN_INFO"File Position: %lld - Permissions: %x\n", filp->f_pos, filp->f_mode);
	return 0;
}
//Remember that for this to work, you have to create a node (preferrably inside /dev) and then type
//sudo mknod <name> c <major> <minor>
//And when you apply a reading command like cat, you trigger this function
static ssize_t chrdev_read(struct file *f, char __user *u, size_t, loff_t *o) {
	printk(KERN_INFO"Read for chrdev was called\n");
	return 0;
}

static int chrdev_release(struct inode *inode, struct file *filp) {
	printk(KERN_INFO"File closed\n");
	return 0;
}
//To confirm arguments for file_operations check out https://elixir.bootlin.com/linux/v6.18/source
//It is a browser for the source-files of many Linux-Kernel-Versions
static struct file_operations fops = {
	.open = chrdev_open,
	.read = chrdev_read,
	.release = chrdev_release,
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
