#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/hrtimer.h>


static struct hrtimer mytimer;
	 	
static enum hrtimer_restart hrtimer_callback (struct hrtimer *hrt)
{
	printk("hrtimer_fuc called at %lu...\n",jiffies);
	return HRTIMER_NORESTART;	
}


static int  mod_init(void)
{
	static ktime_t mytime;
	printk("mod_init aufgerufen bei %lu\n", jiffies);
	hrtimer_init(&mytimer,CLOCK_MONOTONIC,HRTIMER_MODE_REL);
	mytimer.function=hrtimer_callback;
	mytime=ktime_set(0,1000000000);
	hrtimer_start(&mytimer,mytime,HRTIMER_MODE_REL);
	return 0;
	
}


	 
 static void  mod_exit(void)
 {
	printk("mod_exit aufgerufen\n");
	hrtimer_cancel(&mytimer);

 }
	 	

module_init( mod_init );
module_exit( mod_exit );


 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("Wolfram Acker");
 MODULE_DESCRIPTION("Beispiel BK110-3" );
