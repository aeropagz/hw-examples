#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/hrtimer.h>


static struct hrtimer mytimer;
	 	
static enum hrtimer_restart hrtimer_func (struct hrtimer *hrt)
{
	printk(KERN_INFO "hrtimer_fuc called at %lu...\n",jiffies);
	hrtimer_add_expires_ns(&mytimer,1000000);
	return HRTIMER_RESTART;	
}


static int __init mod_init(void)
{
	static ktime_t mytime;
	printk("mod_init called at %lu\n", jiffies);
	hrtimer_init(&mytimer,CLOCK_MONOTONIC,HRTIMER_MODE_REL);
	mytimer.function=hrtimer_func;
	mytime=ktime_set(0,1000000);
	hrtimer_start(&mytimer,mytime,HRTIMER_MODE_REL);
	return 0;
	
}


	 
 static void __exit mod_exit(void)
 {
	printk(KERN_INFO "mod_exit called\n");
	hrtimer_cancel(&mytimer);

 }
	 	

module_init( mod_init );
module_exit( mod_exit );


 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("Wolfram Acker");
 MODULE_DESCRIPTION("Beispiel BK110-3" );
