#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wolfram Acker");
MODULE_DESCRIPTION("Beispiel 1");

static int init_helloworld(void)
{
printk("init ausgefuehrt!\n");
return 0;	
}


static void exit_helloworld(void)
{
printk("exit ausgefuehrt!\n");
	
}


module_init(init_helloworld);
module_exit(exit_helloworld);
