#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h> //gpio_desc, gpio-funcs 

//IO pins used for the button and offset
#define IO_LED 21
#define IO_BUTTON 20
//Offset to correctly address gpio-pins, you can find this out under the folder /sys/class/gpio/gpiochip<XXX>
//The suffix of the folder whose label-file has the word gpio on it is the required offset to definde here
#define IO_OFFSET 0 

//To check out the pin layout of the Raspberry Pi, you can access this website https://pinout.xyz/
//Since the 40-Pin introduction, all models have the same pinout with the exception of the Zero and Zero W.

static struct gpio_desc* led;
static struct gpio_desc* button;

static int __init gpioctrl_init(void);
static void __exit gpioctrl_exit(void);


static int __init gpioctrl_init(void) {
	int status;
	//To descriptor
	led = gpio_to_desc(IO_LED + IO_OFFSET);
	if(!led) {
		printk(KERN_ALERT"Error geting pin %d\n", IO_LED);
		//Meaning: Error - no device
		return -ENODEV;
	}
	button = gpio_to_desc(IO_BUTTON + IO_OFFSET);
	if(!button) {
		printk(KERN_ALERT"Error geting pin %d\n", IO_BUTTON);
		//Meaning: Error - no device
		return -ENODEV;
	}
	//Set the LED as an output-pin, whose desired value is 0
	status = gpiod_direction_output(led, 0);
	//In case we don't receive that, send an error
	if(status) {
		printk(KERN_ALERT"Error seting pin %d to output\n", IO_LED);
		//Meaning: Error - no device
		return status;
	}
	//Set the button as an input-pin, whose desired value is 0
	status = gpiod_direction_input(button);
	//In case we don't receive that, send an error
	if(status) {
		printk(KERN_ALERT"Error seting pin %d to input\n", IO_BUTTON);
		//Meaning: Error - no device
		return status;
	}
	gpiod_set_value(led, 1);
	printk(KERN_INFO"GPIOctrl - Button is %spressed\n", gpiod_get_value(button) ? "" : "not ");
	return 0;
}

static void __exit gpioctrl_exit(void) {
	gpiod_set_value(led, 0);
	printk(KERN_INFO"Goodbye Viki! Removing module\n");
}


module_init(gpioctrl_init);
module_exit(gpioctrl_exit);

//Metadata can be accessed by calling $ modinfo <.ko-file>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lucas Jimenez Resck");
MODULE_DESCRIPTION("Kernel module to start controlling Raspberry Pi's GPIOs");
