#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>



MODULE_AUTHOR("TUNG");
MODULE_LICENSE("GPL");


int init_module (void)
{
	printk(KERN_INFO "hello this is the test\n");

	return 0;
}
void cleanup_module(void)
{
	printk(KERN_INFO "goodbye.... !\n");
}