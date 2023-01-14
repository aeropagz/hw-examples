#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/hrtimer.h>
#include <linux/gpio.h>
#include <linux/ioport.h>

#define GPIO_BASE_RPI4 0xFe200000 


static struct hrtimer mytimer;
static int gpio=17;
static int time=1000000;

static void __iomem *virtualbase;

long counter=0;
char gpioStatus=0;
int i=0;
	
static void gpio_set(int gpio,int value)
 {
	 if	 (value==0)
		iowrite32(1<<gpio,virtualbase+0x28);
	 else
		iowrite32(1<<gpio,virtualbase+0x1c);
	 
 }

//So nicht, da von Optimierung verschlungen
/*
static gpio_set(int gpio,int value)
 {
	 if	 (value==0)
	 *((uint*)(virtualbase+0x28))=1<<gpio;
	 else
	*((uint*)(virtualbase+0x1c))=1<<gpio;
	 
 }*/

	 
	 	
static enum hrtimer_restart hrtimer_func (struct hrtimer *hrt)
{
	iowrite32(1<<gpio,virtualbase+0x28);
	iowrite32(1<<gpio,virtualbase+0x1c);
	iowrite32(1<<gpio,virtualbase+0x28);
	iowrite32(1<<gpio,virtualbase+0x1c);
	iowrite32(1<<gpio,virtualbase+0x28);
	iowrite32(1<<gpio,virtualbase+0x1c);
	iowrite32(1<<gpio,virtualbase+0x28);
	iowrite32(1<<gpio,virtualbase+0x1c);
	iowrite32(1<<gpio,virtualbase+0x28);
	iowrite32(1<<gpio,virtualbase+0x1c);
	iowrite32(1<<gpio,virtualbase+0x28);
	iowrite32(1<<gpio,virtualbase+0x1c);

	/*
	*((uint*)(virtualbase+0x28))=1<<17;
	
	*((uint*)(virtualbase+0x1c))=1<<17;
	
	*((uint*)(virtualbase+0x28))=1<<17;
	
	*((uint*)(virtualbase+0x1c))=1<<17;
	
	*((uint*)(virtualbase+0x28))=1<<17;
	
	*((uint*)(virtualbase+0x1c))=1<<17;
	
	*((uint*)(virtualbase+0x28))=1<<17;
	
	*((uint*)(virtualbase+0x1c))=1<<17;
	
	*((uint*)(virtualbase+0x28))=1<<17;
	
	*((uint*)(virtualbase+0x1c))=1<<17;
	
	*((uint*)(virtualbase+0x28))=1<<17;
	
	*((uint*)(virtualbase+0x1c))=1<<17;
	
	*((uint*)(virtualbase+0x28))=1<<17;
	
	*((uint*)(virtualbase+0x1c))=1<<17;
	
	*((uint*)(virtualbase+0x28))=1<<17;
	
	*((uint*)(virtualbase+0x1c))=1<<17;
	
	gpio_set(gpio, 0);
	gpio_set(gpio, 1);
	gpio_set(gpio, 0);
	gpio_set(gpio, 1);
	gpio_set(gpio, 0);
	gpio_set(gpio, 1);
	gpio_set(gpio, 0);
	gpio_set(gpio, 1);
	
	gpio_set(gpio, 0);
	gpio_set(gpio, 1);
	gpio_set(gpio, 0);
	gpio_set(gpio, 1);
	gpio_set(gpio, 0);
	gpio_set(gpio, 1);
	gpio_set(gpio, 0);
	gpio_set(gpio, 1);
	/*
	gpio_set_value(gpio, 0);
	gpio_set_value(gpio, 1);
	gpio_set_value(gpio, 0);
	gpio_set_value(gpio, 1);
	gpio_set_value(gpio, 0);
	gpio_set_value(gpio, 1);
	gpio_set_value(gpio, 0);
	gpio_set_value(gpio, 1);
	
	gpio_set_value(gpio, 0);
	gpio_set_value(gpio, 1);
	gpio_set_value(gpio, 0);
	gpio_set_value(gpio, 1);
	gpio_set_value(gpio, 0);
	gpio_set_value(gpio, 1);
	gpio_set_value(gpio, 0);
	gpio_set_value(gpio, 1);*/
	
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
 
	




static int __init mod_init(void)
{
	static ktime_t mytime;
	config_gpio_as_output(gpio);
	
	
	virtualbase=ioremap(GPIO_BASE_RPI4,100);
		
	printk("realbase ist at %x\n", GPIO_BASE_RPI4);
	printk("virtual base ist at %x\n", virtualbase);
	
	
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
	iounmap(virtualbase);

 }
	 	

module_init( mod_init );
module_exit( mod_exit );


 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("Wolfram Acker");
 MODULE_DESCRIPTION("Beispiel BK110-3" );
