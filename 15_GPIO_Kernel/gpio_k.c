#include <linux/module.h>

#include <linux/hrtimer.h>
#include <linux/gpio.h>


static struct hrtimer mytimer;
static int gpio=22;
static int time=4000000;

char gpioStatus=0;
	
	
	 	
static enum hrtimer_restart hrtimer_func (struct hrtimer *hrt)
{
	gpioStatus=!gpioStatus;
	gpio_set_value(gpio, gpioStatus);
	hrtimer_add_expires_ns(&mytimer,time);

	return HRTIMER_RESTART;	
}



 static int config_gpio_as_output(int gpionr)
 {
	 int err;
	 char name[20];
	 snprintf(name,sizeof(name),"gpio-%d",gpionr);
	 err=gpio_request(gpionr,name);
	 if(err)
	 {
		 printk("gpio_request failed %d\n",err);
		 return -1;
	 }
	 err=gpio_direction_output(gpionr,0);
	 if(err)
	 {
		 printk("direction_output failed %d\n",err);
		 		 gpio_free(gpionr);
		 return -1;
     }
     return gpionr;
 }
 
	
	
// Dies nur als Beispiel, wird nicht benutzt	
 static int config_gpio_as_input(int gpionr)
 {
	 int err;
	 char name[20];
	 snprintf(name,sizeof(name),"gpio-%d",gpionr);
	 err=gpio_request(gpionr,name);
	 if(err)
	 {
		 printk("gpio_request failed %d\n",err);
		 return -1;
	 }
	 err=gpio_direction_input(gpionr);
	 if(err)
	 {
		 printk("direction_output failed %d\n",err);
		 		 gpio_free(gpionr);
		 return -1;
     }
     return gpionr;
 }
 
	




static int __init mod_init(void)
{
	static ktime_t mytime;
	config_gpio_as_output(gpio);
	printk("mod_init called at %lu\n", jiffies);
	hrtimer_init(&mytimer,CLOCK_MONOTONIC,HRTIMER_MODE_REL);
	mytimer.function=hrtimer_func;
	mytime=ktime_set(0,time);
	hrtimer_start(&mytimer,mytime,HRTIMER_MODE_REL);
	return 0;
	
}


	 
 static void __exit mod_exit(void)
 {
	printk(KERN_INFO "mod_exit called\n");
	gpio_free(gpio);
	hrtimer_cancel(&mytimer);

 }
	 	

module_init( mod_init );
module_exit( mod_exit );


 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("Wolfram Acker");
 MODULE_DESCRIPTION("Beispiel GPIO" );
